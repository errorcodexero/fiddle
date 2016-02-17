#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<fstream>
#include "../log/common.h"
#include "../log/maybe.h"

using namespace std;

//stuff that could be moved to util
vector<size_t> range_inclusive(size_t i){
	return range(i+1);
}

#define PRINT(X) cout<<""#X<<":"<<X<<"\n";

template<typename T>
auto firsts(T a){ return mapf([](auto elem){ return elem.first; },a); }

template<typename T>
auto seconds(T a){ return mapf([](auto elem){ return elem.second; },a); }

template<typename T>
array<T,3> items(tuple<T,T,T> t){
	return {get<0>(t),get<1>(t),get<2>(t)};
}

template<typename A>
auto firsts(tuple<A,A,A> t)->array<decltype(get<0>(t).first),3>{
	return firsts(items(t));
}

template<typename A>
auto seconds(tuple<A,A,A> t)->array<decltype(get<0>(t).second),3>{
	return seconds(items(t));
}

template<typename K,typename V>
vector<K> keys(map<K,V> m){
	return firsts(m);
	/*vector<K> r;
	for(auto p:m) r|=nyi*/
}

template<typename K,typename V>
auto values(map<K,V> m){ return seconds(m); }

template<typename T>
Maybe<pair<T,T>> limits(vector<T> v){
	if(v.empty()) return Maybe<pair<T,T>>();
	return Maybe<pair<T,T>>(make_pair(min(v),max(v)));
}

template<typename T>
vector<T> reversed(vector<T> v){
	reverse(v.begin(),v.end());
	return v;
}

template<typename Func,typename T,size_t LEN>
auto mapf(Func f,array<T,LEN> a)->array<decltype(f(a[0])),LEN>{
	array<decltype(f(a[0])),LEN> r;
	for(auto i:range(LEN)) r[i]=f(a[i]);
	return r;
}

template<typename A>
A sum(tuple<A,A,A> a){
	return get<0>(a)+get<1>(a)+get<2>(a);
}

template<typename T,size_t LEN>
T sum(array<T,LEN> a){
	T r{};
	for(auto elem:a) r+=elem;
	return r;
}

template<typename T,size_t LEN>
T product(array<T,LEN> a){
	T r=1;
	for(auto elem:a) r*=elem;
	return r;
}

template<typename K,typename V>
map<K,V> map_all_to(set<K> s,V v){
	map<K,V> r;
	for(auto a:s) r[a]=v;
	return r;
}

template<typename K,typename V>
map<K,V> map_all_to(vector<K> s,V v){
	map<K,V> r;
	for(auto a:s) r[a]=v;
	return r;
}

template<typename T>
map<T,size_t> count(vector<T> v){
	auto m=to_multiset(v);
	map<T,size_t> r;
	for(auto a:m){
		r[a]=m.count(a);
	}
	return r;
}

template<typename K,typename V>
map<K,float> operator/(map<K,V> in,float f){
	map<K,float> r;
	for(auto p:in){
		r[p.first]=p.second/f;
	}
	return r;
}

template<size_t LEN>
array<size_t,LEN> range_st(){
	array<size_t,LEN> r;
	for(size_t i=0;i<LEN;i++) r[i]=i;
	return r;
}

/*template<typename A,typename B,typename C>
vector<tuple<A,B,C>> cross(vector<A> va,vector<B> vb,vector<C> vc){
	return mapf(
		[](auto p){
			return make_tuple(p.first.first,p.first.second,p.second);
		},
		cross(cross(va,vb),vc)
	);
}*/

template<typename A,typename B,typename C>
auto cross(A a,B b,C c)->vector<tuple<ELEM(a),ELEM(b),ELEM(c)>>{
	return mapf(
		[](auto p){
			return make_tuple(p.first.first,p.first.second,p.second);
		},
		cross(cross(a,b),c)
	);
}

//normal program
#define SCORING_ITEMS X(unsigned int,balls) X(unsigned int,defenses)
struct Scoring{
	#define X(A,B) A B;
	SCORING_ITEMS
	#undef X
};

ostream& operator<<(ostream& o,Scoring const& a){
	return o<<"("<<a.balls<<","<<a.defenses<<")";
}

bool operator<(Scoring const& a,Scoring const& b){
	#define X(A,B) if(a.B<b.B) return 1; if(b.B<a.B) return 0;
	SCORING_ITEMS
	#undef X
	return 0;
}

Scoring& operator+=(Scoring &a,Scoring b){
	#define X(A,B) a.B+=b.B;
	SCORING_ITEMS
	#undef X
	return a;
}

