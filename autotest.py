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

# Clear current log
file('errors.log', 'w').close()

for i in range(1,50):
	print('Running test %d' % i)

	# Uninstall the app
	print('Uninstalling the app')
	Popen("adb shell pm uninstall %s" % appname, shell=True).communicate()

	# Install the app
	print('Installing the app')
	Popen("adb install %s" % apk, shell=True).communicate()

	# Run logcat
	print('Clearing logcat')
	Popen("adb logcat -c", shell=True).communicate()

	print('Running logcat')
	logger = Popen("adb logcat", shell=True, stdout=file('autotest.log', 'w'), stderr=file('autotest.err.log', 'w'))

	# Run the app and wait
	print("Running the application")
	Popen("adb shell am start -n %s/%s.%s" % (appname, appname, activity), shell=True).communicate()
	start = time()
	while(time()-start < time_per_run):
		time_remaining = str(time_per_run - int(time() - start))
		time_str = time_remaining.rjust(6, ' ')
		print('\r' + time_str + " seconds remaining in test", end='')
		stdout.flush()
		sleep(1)
	print('\rFinished test!                  ')

	# Close the application
	print("Closing the application")
	Popen("adb shell am force-stop %s" % appname, shell=True).communicate()

	# Kill logcat
	print("Killing logcat")
	kill(logger.pid, SIGTERM)

	# Print segs if they occur
	Popen("cat autotest.log | grep \"Fatal signal 11\" -A262", shell=True, stdout=file('errors.log', 'a')).communicate()

print("Done testing!")