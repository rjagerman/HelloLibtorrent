#!/bin/bash
echo "Uninstalling the app"
adb shell pm uninstall com.example.hellolibtorrent

echo "Installing the app"
adb install bin/HelloLibtorrent-debug.apk
