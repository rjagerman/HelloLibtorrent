/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string>
#include <jni.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

// A handle to the torrent that will be downloaded
libtorrent::torrent_handle h;

// The file path (as a string) of the torrent that will be downloaded
std::string torrent_to_download;

// Open libtorrent session
libtorrent::session s;

extern "C" {

	/* 
	 * Prints the torrent that we will download
	 */
	jstring Java_com_example_hellolibtorrent_HelloLibtorrent_whichTorrent( JNIEnv* env, jobject thiz ) {
		torrent_to_download = "/storage/sdcard0/Torrents/ubuntu-14.04-desktop-i386.iso.torrent";
		return env->NewStringUTF(torrent_to_download.c_str());
	}

	/*
	 * Starts the download and returns a status message or error message
	 */
	jstring Java_com_example_hellolibtorrent_HelloLibtorrent_startDownload( JNIEnv* env, jobject thiz ) {

		std::string result = "nothing";
		try {
			// Start listening
			s.listen_on(std::make_pair(6881, 6889));

			// Grab torrent file
			libtorrent::add_torrent_params p;
			p.save_path = "/storage/sdcard0/Torrents/";
			p.ti = new libtorrent::torrent_info(torrent_to_download);

			// Start torrent
			h = s.add_torrent(p);

			// Get torrent size
			std::stringstream ss;
			ss  << "Started torrent:\n"
				<< "  Size: " << p.ti->total_size() << " bytes\n"
				<< "  Save path: " << p.save_path;
			result = ss.str();

		} catch (std::exception& e) {
			result = e.what();
		}

		return env->NewStringUTF(result.c_str());
	}

	/*
	 * Gets the progress on the torrent download
	 */
	jstring Java_com_example_hellolibtorrent_HelloLibtorrent_status( JNIEnv* env, jobject thiz ) {
		std::string output = "???";
		try {

			// Get torrent status
			libtorrent::torrent_status status = h.status();

			// Convert torrent state from enum to string
			std::string stringstate = "Unknown state";
			switch(status.state) {
				case libtorrent::torrent_status::queued_for_checking:
					stringstate = "Queued for checking"; break;
				case libtorrent::torrent_status::checking_files:
					stringstate = "Checking files"; break;
				case libtorrent::torrent_status::downloading_metadata:
					stringstate = "Downloading metadata"; break;
				case libtorrent::torrent_status::downloading:
					stringstate = "Downloading"; break;
				case libtorrent::torrent_status::finished:
					stringstate = "Finished"; break;
				case libtorrent::torrent_status::seeding:
					stringstate = "Seeding"; break;
				case libtorrent::torrent_status::allocating:
					stringstate = "Allocating"; break;
				case libtorrent::torrent_status::checking_resume_data:
					stringstate = "Checking resume data"; break;
				default:
					stringstate = "Unknown state";
			}

			// Get torrent status and print it in string format
			std::stringstream ss;
			ss  << "Torrent status\n"
			    << "  Name: " << status.name << "\n"
				<< "  State: " << stringstate << "\n"
				<< "  Error: " << status.error << "\n"
				<< "  Seeds: " << status.list_seeds << " (Active: " << status.num_seeds << ")\n"
				<< "  Peers: " << status.list_peers << " (Active: " << status.num_peers << ")\n"
				<< "  Download rate: " << status.download_rate << " bps\n"
				<< "  Upload rate: " << status.upload_rate << " bps\n"
				<< "  Download progress: " << (status.progress * 100.0) << "%";
			output = ss.str();

		} catch(std::exception& e) {
			output = e.what();
		}
		return env->NewStringUTF(output.c_str());
	}

}

