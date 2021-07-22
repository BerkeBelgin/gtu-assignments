package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.espresso.Espresso;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.rule.ActivityTestRule;

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
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static org.junit.Assert.*;

public class ProfileActivityTest {
    static Intent intent;
    static {
        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), ProfileActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        intent.putExtras(bundle);
    }

    @Rule
    public ActivityScenarioRule<ProfileActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<ProfileActivity> myProfileActivity = null;

    @Before
    public void setUp() throws Exception {
        myProfileActivity = activityScenarioRule.getScenario();
    }

    /*@Test
    public void scenario(){
        myProfileActivity.getResult();
    }*/


    @Test
    public void espressoTest_Text(){
        try{
            Espresso.onView(withId(R.id.text_email)).perform(typeText("text_email"));
            Espresso.onView(withId(R.id.text_phone)).perform(typeText("text_phone"));
            Espresso.onView(withId(R.id.text_edit_phone)).perform(typeText("text_edit_phone"));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @Test
    public void espressoTest_Button(){
        try{
            onView(withId(R.id.button_phone)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_update)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_phone)).check(matches(isDisplayed()));
            onView(withId(R.id.button_update)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myProfileActivity = null;
    }
}