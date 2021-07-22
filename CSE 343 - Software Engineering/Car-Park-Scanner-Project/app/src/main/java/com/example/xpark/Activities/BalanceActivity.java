package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.example.xpark.Utils.ToastMessageConstants;
import es.dmoral.toasty.Toasty;

public class BalanceActivity extends AppCompatActivity {

    private User currentUser;
    private Button nextButton;
    private EditText textAmount;
    private TextView textBalance;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_balance);

        getSupportActionBar().setTitle("Bakiye Yükle");
        getSupportActionBar().setHomeButtonEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        init_logged_user();
        init_ui();
    }

    @Override
    public boolean onSupportNavigateUp() {
        Intent intent = new Intent();
        intent.putExtra("CURRENT_USER",currentUser);
        setResult(Activity.RESULT_OK,intent);
        finish();
        return true;
    }

    @Override
    public void onBackPressed() {
        Intent intent = new Intent();
        intent.putExtra("CURRENT_USER",currentUser);
        setResult(Activity.RESULT_OK,intent);
        finish();
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

        String msg = "BAKİYE: " + currentUser.getCreditbalance() + "₺";
        textBalance.setText(msg);
    }

    private void init_ui(){
        nextButton = findViewById(R.id.button_next);
        textAmount = findViewById(R.id.text_amount);
        textBalance = findViewById(R.id.text_balance);

        String msg = "BAKİYE: " + currentUser.getCreditbalance() + "₺";
        textBalance.setText(msg);

        nextButton.setEnabled(false);
        nextButton.setClickable(false);

        textAmount.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isAmountNotEmpty = !textAmount.getText().toString().isEmpty();

                nextButton.setEnabled(isAmountNotEmpty);
                nextButton.setClickable(isAmountNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });

        nextButton.setOnClickListener(v -> {
            String strAmount = textAmount.getText().toString();

            if(TextUtils.isDigitsOnly(strAmount)){
                int LAUNCH_SECOND_ACTIVITY = 1;
                double amount = Double.parseDouble(strAmount);
                Intent intent = new Intent(this, PaymentActivity.class);
                intent.putExtra("CURRENT_USER",currentUser);
                intent.putExtra("AMOUNT",amount);
                this.startActivityForResult(intent,LAUNCH_SECOND_ACTIVITY);
            }
            else{
                Toasty.error(this.getApplicationContext(), ToastMessageConstants.TOAST_MSG_ERROR_INVALID_AMOUNT, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void init_logged_user() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        System.out.println("USER GETTED : " + currentUser);
    }
}