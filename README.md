HelloLibtorrent
===============

This is a basic setup to test libtorrent on android.

Before building, make sure to create a project out of the cloned folder:

    cd HelloLibtorrent
    android update project -p . -t android-14

You can then run the `clean-and-build.sh` script to build the entire thing. This will also automatically compile and create the .apk file.

Do note that this example will download a torrent file which is hardcoded on a location (see `jni/hello.cpp` for details). You will have to place this torrent file manually on your phone. Next, you will want to change the **2** occurrences of `/storage/sdcard0/Torrents` in `jni/hello.cpp` to where the torrent is located and where the resulting files should be stored.
