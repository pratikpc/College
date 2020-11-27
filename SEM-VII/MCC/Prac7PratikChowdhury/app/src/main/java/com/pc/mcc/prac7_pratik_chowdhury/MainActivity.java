package com.pc.mcc.prac7_pratik_chowdhury;

import android.content.Intent;
import android.os.Bundle;
import android.util.Pair;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    EditText e1, e2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        // defining the edit text 1 to e1
        e1 = (EditText) findViewById(R.id.num1);
        // defining the edit text 2 to e2
        e2 = (EditText) findViewById(R.id.num2);
    }

    // a public method to get the input numbers
    public Pair<Double, Double> getNumbers() {

        // taking input from text box 1
        String s1 = e1.getText().toString();

        // taking input from text box 2
        String s2 = e2.getText().toString();

        // condition to check if box is not empty
        if ((s1 == null || s2 == null)
                || (s1.equals("") && s2.equals(""))) {
            Toast.makeText(getApplicationContext(), "Please enter the value", Toast.LENGTH_LONG);
            return null;
        }
        Double num1 = Double.parseDouble(s1);
        Double num2 = Double.parseDouble(s2);
        return new Pair(num1, num2);
    }

    // a public method to perform addition
    public void doSum(View v) {
        // get the input numbers
        Pair<Double, Double> values = getNumbers();
        if (values != null) {
            double sum = values.first + values.second;
            SendResult(v, sum);
        }
    }

    // a public method to perform power function
    public void doPow(View v) {
        // get the input numbers
        Pair<Double, Double> values = getNumbers();
        if (values != null) {
            double pow = Math.pow(values.first, values.second);
            SendResult(v, pow);
        }
    }

    // a public method to perform subtraction
    public void doSub(View v) {
        // get the input numbers
        Pair<Double, Double> values = getNumbers();
        if (values != null) {
            double sub = values.first - values.second;
            SendResult(v, sub);
        }
    }

    // a public method to perform multiplication
    public void doMul(View v) {
        // get the input numbers
        Pair<Double, Double> values = getNumbers();
        if (values != null) {
            double mul = values.first * values.second;
            SendResult(v, mul);
        }
    }

    // a public method to perform Division
    public void doDiv(View v) {
        // get the input numbers
        Pair<Double, Double> values = getNumbers();
        if (values != null) {
            double div = values.first / values.second;
            SendResult(v, div);
        }
    }

    private void SendResult(View v, Double val) {
        Intent intent = new Intent(v.getContext(), Results.class);
        intent.putExtra("result", val);
        startActivity(intent);
    }

}