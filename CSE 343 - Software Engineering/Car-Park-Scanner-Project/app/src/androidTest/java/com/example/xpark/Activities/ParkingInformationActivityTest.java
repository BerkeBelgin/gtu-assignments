package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.widget.Toolbar;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.espresso.Espresso;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.rule.ActivityTestRule;

import com.craftman.cardform.CardForm;
import com.example.xpark.Module.CarPark;
import com.example.xpark.Module.User;
import com.example.xpark.R;
import com.google.android.material.navigation.NavigationView;

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

public class ParkingInformationActivityTest {
    static Intent intent;

    static {
        CarPark car = new CarPark("1000000","34734_Kadıköy_İstanbul-1000000","Dilara","05000000000",50,10);

        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), ParkingInformationActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        bundle.putSerializable("CARPARK",car);
        intent.putExtras(bundle);
    }

    @Rule
    public ActivityScenarioRule<ParkingInformationActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<ParkingInformationActivity> myParkingInformationActivity = null;

    @Before
    public void setUp() throws Exception {
        myParkingInformationActivity = activityScenarioRule.getScenario();
    }

    @Test
    public void espressoTest(){
        try{
            Espresso.onView(withId(R.id.text_time)).perform(typeText("text_time"));
            onView(withId(R.id.QrScanner)).perform(scrollTo()).perform(click());
            onView(withId(R.id.button_finish)).perform(scrollTo()).perform(click());
            onView(withId(R.id.QrScanner)).check(matches(isDisplayed()));
            onView(withId(R.id.button_finish)).check(matches(isDisplayed()));
            onView(withId(R.id.nav_view2)).check(matches(isDisplayed()));
            onView(withId(R.id.drawer_layout_2)).check(matches(isDisplayed()));
            onView(withId(R.id.toolbar2)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myParkingInformationActivity = null;
    }
}