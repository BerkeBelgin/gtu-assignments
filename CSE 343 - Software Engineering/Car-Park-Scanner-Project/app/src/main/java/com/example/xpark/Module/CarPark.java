package com.example.xpark.Module;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.example.xpark.DataBaseProvider.FirebaseDBConstants;
import com.google.android.gms.maps.model.LatLng;
import com.google.firebase.database.DataSnapshot;

import java.io.Serializable;
import java.util.HashMap;

public class CarPark implements Serializable {
    private String id;
    private String generalid;
    private String name;
    private String phone;
    private double longitude;
    private double latitude;
    private int capacity;
    private int used;
    private double pricePerMinute;

    public CarPark(String id,String generalid,String name,String phone,int capacity,int used){
        this.id = id;
        this.generalid = generalid;
        this.name = name;
        this.phone = phone;
        this.capacity = capacity;
        this.used = used;
    }


    public CarPark(){
    }

    /**
     * Initialize carPark object with given data snap shot - comes from database -
     * @param shot Data comes from real time database.
     */
    public CarPark(DataSnapshot shot)
    {
        this.longitude = (double) shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_LONGITUDE).getValue();
        this.latitude = (double) shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_LATITUDE).getValue();
        this.id = (String)shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_ID).getValue();
        this.capacity = ((Long)(shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_CAPACITY).getValue())).intValue();
        this.used = ((Long)(shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_USED).getValue())).intValue();
        this.name = (String)shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_NAME).getValue();
        this.phone = (String)shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_PHONE).getValue();
        this.generalid = (String)shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_GENERALID).getValue();

        // TODO : Exception yakalanmayacak
        try {
            this.pricePerMinute = (double) shot.child(FirebaseDBConstants.DB_CARPARK_CHILD_PRICEPERMINUTE).getValue();
        } catch (Exception e) {
            this.pricePerMinute = 0;
        }

    }

    /**
     * Initialize carPark object with given hash map - comes from database -
     * @param map Map to be parsed into car park object.
     */
    public CarPark(HashMap map)
    {
        this.longitude = (double)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_LONGITUDE);
        this.latitude = (double)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_LATITUDE);
        this.capacity = ((Long)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_CAPACITY)).intValue();
        this.used = ((Long)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_USED)).intValue();
        this.id = (String)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_ID);
        this.phone = (String)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_PHONE);
        this.name =  (String)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_NAME);
        this.generalid = (String)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_GENERALID);

        // TODO : Exception yakalanmayacak

        try {
            this.pricePerMinute = (double)map.get(FirebaseDBConstants.DB_CARPARK_CHILD_PRICEPERMINUTE);
        } catch (Exception e) {
            this.pricePerMinute = 0;
        }
    }

    /**
     * Gets the ID of the car park.
     * @return ID of the car park.
     */
    public String getId() {
        return id;
    }

    /**
     * Gets the phone number of the car park.
     * @return Phone number of the car park.
     */
    public String getPhone() {
        return phone;
    }

    public double getPricePerMinute() { return this.pricePerMinute; }
    public void setPricePerMinute(double price) { this.pricePerMinute = price; }

    /**
     *
     * @param used
     */
    public void setUsed(int used) {
        this.used = used;
    }

    /**
     * Gets the name of the car park.
     * @return Name of the car park.
     */
    public String getName() {
        return name;
    }

    /**
     * Gets the number of the free parking are in the car park.
     * @return Number of the free parking are in the car park.
     */
    public int getFreeArea()
    {
        return getCapacity() - getUsed();
    }

    public String getGeneralid() {
        return generalid;
    }

    public void setGeneralid(String general_id) {
        this.generalid = general_id;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getUsed() {
        return used;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void incrementUsed(){
        this.setUsed(this.getUsed() + 1);
    }

    public void decrementUsed(){
        this.setUsed(this.getUsed() - 1);
    }

    public double getLongitude(){ return this.longitude;}
    public double getLatitude(){ return this.latitude;}

    @NonNull
    @Override
    /* TODO : change this in a better way */
    public String toString()
    {
        return "Tel : " + this.getPhone() + "\n" + "Boş Yer : " + this.getFreeArea() + "\n" + "Fiyat: " + this.getPricePerMinute() + "  (Dakika Başı)";
    }

    @Override
    public int hashCode()
    {
        String s = " " + latitude + longitude + generalid;
        return s.hashCode();
    }

    @Override
    public boolean equals(@Nullable Object obj) {
        CarPark test = (CarPark)obj;
        return test.hashCode() == this.hashCode();
    }
}