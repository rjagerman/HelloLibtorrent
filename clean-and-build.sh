#!/bin/bash
rm -rf bin &&
rm -rf libs &&
rm -rf obj &&
rm -rf gen &&
ndk-build clean &&
ndk-build &&
ant clean &&
ant debug 
