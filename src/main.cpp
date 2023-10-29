// main.cpp -------- Made for Soviet-Linux Project 
// This code is licensed under the GNU General Public License version 3.0
// Author: tutelwastaken <john.g.zioupos@gmail.com> Repository: Soviet-Linux/ripgrep-cpp
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#define CURL_STATICLIB
#include "libs/curl.h"
#include "libs/curlver.h"
#include "libs/easy.h"
#include "libs/header.h"
#include "libs/mprintf.h"
#include "libs/multi.h"
#include "libs/options.h"
#include "libs/stdcheaders.h"
#include "libs/system.h"
#include "libs/urlapi.h"
#include "libs/websockets.h"
#include <sstream>
using namespace std;

char mainver[] = "0.0.1";
char globalver[] = "0.0.1";

// callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

/**
 * timeout is in seconds
 **/
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if(curl)
	{
		if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}

int main(int argc, char **argv){
    if (argv[1] == "--help" or argv[1] == "-h") {
        cout << "Usage: rg [OPTIONS] [SUBOPTION] INPUT " << endl;
        cout << "Options: --help or -h displays this message and exits" << endl;
        cout << "         --version or -v displays the version of this program and exits" << endl;
        cout << "         --files or -f 1) add --view or -v and provide filename of the file to read a file" << endl;
        cout << "                       2) add --remove or -r to delete a file" << endl;
        cout << "                       3) add --new or -n to create a new file" << endl;
        cout << "                       4) add --size to see the size of the file" << endl;
        cout << "         --download or -dl download a file from a provided url" << endl;
        cout << "                       1) add --downloadfile or -dlf to download a file provide also url and filename" << endl;
        cout << "                       2) add --terminal or -t to print to the terminal" << endl;
        return 0;
    } else if (argv[1] == "--version" or argv[1] == "-v") {
        cout << "ripgrep-cpp Version " << globalver << endl;
        cout << "main.cpp Version " << mainver << endl;
        return 0;
    } else if (argv[1] == "--files" or argv[1] == "-f"){
        fstream file;
        if (argv[2] == "--view" or argv[2] == "-v"){
            if (argv[3] == NULL){
                cout << "Please provide a file name for more information type rg-cpp --help" << endl;
                return 1;
            }
            file.open(argv[3], ios::in);
            if(!file){
                cout << "File doesn't exist" << endl;
                return 1;
            } else {
                char content;
                while (1){
                    file>>content;
                    if (file.eof())
                        break;
                    cout<<content;
                }
            }
            file.close();
            return 0;
        } else if (argv[2] == "--remove" or argv[2] == "-r"){
            if (argv[3] == NULL){
                cout << "Please provide a file name for more information type rg-cpp --help" << endl;
                return 1;
            }
            try {
                if (std::filesystem::remove(argv[3]))
                    std::cout << "file " << argv[3] << " deleted.\n";
                else
                    std::cout << "file " << argv[3] << " not found.\n";
                }
                catch(const std::filesystem::filesystem_error& err) {
                    std::cout << "filesystem error: " << err.what() << '\n';
                    return 1;
                }
            return 0;
        } else if (argv[2] == "--new" or argv[2] == "-n"){
            if (argv[3] == NULL){
                cout << "Please provide a file name for more information type rg-cpp --help" << endl;
                return 1;
            }
            fstream file;
            file.open(argv[3], ios::out);
            if (!file){
                cout << "Error When creating file" << endl;
                return 1;
            } else {
                file.close();
                cout << "File created successfully" << endl;
                return 0;
            }
        } else if (argv[2] == "--size" or argv[2] == "-s"){
            if (argv[3] == NULL){
                cout << "Please provide a file name for more information type rg-cpp --help" << endl;
                return 1;
            }
            std::filesystem::path p{argv[3]};
            std::cout << "The size of " << p.u8string() << " is " << std::filesystem::file_size(p) << " bytes.\n";
            return 0;
        } else{
            cout << "Invalid Subcommand type rg-cpp --help for help" << endl;
            return 1;
        }
    } else if (argv[1] == "--download" or argv[1] == "-dl"){
        if (argv[4] == NULL){
            cout << "Please provide a url for more information type rg-cpp --help" << endl;
            return 1;
        } else if (argv[5] == NULL){
            cout << "Please provide a file name with a path for more information type rg-cpp --help" << endl;
            return 1;
        }
        curl_global_init(CURL_GLOBAL_ALL);
        if (argv[3] == "--downloadfile" or argv[3] == "-dlf"){
            ofstream ofs(argv[5]);
            if (CURLE_OK == curl_read(argv[4], ofs)){
                cout << "File downloaded successfully" << endl;
                ofs.close();
                curl_global_cleanup();
                return 0;
            } else {
                cout << "An Unknown Error Occured" << endl;
                ofs.close();
                curl_global_cleanup();
                return 1;
            }
        } else if (argv[3] == "--terminal" or argv[3] == "-t") {
            if (CURLE_OK == curl_read(argv[4], cout)) {
                curl_global_cleanup();
                return 0;
            } else {
                cout << "An Unknown Error Occured" << endl;
                curl_global_cleanup();
                return 1;
            }
        } else {
            cout << "Invalid Subcommand or No Subcommand type rg-cpp --help for information" << endl;
            curl_global_cleanup();
            return 1;
        }
        curl_global_cleanup();
        return 0;
    } else {
        cout << "Invalid Command or No Command" << endl;
        cout << "Usage: rg [OPTIONS] [SUBOPTION] INPUT " << endl;
        cout << "Options: --help or -h displays this message and exits" << endl;
        cout << "         --version or -v displays the version of this program and exits" << endl;
        cout << "         --files or -f 1) add --view or -v and provide filename of the file to read a file" << endl;
        cout << "                       2) add --remove or -r to delete a file" << endl;
        cout << "                       3) add --new or -n to create a new file" << endl;
        cout << "                       4) add --size to see the size of the file" << endl;
        cout << "         --download or -dl download a file from a provided url" << endl;
        cout << "                       1) add --downloadfile or -dlf to download a file provide also url and filename" << endl;
        cout << "                       2) add --terminal or -t to print to the terminal" << endl;
        return 1;  
    }
    return 0;
}