package com.example.xpark.Activities;

import androidx.annotation.VisibleForTesting;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.xpark.Module.User;
import com.example.xpark.R;

public class BannedActivity extends AppCompatActivity {

    private User currentUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_banned);

        TextView debt = findViewById(R.id.debt);
        Button toPayment = findViewById(R.id.toPayment);


        debt.setVisibility(View.INVISIBLE);

        toPayment.setOnClickListener(view -> {
            Intent intent = new Intent(getApplicationContext(), BalanceActivity.class);
            intent.putExtra("CURRENT_USER", currentUser);
            this.startActivity(intent);
            finish();
        });

        init_logged_user();

        String DEBT = currentUser.getDebt() + " ₺";
        debt.setText(DEBT);
        debt.setVisibility(View.VISIBLE);
    }

    @Override
    public void onBackPressed() {}

    @VisibleForTesting
    private void init_logged_user() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        System.out.println("USER GETTED : " + currentUser);
    }
}