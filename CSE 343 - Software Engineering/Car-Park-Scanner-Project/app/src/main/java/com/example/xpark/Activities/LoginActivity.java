package com.example.xpark.Activities;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.R;
import com.example.xpark.Utils.ToastMessageConstants;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import es.dmoral.toasty.Toasty;


public class LoginActivity extends AppCompatActivity {

    private DatabaseReference ref;
    private Button sign_in_button;
    private Button sign_up_button;
    private FirebaseUserManager DBUserManager;
    private EditText email_input;
    private EditText password_input;
    private TextView forgotPw;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        getSupportActionBar().setDisplayShowTitleEnabled(false);

        super.onCreate(savedInstanceState);

        // kritik
        if ((getIntent().getFlags() & Intent.FLAG_ACTIVITY_BROUGHT_TO_FRONT) != 0) {
            // Activity was brought to front and not created,
            // Thus finishing this will get us to the last viewed activity
            finish();
            return;
        }

        /* initialize UI components */
        UI_init();
        DB_init();

    }

    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
    }



    /**
     * Initialize ui components.
     */
    private void UI_init() {
        setContentView(R.layout.activity_login);

        sign_in_button = findViewById(R.id.sign_in_button);
        sign_up_button = findViewById(R.id.sign_up_button);
        email_input = findViewById(R.id.userName);
        password_input = findViewById(R.id.Password);
        forgotPw = findViewById(R.id.forgotPw);

        sign_in_button.setEnabled(false);
        sign_in_button.setClickable(false);

        email_input.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isMailNotEmpty = !email_input.getText().toString().isEmpty();
                boolean isPasswordNotEmpty = !password_input.getText().toString().isEmpty();

                sign_in_button.setEnabled(isMailNotEmpty && isPasswordNotEmpty);
                sign_in_button.setClickable(isMailNotEmpty && isPasswordNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });

        password_input.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                boolean isMailNotEmpty = !email_input.getText().toString().isEmpty();
                boolean isPasswordNotEmpty = !password_input.getText().toString().isEmpty();

                sign_in_button.setEnabled(isMailNotEmpty && isPasswordNotEmpty);
                sign_in_button.setClickable(isMailNotEmpty && isPasswordNotEmpty);
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });

        forgotPw.setOnClickListener(v -> {
            Intent intent = new Intent(this, ForgotPasswordActivity.class);
            this.startActivity(intent);
        });

        /* oturum ac listener baslat */
        sign_in_button.setOnClickListener(v -> {
            DBUserManager.signInUser(email_input.getText().toString(), password_input.getText().toString());
        });

        /* yeni uyelik ac listener baslat */
        sign_up_button.setOnClickListener(v -> {
            Intent intent = new Intent(this, SignUpActivity.class);
            this.startActivity(intent);
        });
    }

    /**
     * Initialize DB managers & handle connection issues.
     */
    private void DB_init() {
        /* get database reference */
        ref = FirebaseDatabase.getInstance().getReference();

        /* initialize FireBaseUserManager */
        DBUserManager = new FirebaseUserManager(this);

        // deneme, mainactivityde sonra kullanilacak..
        /*
         // Sadece users icin dinleme threadi olustur
        ref.child("Users").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
               Log.i("listener","listener Calisti..");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
         */
    }
    protected void onResume() {
        super.onResume();
    }
    @Override
    public void onBackPressed() {
        /* ignore it */
    }
}