Scoring operator+(Scoring a,Scoring b){
	a+=b;
	return a;
}

Scoring rand(Scoring*){
	return {unsigned(rand()%10),unsigned(rand()%6)};//limits chosen arbitrarily
}

vector<Scoring> below_eq(Scoring a){
	return mapf(
		[](pair<unsigned,unsigned> p){
			return Scoring{p.first,p.second};
		},
		cross(range_inclusive(a.balls),range_inclusive(a.defenses))
	);
}

//does b not exceed a in any way?
bool below_eq(Scoring a,Scoring b){
	nyi
}

template<typename T>
void show_pts(map<Scoring,T> m){
	if(m.empty()){
		cout<<"[empty]\n";
		return;
	}
	auto k=keys(m);
	auto f=mapf([](auto a){ return a.defenses; },k);
	auto s=mapf([](auto a){ return a.balls; },k);
	//cout<<"x:"<<limits(f)<<"\n";
	//cout<<"y:"<<limits(s)<<"\n";

	auto v=values(m);
	auto max_size=max(mapf([](auto a){ return as_string(a).size(); },v));
	//PRINT(max_size)

	for(auto y:reversed(range(max(s)))){
		for(auto x:range(max(s))){
			auto s=[&]()->string{
				auto f=m.find(Scoring{(unsigned)x,(unsigned)y});
				if(f==m.end()){
					return ".";
				}else{
					return as_string(f->second);
				}
			};
			cout<<pad_to_width(max_size+1,s());
		}
		cout<<"\n";
	}
}

using Team_data=vector<Scoring>;

vector<Scoring> team_example_data(){
	return mapf([](int){ return rand((Scoring*)nullptr); },range(5));
}

using Alliance_data=array<Team_data,3>;

Alliance_data alliance_example_data(){
	return mapf([](auto){ return team_example_data(); },range_st<3>());
}

Team_data added(Alliance_data a1){
	auto c=cross(a1[0],a1[1],a1[2]);
	return MAP(sum,c);
}

using Odds=map<Scoring,float>;

Odds odds(Team_data td){
	return count(flatten(MAP(below_eq,td)))/td.size();
}

Odds odds(Alliance_data ad){
	auto m=MAP(odds,ad);
	using P=pair<Scoring,float>;
	auto m2=mapf(
		[](tuple<P,P,P> t){
			return make_pair(sum(firsts(t)),product(seconds(t)));
		},
		cross(m[0],m[1],m[2])
	);
	Odds r;
	for(auto option:m2){
		auto f=r.find(option.first);
		if(f==r.end() || option.second>f->second){
			r[option.first]=option.second;
		}
	}
	return r;
}

float add_noise(float a){
	switch(rand()%3){
		case 0: a-=.25;
		case 1: break;
		case 2: a+=.25;
	}
	return a;
}

void make_plot(vector<Scoring> v){
	{
		ofstream out("plot.tmp");
		for(auto a:v) out<<add_noise(a.defenses)<<","<<add_noise(a.balls)<<"\n";
	}
	{
		ofstream cmd("cmd.txt");
		cmd<<"set datafile separator \",\"\n";
		cmd<<"set title \"Combined alliance proven possiblities\"\n";
		cmd<<"set nokey\n";
		cmd<<"set ylabel \"Balls\"\n";
		cmd<<"set xlabel \"Defenses\"\n";
		cmd<<"set terminal png size 700,700 enhanced font \"Helvetica,20\"\n";
		cmd<<"set output 'output.png'\n";
		//cmd<<"set ytics 1\n";
		//cmd<<"set xtics 1\n";
		cmd<<"plot \"plot.tmp\" using 1:2\n";
	}
	auto r=system("gnuplot cmd.txt");
	assert(r==0);
}

int main(){
	Scoring a{2,1};
	/*cout<<a<<"\n";
	cout<<below_eq(a)<<"\n";*/
	auto rands=team_example_data();
	//cout<<rands<<"\n";
	auto all_pts=to_set(flatten(MAP(below_eq,rands)));
	//auto all_pts=flatten(MAP(below_eq,rands));
	//PRINT(all_pts);
	//show_pts(map_all_to(all_pts,0));

	auto f=flatten(MAP(below_eq,rands));
	show_pts(count(f)/rands.size());

	auto a1=alliance_example_data();
	PRINT(a1)
	auto whole=added(a1);
	PRINT(whole)
	show_pts(map_all_to(whole,0));
	show_pts(odds(a1));
	make_plot(whole);
}
