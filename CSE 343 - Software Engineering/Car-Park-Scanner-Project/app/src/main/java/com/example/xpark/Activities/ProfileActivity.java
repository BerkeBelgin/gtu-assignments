package com.example.xpark.Activities;

import androidx.appcompat.app.AppCompatActivity;
import android.app.Activity;
import android.content.Intent;
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
import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.example.xpark.Utils.ToastMessageConstants;
import es.dmoral.toasty.Toasty;

public class ProfileActivity extends AppCompatActivity {

    private User currentUser;
    private TextView textEmail;
    private EditText textEditPhone;
    private Button bUpdate;
    private FirebaseUserManager fbUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        getSupportActionBar().setTitle("Profil");
        getSupportActionBar().setHomeButtonEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        fbUser = new FirebaseUserManager(this);

        init_logged_user();
        init_uit();
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

    private void init_uit(){
        textEmail = findViewById(R.id.text_email);
        textEditPhone = findViewById(R.id.text_edit_phone);
        bUpdate = findViewById(R.id.button_update);

        textEmail.setText("E-POSTA: " + currentUser.getEmail());
        textEditPhone.setText(currentUser.getPhone());

        bUpdate.setOnClickListener(v ->{
            String newPhone = textEditPhone.getText().toString();
            if(TextUtils.isDigitsOnly(newPhone) && newPhone.length() == 11){
                fbUser.updatePhone(currentUser,newPhone);
                this.recreate();
            }
            else{
                Toasty.error(this.getApplicationContext(), ToastMessageConstants.TOAST_MSG_ERROR_INVALID_PHONE, Toast.LENGTH_SHORT).show();
            }
        });

        bUpdate.setEnabled(false);
        bUpdate.setClickable(false);

        textEditPhone.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isPhoneChanged = !textEditPhone.getText().toString().equals(currentUser.getPhone());

                bUpdate.setEnabled(isPhoneChanged);
                bUpdate.setClickable(isPhoneChanged);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });
    }

    private void init_logged_user() {
        Intent intent = getIntent();
        currentUser = (User) intent.getSerializableExtra("CURRENT_USER");
        System.out.println("USER GETTED : " + currentUser);
    }
}