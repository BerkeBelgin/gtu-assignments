package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import com.craftman.cardform.CardForm;
import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.Module.User;
import com.example.xpark.R;

public class PaymentActivity extends AppCompatActivity {

    private User currentUser;
    private Double amount;
    private TextView textValue;
    private Button buttonPay;
    private CardForm card;
    private FirebaseUserManager fbUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_payment);

        getSupportActionBar().setDisplayShowTitleEnabled(false);
        getSupportActionBar().setHomeButtonEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        fbUser = new FirebaseUserManager(this);

        init_extras();
        init_ui();
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }

    @Override
    public void onBackPressed() {finish();}

    private void init_ui() {
        card = findViewById(R.id.cardForm);
        textValue = findViewById(R.id.payment_amount);
        buttonPay = findViewById(R.id.btn_pay);
        buttonPay.setText("PAY");

        textValue.setText(amount.toString());

        buttonPay.setOnClickListener(v ->{
            Intent intent;
            if(currentUser.getBanned()){
                double debt = currentUser.getDebt();
                if(debt <= amount){
                    fbUser.updateDebt(currentUser,0.0,false);
                    fbUser.updateBalance(currentUser, amount - debt);
                }
                else
                    fbUser.updateDebt(currentUser, debt - amount, true);
                System.out.println("BANNED PAYMENT DONE");
                intent = new Intent(this, MapsActivity.class);
                intent.putExtra("CURRENT_USER",currentUser);
                this.startActivity(intent);
            }
            else{
                fbUser.updateBalance(currentUser,currentUser.getCreditbalance() + amount);
                System.out.println("PAYMENT DONE");
                intent = new Intent(this, BalanceActivity.class);
                intent.putExtra("CURRENT_USER",currentUser);
                setResult(Activity.RESULT_OK,intent);
            }
            finish();
        });
    }

    private void init_extras() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        amount = intent.getDoubleExtra("AMOUNT",0);
        System.out.println("USER GETTED : " + currentUser + "\nAMOUNT GETTED : " + amount);
    }
}