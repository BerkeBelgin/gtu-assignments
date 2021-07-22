package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.google.zxing.Result;

import me.dm7.barcodescanner.zxing.ZXingScannerView;

public class ScanCodeActivity extends AppCompatActivity implements ZXingScannerView.ResultHandler {
    private ZXingScannerView Scanner;
    private User currentUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Scanner = new ZXingScannerView(this);
        setContentView(Scanner);
        ParkingInformationActivity.isScanned = true;
    }

    @Override
    public void handleResult(Result result){
        ParkingInformationActivity.park_id = (result.getText());
        init_logged_user();
        Intent intent = new Intent(getApplicationContext(), ParkingInformationActivity.class);
        intent.putExtra("CURRENT_USER", currentUser);
        startActivity(intent);
        finish();
        onBackPressed();
    }

    @Override
    protected void onPause(){
        super.onPause();
        Scanner.stopCamera();
    }

    @Override
    protected void onResume(){
        super.onResume();
        Scanner.setResultHandler(this);
        Scanner.startCamera();
    }

    private void init_logged_user() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        System.out.println("USER GETTED : " + currentUser);
    }
}