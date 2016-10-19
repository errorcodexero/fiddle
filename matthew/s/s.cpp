#include <iostream>
#include <regex>
#include <curl/curl.h>

using namespace std;

int main() {
	CURL *curl = curl_easy_init();
	if (!curl) {
		cout<<"Error: CURL pointer was not initialized."<<endl;
		return 1;
	}
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.marketwatch.com/investing/stock/AAPL");
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return 0;
}
