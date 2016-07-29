#include<iostream>
#include<set>
#include<vector>
#include<map>

using namespace std;

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }
#define PRINT(X) { cout<<""#X<<":"<<X<<"\n"; }

template<typename T>
set<T> operator|(set<T> a,set<T> b){
	for(auto x:b) a.insert(x);
	return a;
}

template<typename K,typename V>
ostream& operator<<(ostream& o,map<K,V> const& a){
	o<<"{ ";
	for(auto x:a) o<<x<<" ";
	return o<<"}";
}

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
vector<T> operator|(vector<T> a,vector<T> b){
	nyi
}

template<typename T>
vector<T> operator|(vector<T>,T){
	nyi
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

#define MAP(FUNC,ARRAY) mapf([&](decltype(ARRAY[0]) a){ return FUNC(a); },ARRAY)

template<typename T>
vector<T> tail(vector<T> v){
	vector<T> r;
	for(size_t i=1;i<v.size();i++) r|=v[i];
	return r;
}

template<typename T>
vector<T>& operator|=(vector<T>& a,vector<T> t){
	for(auto x:t) a.push_back(x);
	return a;
}

template<typename K,typename V>
vector<K> keys(map<K,V> a){
	vector<K> r;
	for(auto p:a) r|=p.first;
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

using Ranking_points=int;

using Current_standings=map<Team,Ranking_points>;

Current_standings rand(Current_standings*){
	Current_standings r;
	for(auto i:range(10)){
		r[rand((Team*)0)]=rand((Ranking_points*)0);
	}
	return r;
}

Current_standings update(Current_standings in,Alliance win,Alliance lose){
	for(auto team:win){
		auto f=in.find(team);
		if(f==in.end()){
			in[team]=2;
		}else{
			f->second+=2;
		}
	}
	return in;
}

Current_standings tied(Current_standings standings,Alliance a,Alliance b){
	for(auto team:a|b){
		auto f=standings.find(team);
		if(f==standings.end()){
			standings[team]=1;
		}else{
			f->second++;
		}
	}
	return standings;
}

vector<Current_standings> play_match(Current_standings standings,Match match){
	auto a=match.first;
	auto b=match.second;
	vector<Current_standings> r;
	r|=update(standings,a,b);
	r|=update(standings,b,a);
	r|=tied(standings,a,b);
	return r;
}

vector<Current_standings> remaining(Current_standings standings,vector<Match> matches){
	if(matches.empty()) return {standings};
	vector<Current_standings> r;
	for(auto x:play_match(standings,matches[0])){
		r|=remaining(x,tail(matches));
	}
	return r;
}

int main(){
	auto current=rand((Current_standings*)0);
	auto remaining1=rand((Schedule*)nullptr);
	PRINT(current);
	PRINT(remaining);
	PRINT(play_match(current,remaining1[0]));
	auto x=remaining(current,remaining1);
	//PRINT(x)
	auto teams=MAP(flatten,MAP(keys,x));
	PRINT(teams);
}
