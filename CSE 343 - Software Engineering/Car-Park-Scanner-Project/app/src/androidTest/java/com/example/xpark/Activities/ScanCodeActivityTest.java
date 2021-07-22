package com.example.xpark.Activities;

import android.content.Intent;
import android.os.Bundle;

import androidx.test.core.app.ActivityScenario;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.rule.ActivityTestRule;

import com.example.xpark.Module.User;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import static androidx.test.espresso.Espresso.pressBack;

public class ScanCodeActivityTest {
    static Intent intent;
    static {
        User testUser = new User("05345212020","abcd4@gmail.com",100.0, "NOT_PARKED","NOT_PARKED",false,0.0);
        intent = new Intent(ApplicationProvider.getApplicationContext(), ScanCodeActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("CURRENT_USER",testUser);
        intent.putExtras(bundle);
    }

    @Rule
    public ActivityScenarioRule<ScanCodeActivity> activityScenarioRule = new ActivityScenarioRule<>(intent);
    public ActivityScenario<ScanCodeActivity> myScanCodeActivity = null;
    ActivityTestRule<ScanCodeActivity> rule;

    @Before
    public void setUp() throws Exception {
        myScanCodeActivity = activityScenarioRule.getScenario();
    }

    @Test
    public void shouldRenderView() throws Exception {
        rule.launchActivity(new Intent(ApplicationProvider.getApplicationContext(), ScanCodeActivity.class));
        pressBack();
        Thread.sleep(5000);
    }

    /*@Test
    public void scenario(){
        myScanCodeActivity.getResult();
    }*/

    @After
    public void tearDown() throws Exception {
        myScanCodeActivity = null;
    }
}