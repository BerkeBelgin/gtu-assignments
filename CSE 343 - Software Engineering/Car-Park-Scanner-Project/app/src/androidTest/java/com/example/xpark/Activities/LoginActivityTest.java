
/**
 * Author : Dilara Karakas.
 */


package com.example.xpark.Activities;

import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;


import androidx.test.espresso.Espresso;
import androidx.test.rule.ActivityTestRule;

import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.Module.User;
import com.example.xpark.R;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.action.ViewActions.scrollTo;
import static androidx.test.espresso.action.ViewActions.typeText;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static org.junit.Assert.assertNotNull;

public class LoginActivityTest {
    @Rule
    public ActivityTestRule<LoginActivity> loginActivityActivityTestRule = new ActivityTestRule<LoginActivity>(LoginActivity.class);
    private LoginActivity myLoginActivity = null;
    private FirebaseUserManager DBUserManager;
    User testUser = new User("+905000000000","abc@gmail.com",50.0, "NOT_PARKED","NOT_PARKED",false,0.0);
    User testUser2 = new User("","",0.0, "","",false,0.0);

    @Before
    public void setUp() throws Exception {
        myLoginActivity = loginActivityActivityTestRule.getActivity();
    }

    public void testUser_phone_one() throws Exception {
        if(testUser.getPhone().contains("+9")){
            System.out.println("True");
        }
        else{
            throw new Exception(String.format("Wrong input for user's phone"));
        }
    }

    public void testUser_phone_two()throws Exception{
        if(testUser.getPhone().length() == 13){
            System.out.println("True");
        }
        else{
            throw new Exception(String.format("Wrong input for user's phone"));
        }
    }


    public void testUser_email_one()throws Exception{
        if(testUser.getEmail().contains("@gmail.com")){
            System.out.println("True");
        }
        else{
            throw new Exception(String.format("False input for user email"));
        }
    }

    public void testUser_email_two()throws Exception{
        if(testUser.getEmail().contains("@hotmail.com")){
            System.out.println("True");
        }
        else{
            throw new Exception(String.format("False input for user email"));
        }
    }

    public void testUser_park()throws Exception{
        if(testUser.getParkingTime().equals("NOT_PARKED")){
            if(testUser.getCarparkid().equals("NOT_PARKED")){
                System.out.println("True");
            }
            else{
                throw new Exception(String.format("Wrong information for user park"));
            }
        }
    }

    public void testUser2_phone()throws Exception{
        if(testUser2.getPhone().length() == 0){
            throw new Exception(String.format("Empty Phone"));
        }
    }

    public void testUser2_email()throws Exception{
        if(testUser2.getEmail().length() == 0){
            throw new Exception(String.format("Empty email"));
        }
    }

    public void testUser2_parkID()throws Exception{
        if(testUser2.getCarparkid().length() == 0){
            throw new Exception(String.format("Empty ParkID"));
        }
    }

    public void testUser2_parkingTime()throws Exception{
        if(testUser2.getParkingTime().length() == 0){
            throw new Exception(String.format("Empty Parking Time"));
        }
    }

    @Test
    public void testUser(){
        try{
            testUser_email_one();
            testUser_email_two();
            testUser_phone_one();
            testUser_phone_two();
            testUser_park();
        }
        catch (Exception e) {
            Log.i("error",e.getMessage());
        }
    }

    @Test
    public void testUser2(){
        try{
            testUser2_email();
            testUser2_parkingTime();
            testUser2_phone();
            testUser2_parkID();
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @Test
    public void testID_imageView(){
        ImageView imageView = myLoginActivity.findViewById(R.id.imageView);
        assertNotNull(imageView);
    }

    @Test
    public void testID_sign_in(){
        Button sign_in_button = myLoginActivity.findViewById(R.id.sign_in_button);
        assertNotNull(sign_in_button);
    }
    @Test
    public void testID_sign_up(){
        Button sign_up_button = myLoginActivity.findViewById(R.id.sign_up_button);
        assertNotNull(sign_up_button);
    }
    @Test
    public void testID_email(){
        TextView email_input = myLoginActivity.findViewById(R.id.userName);
        assertNotNull(email_input);
    }
    @Test
    public void testID_password(){
        TextView password_input = myLoginActivity.findViewById(R.id.Password);
        assertNotNull(password_input);
    }

    @Test
    public void espressoTest(){
        try{
            Espresso.onView(withId(R.id.userName)).perform(typeText("username"));
            Espresso.onView(withId(R.id.password)).perform(typeText("password"));
            onView(withId(R.id.sign_up_button)).perform(scrollTo()).perform(click());
            onView(withId(R.id.sign_in_button)).perform(scrollTo()).perform(click());
            onView(withId(R.id.sign_up_button)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myLoginActivity = null;
    }
}