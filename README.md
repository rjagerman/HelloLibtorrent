HelloLibtorrent
===============

This is a basic setup to test libtorrent on android.

You can simply run the `clean-and-build.sh` to build the entire thing. This will also automatically install the created apk on a connected phone and start adb logcat.

Do note that this example will download a torrent file which is hardcoded on a location (see `jni/hello.cpp` for details). You will have to place this torrent file manually on your phone. Next, you will want to change the 2 occurrences of `/storage/sdcard0/Torrents` in `jni/hello.cpp` to where the torrent is located.
