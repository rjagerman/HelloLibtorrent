#!/bin/bash
procid=`adb shell ps | grep "hellolibtorrent" | awk '{print $2}'`;
echo "${procid}"
adb logcat -c
adb logcat | grep "${procid})"
