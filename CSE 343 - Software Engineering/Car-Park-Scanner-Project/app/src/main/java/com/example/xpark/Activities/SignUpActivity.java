package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.R;
import com.example.xpark.Module.User;
import com.example.xpark.Utils.ToastMessageConstants;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import es.dmoral.toasty.Toasty;

public class SignUpActivity extends AppCompatActivity {

    private FirebaseAuth fb;
    private DatabaseReference ref;
    private FirebaseUserManager DBUserManager;
    private EditText email_field;
    private EditText phone_field;
    private EditText password_field;
    private Button signUp_button;

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);

        getSupportActionBar().setDisplayShowTitleEnabled(false);
        getSupportActionBar().setHomeButtonEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        signUp_button = findViewById(R.id.button_signup);

        ref = FirebaseDatabase.getInstance().getReference();
        DBUserManager = new FirebaseUserManager(this);

        signUp_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String phone = ((TextView) findViewById(R.id.phone)).getText().toString();
                String email = ((TextView) findViewById(R.id.Email)).getText().toString();

                if(TextUtils.isDigitsOnly(phone) && phone.length() == 11){
                    User test_user = new User(phone,email);
                    String temp_password = ((TextView) findViewById(R.id.password)).getText().toString();

                    System.out.println("USER CREATING : " + test_user);
                    DBUserManager.createNewUser(test_user, temp_password);
                }
                else{
                    Toasty.error(getApplicationContext(), ToastMessageConstants.TOAST_MSG_ERROR_INVALID_CREDTS, Toast.LENGTH_SHORT).show();
                }
            }
        });

        signUp_button.setEnabled(false);
        signUp_button.setClickable(false);

        email_field = findViewById(R.id.Email);
        phone_field = findViewById(R.id.phone);
        password_field = findViewById(R.id.password);

        email_field.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isMailNotEmpty = !email_field.getText().toString().isEmpty();
                boolean isPhoneNotEmpty = !phone_field.getText().toString().isEmpty();
                boolean isPasswordNotEmpty = !password_field.getText().toString().isEmpty();

                signUp_button.setEnabled(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
                signUp_button.setClickable(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });

        phone_field.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isMailNotEmpty = !email_field.getText().toString().isEmpty();
                boolean isPhoneNotEmpty = !phone_field.getText().toString().isEmpty();
                boolean isPasswordNotEmpty = !password_field.getText().toString().isEmpty();

                signUp_button.setEnabled(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
                signUp_button.setClickable(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });

        password_field.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isMailNotEmpty = !email_field.getText().toString().isEmpty();
                boolean isPhoneNotEmpty = !phone_field.getText().toString().isEmpty();
                boolean isPasswordNotEmpty = !password_field.getText().toString().isEmpty();

                signUp_button.setEnabled(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
                signUp_button.setClickable(isMailNotEmpty && isPhoneNotEmpty && isPasswordNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });
    }
}