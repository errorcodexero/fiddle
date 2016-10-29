#include <iostream>
#include <regex>
#include <curl/curl.h>

using namespace std;

struct Value_data {
	string value;
	bool found=0, multi_match=0;
};

int error(string msg) {
	cout<<"Error: "<<msg<<endl;
	return 1;
}

size_t find_value(char* buffer, size_t size, size_t nmemb, Value_data* data) {
	string page = buffer;
	smatch match;
	data->found = data->found || regex_search(page, match, regex("data bgLast\">(.*)</p>"));
	data->multi_match = data->multi_match || match.size() > 2;
	//if (data->found && !data->multi_match) data->value = match[1];
	return nmemb;	
}

int main() {
	Value_data data;
	CURL *curl = curl_easy_init();
	if (!curl) return error("CURL pointer was not initialized.");
	
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.marketwatch.com/investing/stock/AAPL");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, find_value);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	if (!data.found) return error("Value not found in page");
	if (data.multi_match) return error("Multiple matches found in page.");
	cout<<"Value: "<<data.value<<endl;
	return 0;
}
