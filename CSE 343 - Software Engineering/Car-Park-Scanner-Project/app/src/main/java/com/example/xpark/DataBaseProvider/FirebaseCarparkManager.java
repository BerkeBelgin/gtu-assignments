package com.example.xpark.DataBaseProvider;

import android.app.Activity;
import android.content.Intent;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationManager;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.example.xpark.Activities.ParkingInformationActivity;
import com.example.xpark.Module.CarPark;
import com.example.xpark.Module.User;
import com.example.xpark.Utils.ToastMessageConstants;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.LatLngBounds;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.MutableData;
import com.google.firebase.database.Transaction;
import com.google.firebase.database.ValueEventListener;
import com.google.zxing.common.StringUtils;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import es.dmoral.toasty.Toasty;

import static android.content.Context.LOCATION_SERVICE;


public class FirebaseCarparkManager {
    private GoogleMap map;
    private String oldDistrict=null;
    private final Activity activity;

    // store the related listener about database fields.
    private ChildEventListener currentListener;

    private DatabaseReference currentListeningDBfield;

    // mapping between car park and marker on the screen
    private final HashMap<Marker,CarPark> markersOnScreen;

    // mutex for markes on screen
    private Object markers_on_screen_lock;

    /**
     * Singleton constructor.
     */
    public FirebaseCarparkManager(Activity activity,HashMap<Marker,CarPark> markersOnScreen, Object lock)
    {
        this.markersOnScreen = markersOnScreen;
        this.activity = activity;
        this.markers_on_screen_lock = lock;
    }

    public void setMap(GoogleMap map){
        this.map = map;
    }

