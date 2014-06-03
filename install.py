#!/usr/bin/env python

from __future__ import print_function
from subprocess import Popen, PIPE
from time import time, sleep
from sys import stdout
from os import kill
from signal import SIGTERM

# Set variables
appname = "com.example.hellolibtorrent"
activity = "HelloLibtorrent"
apk = "bin/HelloLibtorrent-debug.apk"
times_to_run = 60
time_per_run = 45

# Uninstall the app
print('Uninstalling the app')
Popen("adb shell pm uninstall %s" % appname, shell=True).communicate()

# Install the app
print('Installing the app')
Popen("adb install %s" % apk, shell=True).communicate()


