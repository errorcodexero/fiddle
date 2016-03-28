#include<fstream>
#include<cassert>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<memory>

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }

using namespace std;

string get_elem(unsigned target_col,string const& s){
	unsigned col=0;
	const char *at=s.c_str();
	while(col<target_col && *at){
		while(*at && *at!=',') at++;
		if(*at){
			col++;
			at++;
		}
	}
	assert(*at);
	auto start=at;
	while(*at && *at!=',') at++;
	auto end=at;
	return string(start,end);
}

auto atoi(string s){
	return atoi(s.c_str());
}

template<typename T>
double sum(T v){
	double r=0;
	for(auto a:v) r+=a;
	return r;
}

template<typename T>
double mean(T v){
	double r=0;
	size_t i=0;
	for(auto a:v){
		r+=a;
		i++;
	}
	return r/i;
}

struct Lines{
	string filename;

	struct iterator{
		unique_ptr<ifstream> f;
		bool have_last;
		string last;

		explicit iterator(string s):f(make_unique<ifstream>(s)),have_last(0){}
		iterator():have_last(0){}

		string const& operator*(){
			if(have_last)nyi
			getline(*f,last);
			have_last=1;
			return last;
		}
	};

	iterator begin(){
		return iterator{filename};
	}

	iterator end(){
		return iterator{};
	}
};

Lines::iterator& operator++(Lines::iterator& a){
	if(a.have_last){
		a.have_last=0;
		return a;
	}
	nyi
}

bool operator!=(Lines::iterator const& a,Lines::iterator const& b){
	assert(a.f);
	return a.f->good();
}

template<typename In>
struct Get_col{
	In in;
	size_t col;

	using In_it=decltype(std::begin(in));

	struct iterator{
		size_t col;
		In_it at;

		string operator*(){
			return get_elem(col,*at);
		}

		bool operator!=(iterator const& a)const{
			return at!=a.at;
		}

		iterator& operator++(){
			++at;
			return *this;
		}
	};

	iterator begin(){
		return iterator{col,::begin(in)};
	}

	iterator end(){
		return iterator{col,::end(in)};
	}
};

template<typename In>
struct Atoi{
	In in;

	using In_it=decltype(std::begin(in));

	struct iterator{
		In_it at;

		auto operator*(){
			return atof((*at).c_str());
		}

		bool operator!=(iterator const& a)const{
			return at!=a.at;
		}

		iterator& operator++(){
			++at;
			return *this;
		}
	};

	iterator begin(){
		return iterator{::begin(in)};
	}

	iterator end(){
		return iterator{::end(in)};
	}
};

int main(){
	Lines l{"../Nick/LogReader/log_0.txt"};
	auto g=Get_col<Lines>{l,2};
	auto g2=Atoi<decltype(g)>{g};
	/*for(auto a:g2){
		cout<<a<<"\n";
	}*/
	cout<<mean(g2)<<"\n";
	return 0;
}

int main1(){
	ifstream f("../Nick/LogReader/log_0.txt");
	assert(f.good());
	vector<double> d;
	while(f.good()){
		string s;
		getline(f,s);
		d.push_back(atoi(get_elem(2,s)));
	}
	cout<<sum(d)<<"\n";
	return 0;
}
