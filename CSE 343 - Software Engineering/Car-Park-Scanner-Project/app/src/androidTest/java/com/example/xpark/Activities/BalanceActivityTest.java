package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;

import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.rule.ActivityTestRule;

import com.example.xpark.BuildConfig;
import com.example.xpark.Module.User;
import com.example.xpark.R;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.action.ViewActions.scrollTo;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static org.junit.Assert.*;

public class BalanceActivityTest {
    static Intent intent;
    static {
        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), BalanceActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        intent.putExtras(bundle);
    }

    @Rule
    //public ActivityTestRule<BalanceActivity> balanceActivityActivityTestRule = new ActivityTestRule<BalanceActivity>(BalanceActivity.class);
    //private BalanceActivity myBalancedActivity = null;
    public ActivityScenarioRule<BalanceActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<BalanceActivity> myBalancedActivity = null;

    @Before
    public void setUp() throws Exception {
        myBalancedActivity = activityScenarioRule.getScenario();
    }

    @Test
    public void espressoTest(){
        try{
            onView(withId(R.id.button_next)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_next)).check(matches(isDisplayed()));
            onView(withId(R.id.text_amount)).check(matches(isDisplayed()));
            onView(withId(R.id.text_balance)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myBalancedActivity = null;
    }
}