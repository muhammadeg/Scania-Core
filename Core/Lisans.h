#include "curl\curl.h"
using namespace std;
#pragma comment(lib, "C:/Core - Local/Core/curl/libcurl_a.lib")
//#pragma comment(lib, "D:/lib/libcurl_a.lib")
#pragma comment(lib, "iphlpapi.lib")
#include "sha256.h"
#include <stdint.h>
typedef std::basic_string<TCHAR> tstring;
#define WIN32_LEAN_AND_MEAN        
#include <windows.h>      
#include <intrin.h>       
#include <iphlpapi.h>    

uint16_t ma1;
uint16_t ma2;	
string data;
std::string GetLicenseKey()
{
	// Code to retrieve the license key
	return "Baladi23821kdmsIW";
}

std::string GetHWID()
{
	// Code to retrieve the hardware ID
	std::string hwid;
	HW_PROFILE_INFO hwProfileInfo;

	if (GetCurrentHwProfile(&hwProfileInfo) != NULL)
	{
		hwid = hwProfileInfo.szHwProfileGuid;
	}

	return hwid;
}

std::vector<std::string> getExplode(const std::string delimiter, const std::string ender, const std::string str) {

	std::vector<std::string> results;

	std::vector<std::string> arr = explode(delimiter, str);
	for (size_t i = 1; i<arr.size(); i++) {
		std::vector<std::string> arrend = explode(ender, arr[i]);
		results.push_back(arrend[0]);
	}
	return results;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string getData(string url){
	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

    return readBuffer;

}
int RemoteLisansCheck()
{
	// Get license key and hardware ID
	string licenseKey = GetLicenseKey();
	string hwid = GetHWID();

	// Construct URL to check license remotely
	string url = "http://134.255.216.173/check_license.php?key=" + licenseKey;
//	string url = "http://127.0.0.1/check_license.php?key=" + licenseKey;

	// Retrieve data from the URL
	string response = getData(url);

	// Parse the response
	if (response.find("OK") != string::npos)
	{
		ScaniaLicense = 1;
		return 1; // License is valid
	}
	else
	{
		ScaniaLicense = 0;
		return 0; // License is invalid
	}
}
void SendChatData(const std::string& msg)
{
	CURL* curl = curl_easy_init();
	if (curl)
	{
		std::string url = "http://134.255.216.173/save_chat.php";
		std::string chatData = msg;
		std::string response;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, chatData.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, chatData.length());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		CURLcode res = curl_easy_perform(curl);
		if (res == CURLE_OK)
		{
			std::cout << "Data sent successfully." << std::endl;
			std::cout << "Response: " << response << std::endl;
		}
		else
		{
			std::cerr << "Failed to send data: " << curl_easy_strerror(res) << std::endl;
		}

		curl_easy_cleanup(curl);
	}
}