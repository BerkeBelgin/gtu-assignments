package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import androidx.appcompat.widget.Toolbar;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.rule.ActivityTestRule;

import com.example.xpark.DataBaseProvider.FirebaseUserManager;
import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationView;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestRule;
import org.junit.runner.Description;
import org.junit.runners.model.Statement;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.action.ViewActions.scrollTo;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static org.junit.Assert.assertNotNull;

public class MapsActivityTest
{
    static Intent intent;
    static {
        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), MapsActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        intent.putExtras(bundle);
    }
    @Rule
    public ActivityScenarioRule<MapsActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<MapsActivity> myMapsActivity = null;

    @Before
    public void setUp() throws Exception {
        myMapsActivity = activityScenarioRule.getScenario();
    }

    @Test
    public void espressoTest(){
        try{
            onView(withId(R.id.button_res)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_search)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_res)).check(matches(isDisplayed()));
            onView(withId(R.id.button_search)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myMapsActivity = null;
    }
}
