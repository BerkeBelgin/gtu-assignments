package com.example.xpark.Activities;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import com.example.xpark.R;
import com.example.xpark.Utils.ToastMessageConstants;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;

import es.dmoral.toasty.Toasty;

public class ForgotPasswordActivity extends AppCompatActivity {
    private EditText resetMail;
    private Button sendLink;
    private FirebaseAuth fAuth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getSupportActionBar().setDisplayShowTitleEnabled(false);
        getSupportActionBar().setHomeButtonEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        setContentView(R.layout.activity_forgot_password);

        resetMail = findViewById(R.id.fp_email);
        sendLink = findViewById(R.id.sendLink);
        fAuth = FirebaseAuth.getInstance();

        sendLink_INIT();
        resetMail_INIT();

        sendLink.setEnabled(false);
        sendLink.setClickable(false);
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }

    private void resetMail_INIT(){
        resetMail.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                String mail = resetMail.getText().toString();

                sendLink.setEnabled(!mail.isEmpty());
                sendLink.setClickable(!mail.isEmpty());
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
        });
    }

    private void sendLink_INIT() {
        sendLink.setOnClickListener( v -> {
            final AlertDialog.Builder resetDialog = new AlertDialog.Builder(v.getContext());

            resetDialog.setTitle("Şifre Yenile");
            resetDialog.setMessage("Şifre yenileme için yenileme linki gönder");
            resetDialog.setView(resetMail);

            resetDialog.setPositiveButton("Evet", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialogInterface, int i) {
                    String mail = resetMail.getText().toString();

                    sendLink.setEnabled(mail.isEmpty());
                    sendLink.setClickable(mail.isEmpty());

                    fAuth.sendPasswordResetEmail(mail).addOnSuccessListener(new OnSuccessListener<Void>() {
                        @Override
                        public void onSuccess(Void aVoid) {
                            Toasty.success(ForgotPasswordActivity.this, ToastMessageConstants.TOAST_MSG_VALID_MAIL, Toast.LENGTH_SHORT).show();
                        }
                    }).addOnFailureListener(new OnFailureListener() {
                        @Override
                        public void onFailure(@NonNull Exception e) {
                            Toasty.error(ForgotPasswordActivity.this, ToastMessageConstants.TOAST_MSG_ERROR_INVALID_MAIL, Toast.LENGTH_SHORT).show();
                        }
                    });
                }
            });

            resetDialog.setNegativeButton("Hayır", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialogInterface, int i) {

                }
            });

            resetDialog.create().show();
        });
    }
}
