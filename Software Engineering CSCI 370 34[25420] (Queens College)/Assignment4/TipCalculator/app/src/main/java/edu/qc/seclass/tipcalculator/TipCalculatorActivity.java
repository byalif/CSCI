package edu.qc.seclass.tipcalculator;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class TipCalculatorActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tip_calculator);
    }

    public void displayToast(){
        Toast.makeText(TipCalculatorActivity.this,"Empty or Incorrect Value(s)!",Toast.LENGTH_SHORT).show();
    }

    public void computeTip(View v) {
        //the replaceAll method trims spaces from input in the case of mistakes
        String input1 = ((TextView) findViewById(R.id.checkAmountValue)).getText().toString();
        input1 = input1.replaceAll("\\s+", "");
        String input2 = ((TextView) findViewById(R.id.partySizeValue)).getText().toString();
        input2 = input2.replaceAll("\\s+", "");
        if (input1.equals("") || input2.equals("")) {
            displayToast();
            return;
        }
        //This hides the keyboard after you press the Compute tip button for convenience
        InputMethodManager inputManager = (InputMethodManager) getApplication().getSystemService(Context.INPUT_METHOD_SERVICE);
        inputManager.hideSoftInputFromWindow(getWindow().getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);

        //These loops check for any non integer values in which it will show a pop up error message by making it visible
        for (int i = 0; i < input1.length(); i++) {
            if (!Character.isDigit(input1.charAt(i))) {
                Log.d("failed", "check amount not valid");
                displayToast();
                return;
            }
        }

        for (int i = 0; i < input2.length(); i++) {
            if (!Character.isDigit(input2.charAt(i))) {
                Log.d("failed", "party size not valid");
                displayToast();
                return;
            }
        }

        Double checkAmt = Double.parseDouble(input1);
        Double party = Double.parseDouble(input2);

        if(checkAmt<0 || party<=0){
            inputManager = (InputMethodManager) getApplication().getSystemService(Context.INPUT_METHOD_SERVICE);
            inputManager.hideSoftInputFromWindow(getWindow().getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
            return;
        }


        //Will be using Math.ceil instead of Math.round because in real life you wont be rounding down
        double ttl = Math.ceil(checkAmt / party);



        ((EditText) findViewById(R.id.fifteenPercentTipValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .15) / party)));
        ((EditText) findViewById(R.id.twentyPercentTipValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .20) / party)));
        ((EditText) findViewById(R.id.twentyfivePercentTipValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .25) / party)));

        ((EditText) findViewById(R.id.fifteenPercentTotalValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .15) / party) + (int) ttl));
        ((EditText) findViewById(R.id.twentyPercentTotalValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .20) / party) + (int) ttl));
        ((EditText) findViewById(R.id.twentyfivePercentTotalValue)).setText(Integer.toString((int) Math.ceil((checkAmt * .25) / party) + (int) ttl));

        Log.d("amt", "" + (int) Math.round((checkAmt * .15) / party));
    }

}