    /**
     * Shows the closest car parks in the current location in a different thread.
     * UI, user space, call this method.
     */
    public void showNearestCarParks()
    {
        new Thread(() -> {

            /* Give info msg */
            activity.runOnUiThread(() -> Toasty.info(activity.getApplicationContext(), ToastMessageConstants.TOAST_MSG_INFO_CARPARK_SEARCH,Toast.LENGTH_SHORT).show());

            /* get current location */
            Location currentLocation = getLastKnownLocation();

            /* try to find district name from current location */
            String parsedAddr = tryToParseAddress(currentLocation.getLatitude(),currentLocation.getLongitude());

            activity.runOnUiThread(() -> {
                if(parsedAddr != null)
                    showNearestCarParks(parsedAddr);
                else
                {   /* give err msg to screen */
                    activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_ERROR_CARPARK_NOT_FOUND,Toast.LENGTH_SHORT).show());
                }
            });

        }).start();
    }

    /**
     * Shows the selected directions car parks in the current location in a different thread.
     * UI, user space, call this method.
     */
    public void showNearestCarParks(double lat, double lng)
    {
        new Thread(() -> {

            /* Give info msg */
            activity.runOnUiThread(() -> Toasty.info(activity.getApplicationContext(), ToastMessageConstants.TOAST_MSG_INFO_CARPARK_SEARCH,Toast.LENGTH_SHORT).show());

            /* try to find district name from current location */
            String parsedAddr = tryToParseAddress(lat,lng);

            activity.runOnUiThread(() -> {
                if(parsedAddr != null)
                    showNearestCarParks(parsedAddr);
                else
                {   /* give err msg to screen */
                    activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_ERROR_CARPARK_NOT_FOUND,Toast.LENGTH_SHORT).show());
                }
            });

        }).start();
    }

    public void startParking(CarPark carpark, User user, String time)
    {
        // Todo : check balance
        this.registerUserToCarpark(carpark,user,time);
    }

    /**
     * Gets the current location of user.
     * @return Current location of user as Location type which provides getter of latitude and longitude.
     * @throws SecurityException If user don't agree with sharing his / her location.
     */
    public Location getLastKnownLocation() throws SecurityException{
        LocationManager locationManager = (LocationManager)activity.getSystemService(LOCATION_SERVICE);
        List<String> providers = locationManager.getProviders(true);
        Location bestLocation = null;
        for (String provider : providers) {
            System.out.println("PROVIDE : " + provider);
            Location l = locationManager.getLastKnownLocation(provider);

            if (l == null) {
                continue;
            }
            if (bestLocation == null || l.getAccuracy() < bestLocation.getAccuracy()) {
                // Found best last known location: %s", l);
                bestLocation = l;
                System.out.println(">LOCATION ACCURACY = " + bestLocation.getAccuracy());
                System.out.println(">PARSE ADDRESS = " + tryToParseAddress(bestLocation.getLatitude(),bestLocation.getLongitude()));
            }
        }

        return bestLocation;
    }

    /**
     * Adds new mark to the google map related car park.
     * @param newCarPark new car park object to be added on the map.
     * @param title Title of the map.
     * @param park_info String in the marker, explanation about related car park.
     * @return Newly added marker to google map.
     */
    private void addCarparkToMap(CarPark newCarPark,String title, String park_info)
    {
        Marker m = map.addMarker(new MarkerOptions().position(new LatLng(newCarPark.getLatitude(),newCarPark.getLongitude())).title(newCarPark.getName()).snippet(park_info));
        synchronized (markers_on_screen_lock) {
            markersOnScreen.put(m, newCarPark);
        }
    }

    @VisibleForTesting
    private void focusMapToMarkers()
    {
        LatLngBounds.Builder builder = new LatLngBounds.Builder();
        synchronized (markers_on_screen_lock) {
            for (Map.Entry<Marker, CarPark> val : markersOnScreen.entrySet())
                builder.include(val.getKey().getPosition());
        }

        int padding = 10; // default
        LatLngBounds bounds = builder.build();
        CameraUpdate cu = CameraUpdateFactory.newLatLngBounds(bounds, padding);

        // focus the camera
        map.animateCamera(cu);
    }

    /**
     * Observer. Adds listener.
     * Starts to listen the close environment in order to catch the updates.
     * This is for keeping the screen (map) update.
     * If any updates caught, the listener will handle it by updating the google map.
     * @param districtName District name to be listen.
     */
    private void addListenerForDistrict(String districtName)
    {
        /* get database reference */
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference(FirebaseDBConstants.DB_CARPARK_FIELD).child(districtName);
        currentListeningDBfield = ref;
        ChildEventListener listener = new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

                /* give info msg */
                activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_INFO_MAP_UPDATED,Toast.LENGTH_SHORT).show());

                CarPark newPark = new CarPark(snapshot);

                Marker marker = null;
                synchronized (markers_on_screen_lock) {

                    for (Map.Entry<Marker, CarPark> val : markersOnScreen.entrySet()) {
                        if (val.getValue().equals(newPark)) {
                            marker = val.getKey();
                            break;
                        }
                    }
                    System.out.println("MARKER FOUND = " + markersOnScreen.get(marker));
                    System.out.println("markers size " + markersOnScreen.size());
                }

                marker.setSnippet(newPark.toString());
                marker.setVisible(false);
                marker.setVisible(true);
                marker.showInfoWindow();
            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot snapshot) {

            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        };

        currentListener = listener;
        ref.addChildEventListener(listener);
    }

    /**
     * This methods register given user to given car park.
     * Field of the car park in the database does not store the users.
     * Users store the id of the car park which he / she parked.
     *
     * This method registers user to car park "directly", not checks the balance or anything..
     *
     * @param carpark Target car park.
     * @param user User to be registered.
     */
    private void registerUserToCarpark(CarPark carpark, User user, String time)
    {
        /* first find the reference of the given car park */
        String carpark_general_id = carpark.getGeneralid();
        String[] tokens = carpark_general_id.split("-");
        String db_ref_district = tokens[0];
        String db_ref_carpark_id = tokens[1];

        System.out.println("DEBUG : " + db_ref_district + " -- " + db_ref_carpark_id);
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_CARPARK_FIELD).child(db_ref_district).child(db_ref_carpark_id);

        ref.runTransaction(new Transaction.Handler() {
            @NonNull
            @Override
            public Transaction.Result doTransaction(@NonNull MutableData currentData) {

                /* get car park object from database */
                HashMap map = (HashMap)currentData.getValue();
                if(map == null)
                    return Transaction.success(currentData);

                /* get park object from data base */
                CarPark park = new CarPark((HashMap) currentData.getValue());

                /* check available space */
                if(park.getFreeArea() > 0)
                {
                    /* stop listener */
                    currentListeningDBfield.removeEventListener(currentListener);

                    /* give info msg about reserving */
                    activity.runOnUiThread(() -> Toasty.info(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_INFO_RESERVING,Toast.LENGTH_SHORT).show());

                    /* increment used counter */
                    park.incrementUsed();

                    /* update the database */
                    currentData.setValue(park);

                    /* find user field in DB */
                    DatabaseReference uref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_USER_FIELD).child(user.getUid());
                    user.setCarparkid(park.getGeneralid());
                    user.setParkingTime(time);

                    /* update user in the DB */
                    uref.setValue(user);
                    return Transaction.success(currentData);
                }
                else
                    return Transaction.abort();
            }

            @Override
            public void onComplete(@Nullable DatabaseError error, boolean committed, @Nullable DataSnapshot currentData) {
                System.out.println("Commit check : " + committed + " " + currentData.getValue());
                if(committed)
                {
                    /* switch next activity */
                    new Thread(() -> {
                        try {
                            Thread.sleep(2000);
                            Intent intent = new Intent(activity, ParkingInformationActivity.class);
                            intent.putExtra("CURRENT_USER",user);
                            intent.putExtra("CARPARK",carpark);
                            activity.startActivity(intent);
                            activity.finish();
                        }catch (InterruptedException ex)
                        {

                        }
                    }).start();
                }
                else
                    activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_INFO_MAP_UPDATED,Toast.LENGTH_SHORT).show());
            }
        });
    }

    /**
     * Get District (ilce) from given address.
     * Todo : this method will be private later.
     * @param inputAdress address to be parsed.
     * @return District of given address, if parsed successfully.
     */
    private String parseAddressToDistrict(String inputAdress)
    {
        System.out.println(">ADRESINIZ : " + inputAdress);
        String[] tokens = inputAdress.split(", ");

        /* find address token str index */
        int index = -1;
        for (int i = 0; i < tokens.length; i++)
        {
            if(tokens[i].indexOf("/") > 0 && getCharCount(tokens[i],' ') == 1){
                index = i;
                break;
            }
        }

        if(-1 == index)
            return null;

        String res = tokens[index].replaceAll("/","_");
        return res.replaceAll(" ","_");
    }

    /**
     * Checks that address is regular address or not.
     * show nearest parks method uses this helper method.
     * @param adress address to be checked
     * @return True if address is successfully parsable.
     */
    private boolean isAdressParsed(String adress)
    {
        if(adress == null)
            return false;

        int counter = 0;
        for (int i = 0; i < adress.length() && counter <= 2; i++) {
            if(adress.charAt(i) == '_')
                ++counter;
        }
        return counter == 2;
    }

    /**
     * If adress is not parsable, try to get some meaningful data.
     * @param latitude Latitude of the given address.
     * @param longitude Longitude of the given address.
     * @return parsed address if successful, null on error.
     */
    public String tryToParseAddress(double latitude, double longitude)
    {
        Geocoder gcd = new Geocoder(activity.getApplicationContext(), Locale.getDefault());
        final double INCREMENT_AMOUNT = 0.001;
        final int MAX_TRY = 100;
        int i = 0;
        String parsedAddr = null;
        try {
            /* if address is not parsed yet, try to find */

            System.out.println("Test: " + gcd);
            while(!isAdressParsed(parsedAddr) && i < MAX_TRY)
            {
                List<Address> addresses = gcd.getFromLocation(latitude, longitude, 1);

                if (addresses != null && addresses.size() > 0) {
                    parsedAddr = parseAddressToDistrict(addresses.get(0).getAddressLine(0));
                    System.out.println(">address parse try : " + parsedAddr);
                }

                if(i++ % 2 == 0)
                    longitude += INCREMENT_AMOUNT;
                else
                    latitude += INCREMENT_AMOUNT;

            }
        }
        catch (IOException ex)
        {
            /* TODO : Handle error */
            System.out.println("PEX : " + ex.getMessage());
            activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_ERROR_GRPC,Toast.LENGTH_SHORT).show());
        }

        return parsedAddr;
    }

    private int getCharCount(String s,char c)
    {
        int count = 0;
        for (int i = 0; i < s.length() ; i++) {
            if(s.charAt(i) == c)
                ++count;
        }
        return count;
    }

    private void showNearestCarParks(String districtName)
    {
        /* if location has changed, remove the older listeners*/
        if(oldDistrict != null) {
            if (!oldDistrict.equals(districtName)) {
                DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_CARPARK_FIELD).child(oldDistrict);
                ref.removeEventListener(currentListener);
                oldDistrict = districtName;
            }
        }

        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_CARPARK_FIELD).child(districtName);

        /* adds event listener for given district, start observe */
        this.addListenerForDistrict(districtName);

        ref.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot shot : snapshot.getChildren())
                {
                    /* add new car park to the map */
                    CarPark newCarPark = new CarPark(shot);
                    addCarparkToMap(newCarPark,newCarPark.getName(),newCarPark.toString());

                    /* focus on the center of the car parks (marks) */
                    if(markersOnScreen.size() > 0)
                        focusMapToMarkers();
                    else
                    {
                        /* TODO : otopark bulunamadi, ekrana guzel bilgi ver... */
                        activity.runOnUiThread(() -> Toasty.warning(activity.getApplicationContext(),ToastMessageConstants.TOAST_MSG_ERROR_CARPARK_NOT_FOUND,Toast.LENGTH_SHORT).show());
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}