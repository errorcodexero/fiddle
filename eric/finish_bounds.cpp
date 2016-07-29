#include<iostream>
#include<set>
#include<vector>

using namespace std;

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }

template<typename T>
ostream& operator<<(ostream& o,set<T> const& a){
	o<<"{ ";
	for(auto x:a) o<<x<<" ";
	return o<<"}";
}

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> const& p){
	return o<<"("<<p.first<<","<<p.second<<")";
}

template<typename T>
ostream& operator<<(ostream& o,vector<T> const& a){
	o<<"[ ";
	for(auto x:a) o<<x<<" ";
	return o<<"]";
}

template<typename T>
vector<T>& operator|=(vector<T>& a,T t){
	a.push_back(t);
	return a;
}

vector<size_t> range(size_t lim){
	vector<size_t> r;
	for(size_t i=0;i<lim;i++) r|=i;
	return r;
}

template<typename Func,typename T>
auto mapf(Func f,vector<T> v)->vector<decltype(f(v[0]))>{
	vector<decltype(f(v[0]))> r;
	for(auto a:v) r|=f(a);
	return r;
}

using Team=int;

Team rand(Team*){
	return rand()%20;
}

using Alliance=set<Team>;

Alliance rand(Alliance*){
	Team *t;
	return {rand(t),rand(t),rand(t)};
}

using Match=pair<Alliance,Alliance>;

Match rand(Match*){
	return make_pair(rand((Alliance*)0),rand((Alliance*)0));
}

using Schedule=vector<Match>;

Schedule rand(Schedule*){
	return mapf([](int){ return rand((Match*)0); },range(5));
}

int main(){
	cout<<rand((Schedule*)nullptr);
}
