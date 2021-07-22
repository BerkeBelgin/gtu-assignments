package com.example.xpark.Module;

/**
 * Author : Dilara Karakas.
 */


import com.example.xpark.DataBaseProvider.FirebaseDBConstants;
import com.google.firebase.database.DataSnapshot;

import java.io.Serializable;
public class User implements Serializable {

    public static final String NOT_PARKED = "NOT_PARKED";

    /** User's Email */
    private final String eMail;
    /** User's Phone  */
    private String phone;
    /** User's Credit Balance */
    private double credit_balance;
    /* uid for auth */
    private String uid;
    /* parked carpark id */
    private String carparkid;
    /* parking time*/
    private String parkingtime;
    /* banned information */
    private boolean banned;
    /* dept information */
    private double debt;

    /**
     * Builds a user object
     */
    public User(){
        this.phone = null;
        this.eMail = null;
        this.credit_balance = 0.0;
        this.carparkid = NOT_PARKED;
        this.parkingtime = NOT_PARKED;
        this.banned = false;
        this.debt = 0.0;
    }

    public User(DataSnapshot shot)
    {
        this.eMail = (String)shot.child(FirebaseDBConstants.DB_USER_CHILD_EMAIL).getValue();
        this.phone = (String)shot.child(FirebaseDBConstants.DB_USER_CHILD_PHONE).getValue();
        this.uid = (String)shot.child(FirebaseDBConstants.DB_USER_CHILD_UID).getValue();
        this.credit_balance = ((Long)(shot.child(FirebaseDBConstants.DB_USER_CHILD_CREDITBALANCE).getValue())).doubleValue();
        this.carparkid = (String)shot.child(FirebaseDBConstants.DB_USER_CHILD_CARPARKID).getValue();
        this.parkingtime = (String) shot.child(FirebaseDBConstants.DB_USER_CHILD_PARKINGTIME).getValue();
        this.banned = ((Boolean)(shot.child(FirebaseDBConstants.DB_USER_CHILD_ISBANNED).getValue())).booleanValue();
        this.debt = ((Double)(shot.child(FirebaseDBConstants.DB_USER_CHILD_DEBT).getValue())).doubleValue();
    }

    public User(String phone,String email,double credit_balance, String carparkid, String parkingtime, boolean banned, double debt){
        this.eMail = email;
        this.phone = phone;
        this.credit_balance = credit_balance;
        this.carparkid = carparkid;
        this.parkingtime = parkingtime;
        this.banned = banned;
        this.debt = debt;
    }
    public User(String phone, String email) {
        this.eMail = email;
        this.phone = phone;
        this.credit_balance = 50;
        this.carparkid = NOT_PARKED;
        this.parkingtime = NOT_PARKED;
        this.banned = false;
        this.debt = 0.0;
    }

    /**
     * Setter phone
     * @param phone given User's phone
     */
    public void setPhone(String phone) {
        this.phone = phone;
    }

    /**
     * Setter credit balance
     * @param credit_balance given User's credit balance
     */
    public void setCreditbalance(double credit_balance) {
        this.credit_balance = credit_balance;
    }

    /**
     * Sets the UID for user.
     * @param uid UID to be setted.
     */
    public void setUid(String uid) {
        this.uid = uid;
    }

    /**
     * Sets the parked carpark id for user.
     * @param id id to be setted.
     */
    public void setCarparkid(String id){
        this.carparkid = id;
    }

    /**
     * Sets the parking time id for user.
     * @param time time to be setted.
     */
    public void setParkingTime(String time) { this.parkingtime = time; }

    /**
     * set the banned information of user
     * @param x will be assign banned information
     */
    public void setBanned(boolean x) { this.banned = x; }

    /**
     * Clears the value of parked carpark id.
     */
    public void removeCarparkid()
    {
        this.carparkid = NOT_PARKED;
    }

    /**
     * Clears the value of parking time.
     */
    public void removeParkingTime() { this.parkingtime = NOT_PARKED; }

    public void setDebt(double x) { this.debt = x; }
    public double getDebt() { return this.debt; }

    /**
     * Gets the UID of user.
     * @return UID of user.
     */
    public String getUid() {
        return uid;
    }

    /**
     * Getter email
     * @return string is user's email
     */
    public String getEmail() {
        return eMail;
    }
    /**
     * Getter phone
     * @return string is user's phone
     */
    public String getPhone() {
        return phone;
    }
    /**
     * Getter credit_balance
     * @return double is user's credit balance
     */
    public double getCreditbalance() {
        return credit_balance;
    }

    /**
     * Gets the parked carpark id.
     * @return carpark id.
     */
    public String getCarparkid() {return carparkid;}

    /**
     * Gets the parking time.
     * @return parking time.
     */
    public String getParkingTime() {return parkingtime;}

    /**
     * Banned information
     * @return true if user banned otherwise false
     */
    public boolean getBanned() { return this.banned; }

    /**
     * Overridden toString method to show user's data information
     * @return string user's data information
     */

    @Override
    public String toString() {
        return "User{" +
                "email="+this.eMail +
                ",phone="+this.phone +
                ",uid="+this.uid +
                ",carparkid="+this.carparkid +
                ",parkingtime="+this.parkingtime +
                ",credit="+this.credit_balance +
                ",banned="+this.banned +
                ",debt="+this.debt +
                "}";
    }
}
