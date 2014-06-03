/*
 * A simple libtorrent client for android using JNI
 */
#include <string>
#include <jni.h>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

// Expose our JNI functions
extern "C" {
	jstring Java_com_example_hellolibtorrent_HelloLibtorrent_startTorrent( JNIEnv* env, jobject thiz );
	jstring Java_com_example_hellolibtorrent_HelloLibtorrent_getStatus( JNIEnv* env, jobject thiz );
}

// Set variables
char* torrent_file = "/storage/extSdCard/Torrents/ubuntu-14.04-desktop-i386.iso.torrent";
char* save_location = "/storage/extSdCard/Torrents/";
libtorrent::session s;
libtorrent::add_torrent_params p;
libtorrent::torrent_handle h;

/* 
 * Starts downloading the torrent and returns the path of the torrent file we are downloading
 */
jstring Java_com_example_hellolibtorrent_HelloLibtorrent_startTorrent( JNIEnv* env, jobject thiz ) {
	std::string result = "";

	try {
		s.listen_on(std::make_pair(6881, 6889));
    	p.save_path = save_location;
    	p.ti = new libtorrent::torrent_info(torrent_file);
    	h = s.add_torrent(p);

    	result = "Started torrent";
    } catch(std::exception& e) {
    	result = e.what();
    }

	return env->NewStringUTF(result.c_str());
}

/*
 * Returns the current status of the torrent in a single string
 */
int counter = 0;
jstring Java_com_example_hellolibtorrent_HelloLibtorrent_getStatus( JNIEnv* env, jobject thiz ) {
	std::stringstream result;

	if (h.is_valid()) {
		libtorrent::torrent_status status = h.status();
		counter++;
		result << "Status update " << counter << std::endl
		    << "  Progress: " << (status.progress * 100.0) << "%" << std::endl
		    << "  Download rate: " << status.download_rate << std::endl
		    << "  Upload rate: " << status.upload_rate << std::endl
		    << "  Seeds: " << status.num_seeds << std::endl
		    << "  Peers: " << status.num_peers;
	} else {
		result << "Handle is not valid";
	}
	
	return env->NewStringUTF(result.str().c_str());
}

