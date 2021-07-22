package com.example.xpark.Activities;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.annotation.VisibleForTesting;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import com.example.xpark.DataBaseProvider.FirebaseDBConstants;
import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.Module.CarPark;
import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.example.xpark.Utils.ToastMessageConstants;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.material.navigation.NavigationView;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.MutableData;
import com.google.firebase.database.Transaction;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.util.HashMap;
import java.time.ZoneId;
import es.dmoral.toasty.Toasty;

public class ParkingInformationActivity extends AppCompatActivity implements OnMapReadyCallback {

    private Button finishPark_button;
    private TextView textTime;
    private User currentUser;
    private CarPark selectedpark;
    private Button qrScanButton;
    private Boolean qrBoolean;
    private DrawerLayout mDrawer;
    private Toolbar toolbar;
    private NavigationView nvDrawer;
    private ActionBarDrawerToggle drawerToggle;
    private FirebaseUserManager fbUser;

    public static String park_id = "";
    public static Boolean isScanned = false;

    /* CAMERA PERMISSION REQUEST CODE */
    private static final int MY_CAMERA_REQUEST_CODE = 100;

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_parking_information);
        System.out.println("PARKING INF ACTIVITY");

        fbUser = new FirebaseUserManager(this);
        init_logged_user();
        init_selected_carpark();

        UI_init();
        checkParking();
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        if(googleMap != null) {
            if (selectedpark != null) {
                LatLng coordinates = new LatLng(selectedpark.getLatitude(), selectedpark.getLongitude());
                googleMap.moveCamera(CameraUpdateFactory.newLatLngZoom(coordinates, 16));
                googleMap.addMarker(new MarkerOptions().position(coordinates).title(selectedpark.getName()));
            }
        }
    }

    private void init_selected_carpark(){
        Intent intent = getIntent();
        selectedpark = (CarPark) intent.getSerializableExtra("CARPARK");
        System.out.println("GETTED CARPARK NAME:" + selectedpark.getName());
    }

    private void checkParking() {
        if (currentUser != null) {
            if (currentUser.getCarparkid().equals(ParkingInformationActivity.park_id))
                finishPark();
            else if (isScanned)
                Toasty.warning(this.getApplicationContext(), ToastMessageConstants.TOAST_MSG_ERROR_WRONG_QR, Toast.LENGTH_SHORT).show();
        } else {
            throw new ExceptionInInitializerError("The User cannot be getted...");
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void scanCarParkQR() {
        /* Eğer uygulamanın kamera izni yoksa bunu sorar */
        if (ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.CAMERA)
                == PackageManager.PERMISSION_DENIED) {
            requestPermissions(new String[]{Manifest.permission.CAMERA}, MY_CAMERA_REQUEST_CODE);
        } else {
            Intent intent = new Intent(getApplicationContext(), ScanCodeActivity.class);
            intent.putExtra("CURRENT_USER", currentUser);
            startActivity(intent);
            finish();
        }
    }

    @VisibleForTesting
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // The action bar home/up action should open or close the drawer.
        switch (item.getItemId()) {
            case android.R.id.home:
                mDrawer.openDrawer(GravityCompat.START);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private boolean onDrawerItemSelected(MenuItem item) {
        int LAUNCH_SECOND_ACTIVITY = 1;
        if(item.getItemId() == R.id.nav_third_fragment){
            SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
            settings.edit().clear().commit();

            Intent intent = new Intent(this, LoginActivity.class);
            this.startActivity(intent);
            finish();

            //close navigation drawer
            mDrawer.closeDrawer(GravityCompat.START);
            return true;
        } else if(item.getItemId() == R.id.nav_second_fragment){
            Intent intent = new Intent(this, BalanceActivity.class);
            intent.putExtra("CURRENT_USER", currentUser);
            this.startActivityForResult(intent,LAUNCH_SECOND_ACTIVITY);

            //close navigation drawer
            mDrawer.closeDrawer(GravityCompat.START);
            return true;
        } else {
            Intent intent = new Intent(this, ProfileActivity.class);
            intent.putExtra("CURRENT_USER", currentUser);
            this.startActivityForResult(intent,LAUNCH_SECOND_ACTIVITY);

            mDrawer.closeDrawer(GravityCompat.START);
            return true;
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
        super.onActivityResult(requestCode, resultCode, intent);
        int LAUNCH_SECOND_ACTIVITY = 1;

        if (requestCode == LAUNCH_SECOND_ACTIVITY) {
            if(resultCode == Activity.RESULT_OK){
                currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
                System.out.println("USER GETTED ONACTIVITYRES : " + currentUser);
            }
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void UI_init() {
        toolbar = (Toolbar) findViewById(R.id.toolbar2);
        mDrawer = (DrawerLayout) findViewById(R.id.drawer_layout_2);
        nvDrawer = (NavigationView) findViewById(R.id.nav_view2);

        drawerToggle = new ActionBarDrawerToggle(this, mDrawer, toolbar, R.string.drawer_open,  R.string.drawer_close);

        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        drawerToggle.setDrawerIndicatorEnabled(true);
        drawerToggle.syncState();

        mDrawer.addDrawerListener(drawerToggle);
        nvDrawer.setNavigationItemSelectedListener(
                new NavigationView.OnNavigationItemSelectedListener() {
                    @Override
                    public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                        return onDrawerItemSelected(menuItem);
                    }
                }
        );

        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map2);
        mapFragment.getMapAsync(this);

        finishPark_button = findViewById(R.id.button_finish);
        textTime = findViewById(R.id.text_time);
        qrScanButton = findViewById(R.id.QrScanner);
        textTime.setText(currentUser.getParkingTime());

        /* parkı bitir butonu */
        finishPark_button.setOnClickListener(v -> { finishPark(); });
        /* parkı tarayarak bitir butonu yukardaki şuanlık direkt parkı bitirir testler için kullanıyoruz */
        qrScanButton.setOnClickListener(v -> { scanCarParkQR(); });
    }

    private void init_logged_user() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        System.out.println("USER GETTED : " + currentUser);
    }

    private void finishPark() {
        // if not parked yet, return
        if(currentUser.getCarparkid().equals(User.NOT_PARKED))
            return;

        LocalDateTime finishtime = LocalDateTime.now(ZoneId.of("Europe/Istanbul"));
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime parkingtime = LocalDateTime.parse(currentUser.getParkingTime(), formatter);

        long diff = calculateTime(finishtime, parkingtime);
        payment(diff);

        // Todo : handle balance and etc..
        this.removeUserFromCarpark();
    }

    private void payment(long diff){
        double amount = diff * selectedpark.getPricePerMinute();
        double userBalance = currentUser.getCreditbalance();

        if(userBalance >= amount){
            double remainingBalance = userBalance - amount;
            fbUser.updateBalance(currentUser,remainingBalance);
        }
        else {
            double debt = amount - userBalance;
            fbUser.updateDebt(currentUser,debt,true);
        }
    }

    private long calculateTime(LocalDateTime d1, LocalDateTime d2){
        long diff = ChronoUnit.MINUTES.between(d2, d1);

        System.out.println("CALCULATED TIME(minute): " + diff);
        return diff;
    }

    private void removeUserFromCarpark()
    {
        /* parse user */
        String carParkGnrlId = currentUser.getCarparkid();

        /* get district */
        String[] tokens = carParkGnrlId.split("-");
        String db_district_field = tokens[0];
        String db_carpark_id = tokens[1];
        System.out.println("DB DISTRICT = " + db_district_field);
        System.out.println("DB ID = " + db_carpark_id);

        /* find database reference from user */
        DatabaseReference pref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_CARPARK_FIELD).child(db_district_field).child(db_carpark_id);
        pref.runTransaction(new Transaction.Handler() {
            @NonNull
            @Override
            public Transaction.Result doTransaction(@NonNull MutableData currentData) {
                /* get car park object from database */
                HashMap map = (HashMap)currentData.getValue();
                if(map == null)
                    return Transaction.success(currentData);

                /* get park object from data base */
                CarPark park = new CarPark((HashMap) currentData.getValue());

                /* increment free are in car park */
                park.decrementUsed();

                /* update the database */
                currentData.setValue(park);

                /* find user field in DB */
                DatabaseReference uref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_USER_FIELD).child(currentUser.getUid());
                currentUser.removeCarparkid();
                currentUser.removeParkingTime();

                /* update the user in DB */
                uref.setValue(currentUser);
                return Transaction.success(currentData);
            }

            @Override
            public void onComplete(@Nullable DatabaseError error, boolean committed, @Nullable DataSnapshot currentData) {
                System.out.println("Commit check : " + committed + " " + currentData.getValue());
                if(committed){
                    Intent intent = new Intent(getApplicationContext(), MapsActivity.class);
                    intent.putExtra("CURRENT_USER",currentUser);
                    startActivity(intent);
                    finish();
                }
                //this.runOnUiThread(() -> Toasty.warning(this.getApplicationContext(), ToastMessageConstants.TOAST_MSG_INFO_MAP_UPDATED, Toast.LENGTH_SHORT).show());
            }
        });
    }
}