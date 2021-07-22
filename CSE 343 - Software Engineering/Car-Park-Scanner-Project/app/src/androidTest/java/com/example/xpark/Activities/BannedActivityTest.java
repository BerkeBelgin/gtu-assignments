package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.espresso.Espresso;
import androidx.test.ext.junit.rules.ActivityScenarioRule;

import com.example.xpark.Module.CarPark;
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

public class BannedActivityTest {

    static Intent intent;

    static {
        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), BannedActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        intent.putExtras(bundle);
    }

    @Rule
    public ActivityScenarioRule<BannedActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<BannedActivity> myBannedActivity = null;

    @Before
    public void setUp() throws Exception {
        myBannedActivity = activityScenarioRule.getScenario();
    }

    /*@Test
    public void scenario(){
        myBannedActivity.getResult();
    }*/

    @Test
    public void espressoTest(){
        try{
            Espresso.onView(withId(R.id.debt)).perform(typeText("BANNED"));
            onView(withId(R.id.toPayment)).perform(scrollTo()).perform(click());
            onView(withId(R.id.toPayment)).check(matches(isDisplayed()));
            onView(withId(R.id.debt)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myBannedActivity = null;
    }
}