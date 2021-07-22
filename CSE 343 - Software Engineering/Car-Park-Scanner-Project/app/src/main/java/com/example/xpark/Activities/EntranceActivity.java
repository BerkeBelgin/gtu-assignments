package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.R;

public class EntranceActivity extends AppCompatActivity {

    private FirebaseUserManager FBUserManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_entrance);

        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);

        FBUserManager = new FirebaseUserManager(this);

        getSupportActionBar().setDisplayShowTitleEnabled(false);
        
        if(sp.getBoolean("logged",false)){
            String user_uid = sp.getString("user_uid","");
            FBUserManager.startNextActivityAfterLogin(user_uid);
        } else{
            Handler handler = new Handler();
            handler.postDelayed(() -> {
                Intent intent = new Intent(this, LoginActivity.class);
                this.startActivity(intent);
                this.finish();
            }, 2000);
        }
    }
}