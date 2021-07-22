package com.example.xpark.DataBaseProvider;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;
import android.widget.Toast;
import androidx.annotation.NonNull;
import com.example.xpark.Activities.LoginActivity;
import com.example.xpark.Activities.MapsActivity;
import com.example.xpark.Activities.ParkingInformationActivity;
import com.example.xpark.Module.CarPark;
import com.example.xpark.Utils.ToastMessageConstants;
import com.example.xpark.Module.User;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.firebase.FirebaseNetworkException;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseAuthInvalidCredentialsException;
import com.google.firebase.auth.FirebaseAuthInvalidUserException;
import com.google.firebase.auth.FirebaseAuthWeakPasswordException;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import es.dmoral.toasty.Toasty;

/**
 * Author : Goktug Akin.
 */

public class FirebaseUserManager {

    private static final String DB_USER_FIELD = FirebaseDBConstants.DB_USER_FIELD;
    private final Activity activity_ref;

    public FirebaseUserManager(Activity activity)
    {
        this.activity_ref = activity;
    }

    /**
     * Login olmayi dener. Basarili olursa intent yaratarak yeni bir activitye gecer.
     * @param email Kullanici maili.
     * @param password Kullanici sifresi.
     * @note Login ekraninda, (LoginActivity) de cagirilmali.
     */
    public void signInUser(String email, String password)
    {
        FirebaseAuth auth = FirebaseAuth.getInstance();
        auth.signInWithEmailAndPassword(email, password).addOnCompleteListener(task -> {
            if(task.isSuccessful()){
                Log.i("USER LOGIN", "LOGIN SUCCEED");
                Toasty.success(activity_ref.getApplicationContext(), ToastMessageConstants.TOAST_MSG_INFO_USER_LOGIN_SUCCESS,Toast.LENGTH_SHORT).show();
                startNextActivityAfterLogin(auth.getCurrentUser().getUid());
            }
            else {
                Log.i("USER LOGIN 1)",task.getException().toString());
                Log.i("USER LOGIN 2)",task.getException().getLocalizedMessage());
                Toasty.error(activity_ref.getApplicationContext(),getErrorMessage(task.getException()),Toast.LENGTH_SHORT).show();
            }
        });
    }

    /**
     * Yeni uyelik acar. Acilan yeni uyeligi DB de auth kismina ve Real Time DB kismina ekler.
     * AUTH ve real time DB kismi senkronize edilmistir.
     * @param user DB ye yeni eklenecek user referansi.
     * @param temp_password auth kısmına hashlenerek eklenecek şifre
     * @note Bu metod calistiktan sonra user referansi uid degerini elde etmis olur.
     */
    public void createNewUser(User user, String temp_password)
    {
        FirebaseAuth auth = FirebaseAuth.getInstance();
        auth.createUserWithEmailAndPassword(user.getEmail(), temp_password).addOnCompleteListener((OnCompleteListener<AuthResult>) task -> {

            if(task.isSuccessful()) {

                /* get logged in user */
                FirebaseUser created_user = auth.getCurrentUser();
                user.setUid(created_user.getUid());

                /* add to the database */
                FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(created_user.getUid()).setValue(user);

                /* give info msg */
                Toasty.success(activity_ref,ToastMessageConstants.TOAST_MSG_INFO_USER_CREATE_SUCCESS,Toast.LENGTH_SHORT).show();

                /* switch next (login) activity */
                Log.i("USER CREATE", "USER CREATE SUCCEED");
                startNextActivityAfterLogin(created_user.getUid());
            }
            else
            {
                Log.i("USER CREATE ERR 1)",(task.getException()).toString());
                Log.i("USER CREATE ERR 2)",(task.getException()).getLocalizedMessage());
                Toasty.error(activity_ref.getApplicationContext(),getErrorMessage(task.getException()),Toast.LENGTH_SHORT).show();
            }
        });

    }
    /**
     * Kullanici verilerini gunceller.
     * @param user kullanici referansi.
     * @param newuser override edilecek yeni kullanici.
     * @note Bu method calistiktan sonra, newuser referansi uid degeri kazanacaktir.
     */
    public void updateUserProperties(User user, User newuser)
    {
        user.setCreditbalance(newuser.getCreditbalance());
        user.setPhone(newuser.getPhone());

        /* find user by uid */
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(user.getUid());

        /* update in the db */
        ref.setValue(user);
    }

