#include<iostream>
#include<vector>
#include<fstream>
#include<set>

using namespace std;

#define nyi { cout<<"error! "<<__LINE__<<"\n"; exit(44); }

template<typename T>
ostream& operator<<(ostream& o,vector<T> v){
	o<<"[";
	for(auto a:v) o<<a<<" ";
	return o<<"]";
}

template<typename T>
ostream& operator<<(ostream& o,set<T> const& a){
	o<<"{ ";
	for(auto elem:a) o<<elem<<" ";
	return o<<"}";
}

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> const& p){
	return o<<"("<<p.first<<","<<p.second<<")";
}

template<typename T,typename T2>
vector<T>& operator|=(vector<T> &a,T2 t){
	a.push_back(t);
	return a;
}

template<typename T>
set<T> operator|=(set<T> &a,T t){
	a.insert(t);
	return a;
}

vector<string> args(int argc,char **argv){
	vector<string> r;
	for(int i=1;i<argc;i++) r|=argv[i];
	return r;
}

template<typename Collection>
vector<size_t> sizes(Collection c){
	vector<size_t> r;
	for(auto a:c){
		r|=a.size();
	}
	return r;
}

template<typename Collection>
bool all_equal(Collection c){
	if(c.empty()) return 1;
	for(auto elem:c){
		if(elem!=c[0]){
			return 0;
		}
	}
	return 1;
}

template<typename T>
set<T> values(vector<T> c){
	set<T> r;
	for(auto a:c) r|=a;
	return r;
}

template<typename C>
auto flatten(C c)->vector<
	typename remove_reference<decltype(*begin(*begin(c)))>::type
>{
	vector<
		typename remove_reference<decltype(*begin(*begin(c)))>::type
	> r;
	for(auto b:c){
		for(auto a:b){
			r|=a;
		}
	}
	return r;
}

size_t div_round_up(size_t num,size_t denom){
	return num/denom+((num%denom)!=0);
}

vector<pair<unsigned,unsigned>> scale_sections(unsigned len,unsigned denom){
	vector<pair<unsigned,unsigned>> r;
	for(unsigned i=0;i<len;i+=denom){
		r|=make_pair(i,min(len-1,i+denom-1));
	}
	return r;
}

vector<size_t> inclusive_range(pair<size_t,size_t> p){
	vector<size_t> r;
	for(auto i=p.first;i<=p.second;i++){
		r|=i;
	}
	return r;
}

template<typename C>
auto select_area(
	pair<size_t,size_t> xs,
	pair<size_t,size_t> ys,
	vector<C> in
)->
vector<vector<
	typename remove_reference<decltype(*begin(*begin(in)))>::type
>>
{
	using T=typename remove_reference<decltype(*begin(*begin(in)))>::type;
	vector<vector<T>> r;
	for(auto y:inclusive_range(ys)){
		vector<T> line;
		for(auto x:inclusive_range(xs)){
			line|=in[y][x];
		}
		r|=line;
	}
	return r;
}

int main(int argc,char **argv){
	auto a=args(argc,argv);
	if(a.size()!=2){
		cout<<"usage: <SCALE_FACTOR> <FILENAME>\n";
		return 1;
	}
	vector<string> in;
	ifstream f(a[1]);
	while(f.good()){
		string s;
		getline(f,s);
		if(s.size()){
			in|=s;
		}
	}

	//validate input
	//cout<<"sizes:"<<sizes(in)<<"\n";
	if(!all_equal(sizes(in))){
		cout<<"Error: not all lines are the same length\n";
		return 1;
	}
	auto v=values(flatten(in));
	cout<<v<<"\n";
	if(v!=set<char>{'0','1'}){
		cout<<"Error: Unknown characters:"<<v<<"\n";
	}

	//compress to new size
	int scale=atoi(a[0].c_str());
	if(scale<=0){
		cout<<"Invalid scale: "<<scale<<".  Must be a positive integer.\n";
		return 1;
	}

	const auto width=in[0].size();
	const auto height=in.size();
	//const size_t new_width=div_round_up(a[0].size(),scale);
	//const size_t new_height=div_round_up(a.size(),scale);

	//cout<<"new_width:"<<new_width<<"\n";
	//cout<<"new_height:"<<new_height<<"\n";

	#define P(X) cout<<""#X<<(X)<<"\n";
	auto y_sections=scale_sections(height,scale);
	auto x_sections=scale_sections(width,scale);
	P(y_sections)
	P(x_sections)

	vector<vector<char>> out;
	for(auto ys:scale_sections(height,scale)){
		vector<char> line;
		for(auto xs:scale_sections(width,scale)){
			cout<<"ys:"<<ys<<","<<xs<<"\n";
			auto n=select_area(xs,ys,in);
			cout<<"n:"<<n<<"\n";

			auto v=values(flatten(n));
			auto next=[&](){
				if(v==set<char>{'0','1'}){
					return '1';
				}else if(v==set<char>{'0'}){
					return '0';
				}else if(v==set<char>{'1'}){
					return '1';
				}else{
					nyi
				}
			}();
			line|=next;
		}
		out|=line;
	}

	cout<<"out:\n";
	for(auto a:out){
		for(auto c:a){
			cout<<c;
		}
		cout<<"\n";
	}

	return 0;
}
