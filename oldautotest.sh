#!/bin/bash

# Set variables
APPNAME="com.example.hellolibtorrent"
ACTIVITY="HelloLibtorrent"

# Uninstall the app
adb shell pm uninstall $APPNAME

# Install the app
adb install bin/HelloLibtorrent-debug.apk

# Start logging the output
adb logcat -c
adb logcat > 'autotest.log' &

# Run the application
adb shell am start -n ${APPNAME}/${APPNAME}.${ACTIVITY}

# Wait for 2 minutes


# Close the application
 adb shell am force-stop com.example.hellolibtorrent