/*
 * Simple example of a torrent client on android
 */
package com.example.hellolibtorrent;

import java.util.Timer;
import java.util.TimerTask;
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.ScrollView;

public class HelloLibtorrent extends Activity {

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Create text area with scroll
        final TextView textView = new TextView(this);
        ScrollView scrollView = new ScrollView(this);
        scrollView.addView(textView);
        this.setContentView(scrollView);

        // Start torrent and output torrent name to screen
        String torrent_name = startTorrent();
        textView.setText(torrent_name);

        // Get updates at a regular interval and print them to the screen
        new Timer().scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        String status = getStatus();
                        textView.setText(status);
                        System.out.println(status);
                    }
                });
            }
        }, 0, 5);


    }

    /* A native method that tells us which torrent file we are going to download
     */
    public native String  startTorrent();

    /* A native method that starts the download of the hardcoded torrent
     */
    public native String getStatus();

    /* Which libraries to include and their dependencies
     * Note that the order is very important. Place libraries that are not dependent
     * on anything first, and only place dependent libraries after the dependencies have
     * already been included. 
     */
    static {
	    System.loadLibrary("torrent-rasterbar");
        System.loadLibrary("hello");
    }
}