    /**
     * Kullanicinin telefon numarasını gunceller.
     * @param user kullanici referansi.
     * @param phone güncellenecek telefon numarası.
     */
    public void updatePhone(User user, String phone){
        user.setPhone(phone);
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(user.getUid());
        ref.setValue(user);
    }

    /**
     * Kullanicinin borcunu gunceller.
     * @param user kullanici referansi.
     * @param debt güncel borc.
     * @param banned banlı olup olmadığı bilgisi.
     */
    public void updateDebt(User user, double debt, boolean banned){
        user.setDebt(debt);
        user.setBanned(banned);
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(user.getUid());
        ref.setValue(user);
    }

    /**
     * Kullanicinin bakiyesini gunceller.
     * @param user kullanici referansi.
     * @param balance güncel bakiye.
     */
    public void updateBalance(User user, double balance){
        user.setCreditbalance(balance);
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(user.getUid());
        ref.setValue(user);
    }

    /**
     * TODO Şifre güncelleme update edilecek -Ozan
     * @param currentUser, mevcut user
     * @param newPassword, yeni şifresi
     */
    public void updatePassword(User currentUser, String newPassword) {

    }

    public void startNextActivityAfterLogin(String fbuser_uid)
    {
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(activity_ref);

        if(!sp.getBoolean("logged",false)) {
            SharedPreferences.Editor editor = sp.edit();
            editor.putBoolean("logged", true);
            editor.commit();

            editor.putString("user_uid",fbuser_uid);
            editor.commit();
        }
        /* get User by FirebaseUser with uid */
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(DB_USER_FIELD).child(fbuser_uid);

        /* get logged in user for ONCE */
        ref.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                User getted_user = new User(snapshot);
                System.out.println("1) user getted : " + getted_user);

                if(getted_user.getCarparkid().equals(User.NOT_PARKED)) {
                    /* create new intent and start new activity */
                    Intent intent = new Intent(activity_ref, MapsActivity.class);
                    intent.putExtra("CURRENT_USER",getted_user);
                    activity_ref.startActivity(intent);
                    activity_ref.finish();
                } else {
                    String carparkid = getted_user.getCarparkid();
                    String carpark = carparkid.substring(0,carparkid.indexOf("-"));
                    String id = carparkid.substring(carparkid.indexOf("-")+1, carparkid.length());
                    DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child(FirebaseDBConstants.DB_CARPARK_FIELD).child(carpark).child(id);

                    /* get logged in user for ONCE */
                    ref.addListenerForSingleValueEvent(new ValueEventListener() {
                        @Override
                        public void onDataChange(@NonNull DataSnapshot snapshot) {
                            CarPark getted_carpark = new CarPark(snapshot);
                            System.out.println("1) user carpark : " + getted_carpark);

                            Intent intent = new Intent(activity_ref, ParkingInformationActivity.class);
                            intent.putExtra("CURRENT_USER", getted_user);
                            intent.putExtra("CARPARK", getted_carpark);
                            activity_ref.startActivity(intent);
                            activity_ref.finish();
                        }

                        @Override
                        public void onCancelled(@NonNull DatabaseError error) {

                        }
                    });
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }

    private String getErrorMessage(Exception ex)
    {
        if (ex instanceof FirebaseAuthInvalidCredentialsException || ex instanceof FirebaseAuthInvalidUserException)
            return ToastMessageConstants.TOAST_MSG_ERROR_INVALID_CREDTS;
        else if(ex instanceof FirebaseNetworkException)
            return ToastMessageConstants.TOAST_MSG_ERROR_NO_CONNECTION;
        else if(ex instanceof FirebaseAuthWeakPasswordException)
            return ToastMessageConstants.TOAST_MSG_ERROR_WEAK_PASSWORD;
        else if(ex.getLocalizedMessage().equals("An internal error has occurred. [ Unable to resolve host \"www.googleapis.com\":No address associated with hostname ]"))
            return ToastMessageConstants.TOAST_MSG_ERROR_NO_CONNECTION;
        else
            return ToastMessageConstants.TOAST_MSG_ERROR_FATAL;

    }
}