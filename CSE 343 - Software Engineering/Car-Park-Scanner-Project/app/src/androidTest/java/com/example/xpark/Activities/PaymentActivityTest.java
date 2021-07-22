package com.example.xpark.Activities;

import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import androidx.test.espresso.Espresso;
import androidx.test.rule.ActivityTestRule;

import com.craftman.cardform.CardForm;
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

public class PaymentActivityTest {
    @Rule
    public ActivityTestRule<PaymentActivity> paymentActivityActivityTestRule = new ActivityTestRule<PaymentActivity>(PaymentActivity.class);
    private PaymentActivity myPaymentActivity = null;

    @Before
    public void setUp() throws Exception {
        myPaymentActivity = paymentActivityActivityTestRule.getActivity();
    }

    @Test
    public void testID_textValue(){
        TextView textValue = myPaymentActivity.findViewById(R.id.payment_amount);
        assertNotNull(textValue);
    }

    @Test
    public void testID_buttonPay(){
        Button buttonPay = myPaymentActivity.findViewById(R.id.btn_pay);
        assertNotNull(buttonPay);
    }

    @Test
    public void testID_card(){
        CardForm card = myPaymentActivity.findViewById(R.id.cardForm);
        assertNotNull(card);
    }

    @Test
    public void espressoTest(){
        try{
            Espresso.onView(withId(R.id.payment_amount)).perform(typeText("payment"));
            onView(withId(R.id.btn_pay)).perform(scrollTo()).perform(click());
            onView(withId(R.id.btn_pay)).check(matches(isDisplayed()));
            onView(withId(R.id.cardForm)).check(matches(isDisplayed()));
        }
        catch (Exception e){
            Log.i("error",e.getMessage());
        }
    }

    @After
    public void tearDown() throws Exception {
        myPaymentActivity = null;
    }
}