package com.pc.mcc.prac7_pratik_chowdhury;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class Results extends AppCompatActivity {
    private TextView result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_results);

        // defining the text view to t1
        result = (TextView) findViewById(R.id.result);

        // get the text from MainActivity
        Intent intent = getIntent();
        double val = intent.getDoubleExtra("result", 0.0);
        result.setText(String.valueOf(val));
    }
}