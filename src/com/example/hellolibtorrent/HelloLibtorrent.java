/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.hellolibtorrent;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;

public class HelloLibtorrent extends Activity
{
    /**
     * The output TextView that we print to
     */
    private TextView output;

    /**
     * The total text in the output text view, to easily append to
     */
    private String currentText = "";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        // Create vertical layout
        LinearLayout ll = new LinearLayout(this);
        ll.setOrientation(LinearLayout.VERTICAL);

        // Create button
        final Button b = new Button(this);
        b.setText("Start");
        ll.addView(b);

        // Create text area (with scroll)
        ScrollView sv = new ScrollView(this);
        output = new TextView(this);
        sv.addView(output);
        ll.addView(sv);

        // Set vertical layout as main view
        this.setContentView(ll);

        // Get the torrent to download and print it
        appendToOutput("We are going to download:\n  " + whichTorrent(), true);    

        // Start session
        appendToOutput(startSession(), true);

        // Open torrent file
        appendToOutput(openTorrent(), true);    

        // On click, print the current progress of the download to the output
        b.setOnClickListener(new OnClickListener() {
            private boolean started = false;
            @Override
            public void onClick(View v) {
                if(!started) {

                    // Start the download and print the status
                    appendToOutput(startDownload(), true);

                    // Set a schedule for getting progress updates
                    new Timer().scheduleAtFixedRate(new TimerTask() {
                        private int updates = 0;
                        @Override
                        public void run() {
                            updates++;
                            final String status = status();
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    appendToOutput("Update #" + updates + "\n" + status, false);
                                }
                            });
                        }
                    }, 0, 3);

                    // Ensure this function doesn't get called again
                    started = true;
                    b.setText("Downloading...");
                    b.setEnabled(false);
                }
            }
        });
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(1500);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            b.performClick();
                        }
                    });
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
        
    }

    /* Appends given text to the output TextView. 
     */
    public void appendToOutput(String text, boolean addPermanently) {
        if (addPermanently) {
            currentText += text + "\n\n";
            output.setText(currentText);
        } else {
            output.setText(currentText + text);
        }
    }

    /* A native method that tells us which torrent file we are going to download
     */
    public native String  whichTorrent();

    /* A native method that starts the download of the hardcoded torrent
     */
    public native String startSession();

    /* A native method that starts the download of the hardcoded torrent
     */
    public native String openTorrent();

    /* A native method that starts the download of the hardcoded torrent
     */
    public native String startDownload();

    /* A native method that returns the status of the torrent download
     */
    public native String status();

    /* Which libraries to include and their dependencies
     * Note that the order is very important. Place libraries that are not dependent
     * on anything first, and only place dependen libraries after the dependencies have
     * already been included. 
     */
    static {
	    System.loadLibrary("torrent-rasterbar");
        System.loadLibrary("hello");
    }
}
