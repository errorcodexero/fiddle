#include <iostream>
#include <regex>
#include <curl/curl.h>

using namespace std;

struct Price_data {
	double price, low, opening;
	bool found = 0, multi_match = 0;
	bool get_open = 1;
};

int error(string msg) {
	cout<<"Error: "<<msg<<endl;
	return 1;
}

size_t find_price(char* buffer, size_t size, size_t nmemb, Price_data* data) {
	string page = buffer;
	
	smatch match;
	bool found = regex_search(page, match, regex("data bgLast\">(.*)</p>"));
	bool multi_match = match.size() > 2;
	data->found = data->found || found;
	data->multi_match = data->multi_match || multi_match;
	if (found && !multi_match) data->price = stod(match[1]);
	if (regex_search(page, match, regex("Day high</p>\\s*<p class=\"column data\">(.*)</p>")))
		data->low = stod(string(match[1]).substr(1));
	if (data->get_open && regex_search(page, match, regex("Open: (.*)"))) {
		data->opening = stod(match[1]);
		data->get_open = 0;
	}
	return size*nmemb;	
}

int main(int argc, char** argv) {
	Price_data data;
	if (argc < 2) return error("A stock symbol must be supplied as an argument.");
	string url("http://www.marketwatch.com/investing/stock/" + string(argv[1]));

	CURL *curl = curl_easy_init();
	if (!curl) return error("CURL pointer was not initialized.");

	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, find_price);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	if (!data.found) return error("Price not found in page");
	if (data.multi_match) return error("Multiple matches found in page.");
	cout<<"Price: "<<data.price<<endl;
	cout<<"Day Low: "<<data.low<<endl;
	cout<<"Opening: "<<data.opening<<endl;
	return 0;
}
