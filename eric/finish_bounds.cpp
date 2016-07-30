#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<typeinfo>
#include<cassert>
#include<algorithm>
#include<unordered_map>

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

template<typename K,typename V>
ostream& operator<<(ostream& o,unordered_map<K,V> const& a){
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

template<typename T,size_t LEN>
ostream& operator<<(ostream& o,array<T,LEN> const& a){
	o<<"[ ";
	for(auto elem:a) o<<elem<<" ";
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

template<size_t LEN>
array<size_t,LEN> range_st(){
	array<size_t,LEN> r;
	for(size_t i=0;i<LEN;i++) r[i]=i;
	return r;
}

template<typename Func,typename T>
auto mapf(Func f,vector<T> const& v)->vector<decltype(f(v[0]))>{
	vector<decltype(f(v[0]))> r;
	r.reserve(v.size());
	for(auto const& a:v) r|=f(a);
	return r;
}

#define MAP(FUNC,ARRAY) mapf([&](auto a){ return FUNC(a); },ARRAY)

template<typename T>
vector<T> tail(vector<T> const& v){
	vector<T> r;
	for(size_t i=1;i<v.size();i++) r|=v[i];
	return r;
}

template<typename T>
vector<T>& operator|=(vector<T>& a,vector<T> const& t){
	for(auto x:t) a.push_back(x);
	return a;
}

template<typename K,typename V>
vector<K> keys(map<K,V> const& a){
	vector<K> r;
	for(auto p:a) r|=p.first;
	return r;
}

template<typename K,typename V>
vector<K> keys(unordered_map<K,V> const& a){
	vector<K> r;
	for(auto p:a) r|=p.first;
	return r;
}

template<typename T>
vector<T> flatten(vector<vector<T>> const& a){
	vector<T> r;
	for(auto elem:a) r|=elem;
	return r;
}

template<typename T>
set<T> flatten(vector<set<T>> a){
	set<T> r;
	for(auto elem:a) r|=elem;
	return r;
}

template<typename T>
set<T>& operator|=(set<T>& a,T b){
	a.insert(b);
	return a;
}

template<typename T>
set<T> to_set(vector<T> a){
	set<T> r;
	for(auto x:a) r|=x;
	return r;
}

template<typename T>
vector<T> sorted(vector<T> a){
	sort(begin(a),end(a));
	return a;
}

template<typename T>
T min(vector<T> const& a){
	assert(a.size());
	T r=a[0];
	for(auto x:a) r=min(r,x);
	return r;
}

template<typename T>
T max(vector<T> const& a){
	/*assert(a.size());
	return sorted(a)[a.size()-1];*/
	T r=a[0];
	for(auto elem:a) r=max(r,elem);
	return r;
}

template<typename T>
T median(vector<T> v){
	assert(v.size());
	//return sorted(v)[v.size()/2];
	auto n=v.size()/2;
	nth_element(v.begin(),v.begin()+n,v.end());
	return v[n];
}

template<typename A,typename B>
pair<B,A> reverse(pair<A,B> p){
	nyi
}

template<typename T>
vector<pair<size_t,T>> enumerate_from(size_t start,vector<T> v){
	vector<pair<size_t,T>> r;
	for(size_t i=0;i<v.size();i++){
		r|=make_pair(start+i,v[i]);
	}
	return r;
}

template<typename T>
vector<T> to_vec(set<T> a){
	vector<T> r;
	for(auto elem:a) r|=elem;
	return r;
}

template<typename T>
vector<T> to_vec(initializer_list<T> const& a){
	vector<T> r;
	for(auto x:a) r|=x;
	return r;
}

template<typename Collection>
auto enumerate_from(size_t start,Collection c){ return enumerate_from(start,to_vec(c)); }

template<typename T>
auto enumerate(T t){ return enumerate_from(0,t); }

template<typename T>
set<T>& operator|=(set<T> &a,set<T> b){
	for(auto elem:b) a|=elem;
	return a;
}

template<typename Func,typename T,size_t LEN>
auto mapf(Func f,array<T,LEN> a){
	array<decltype(f(a[0])),LEN> r;
	for(auto i:range_st<LEN>()){
		r[i]=f(a[i]);
	}
	return r;
}

template<typename Func,typename Collection>
auto mapv(Func f,Collection c){
	for(auto a:c) f(a);
}

template<typename T,size_t LEN1,size_t LEN2>
array<T,LEN1+LEN2> operator|(array<T,LEN1> a,array<T,LEN2> b){
	array<T,LEN1+LEN2> r;
	size_t i=0;
	auto add=[&](auto x){
		r[i++]=x;
	};
	mapv(add,a);
	mapv(add,b);
	return r;
}

template<typename T,size_t LEN>
vector<T>& operator|=(vector<T> &a,array<T,LEN> b){
	for(auto elem:b) a|=elem;
	return a;
}

template<typename T,size_t LEN>
vector<T> flatten(vector<array<T,LEN>> a){
	vector<T> r;
	for(auto x:a) r|=x;
	return r;
}

template<typename T,size_t LEN>
set<T> to_set(array<T,LEN> a){
	nyi
}

//program-specific stuff is below here.

using Team=int;

Team rand(Team*){
	return rand()%64;
}

//using Alliance=set<Team>;

struct Alliance{
	//set<Team> data;
	array<Team,3> data;

	//todo:make these explicit
	explicit Alliance(set<Team> s){
		//:data(s){}
		assert(s.size()==3);
		for(auto p:enumerate(s)) data[p.first]=p.second;
	}

	//Alliance(initializer_list<Team> a):data(a){}
	explicit Alliance(initializer_list<Team> a){
		assert(a.size()==3);
		for(auto p:enumerate(a)) data[p.first]=p.second;
	}

	explicit Alliance(array<Team,3> a):data(a){}

	auto begin()const{ return data.begin(); }
	auto end()const{ return data.end(); }
};

template<typename Func>
auto mapf(Func f,Alliance a){
	return mapf(f,a.data);
}

auto operator|(Alliance a,Alliance b){
	return a.data|b.data;
}

Alliance rand(Alliance*){
	Team *t;
	return Alliance{rand(t),rand(t),rand(t)};
}

Alliance to_alliance(vector<Team> v){
	return Alliance{to_set(v)};
}

Alliance to_alliance(array<Team,3> a){ return Alliance{a}; }

using Match=pair<Alliance,Alliance>;

Match rand(Match*){
	return make_pair(rand((Alliance*)0),rand((Alliance*)0));
}

using Schedule=vector<Match>;

Schedule rand(Schedule*){
	return mapf([](int){ return rand((Match*)0); },range(12));
}

using Ranking_points=int;

//using Current_standings=map<Team,Ranking_points>;

struct Current_standings{
	//map<Team,Ranking_points> r;
	unordered_map<Team,Ranking_points> r;

	auto& operator[](auto a){ return r[a]; }

	auto find(auto a){ return r.find(a); }
	auto find(auto a)const{ return r.find(a); }

	auto begin(){ return r.begin(); }
	auto begin()const{ return r.begin(); }

	auto end(){ return r.end(); }
	auto end()const{ return r.end(); }

	auto size()const{ return r.size(); }

	auto inc(Team team,Ranking_points amount){
		auto f=r.find(team);
		if(f==r.end()){
			r[team]=2;
		}else{
			f->second+=2;
		}
	}
};

ostream& operator<<(ostream& o,Current_standings const& a){
	return o<<a.r;
}

vector<Team> keys(Current_standings const& a){
	return keys(a.r);
}

Current_standings rand(Current_standings*){
	Current_standings r;
	for(auto i:range_st<10>()){
		r[rand((Team*)0)]=rand((Ranking_points*)0);
	}
	return r;
}

Current_standings update(Current_standings in,Alliance const& win){
	for(auto team:win){
		in.inc(team,2);
	}
	return in;
}

Current_standings tied(Current_standings standings,Alliance a,Alliance b){
	for(auto team:a|b){
		standings.inc(team,1);
	}
	return standings;
}

/*vector<Current_standings> play_match(Current_standings standings,Match match){
	auto a=match.first;
	auto b=match.second;
	vector<Current_standings> r;
	r|=update(standings,a);
	r|=update(standings,b);
	r|=tied(standings,a,b);
	return r;
}*/

array<Current_standings,3> play_match(Current_standings standings,Match match){
	auto a=match.first;
	auto b=match.second;
	return {
		update(standings,a),
		update(standings,b),
		tied(standings,a,b)
	};
}

vector<Current_standings> remaining(Current_standings standings,vector<Match> matches){
	if(matches.empty()) return {standings};
	vector<Current_standings> r;
	for(auto x:play_match(standings,matches[0])){
		r|=remaining(x,tail(matches));
	}
	return r;
}

auto appearing_teams(Match match){
	return match.first|match.second;
}

set<Team> appearing_teams(Schedule sched){
	return to_set(flatten(MAP(appearing_teams,sched)));
}

using Outcome=vector<Ranking_points>;
using Rank=size_t;

Outcome win(Outcome out,Alliance a){
	for(auto team:a) out[team]+=2;
	return out;
}

auto teams(Match m){
	return m.first|m.second;
}

Outcome tie(Outcome out,Match m){
	for(auto team:teams(m)) out[team]++;
	return out;
}

array<Outcome,3> play(Outcome current,Match match){
	return {
		win(current,match.first),
		win(current,match.second),
		tie(current,match)
	};
}

//assuming that matches has already been changed to the dense team numbers
vector<Outcome> update_rankings(Outcome current,Schedule matches){
	if(matches.empty()) return {current};
	vector<Outcome> r;
	for(auto out:play(current,matches[0])){
		r|=update_rankings(out,tail(matches));
	}
	return r;
}

template<typename Func,typename A,typename B>
auto mapf(Func f,pair<A,B> p)->pair<decltype(f(p.first)),decltype(f(p.second))>{
	return make_pair(f(p.first),f(p.second));
}

template<typename Func,typename T>
vector<T> mapf(Func f,set<T> s){
	vector<T> r;
	for(auto a:s) r|=f(a);
	return r;
}

template<typename Func>
void visit_result(Func f,Outcome const& current,Schedule::const_iterator matches_start,Schedule::const_iterator matches_end){
	if(matches_start==matches_end){
		f(current);
		return;
	}

	for(auto out:play(current,*matches_start)){
		visit_result(f,out,matches_start+1,matches_end);
	}
}

template<typename A,typename B>
vector<pair<B,A>> swap_pairs(vector<pair<A,B>> v){
	vector<pair<B,A>> r;
	r.reserve(v.size());
	for(auto p:v) r|=make_pair(p.second,p.first);
	return r;
}

template<typename T>
vector<pair<T,size_t>> enumerate_back(vector<T> const& a){
	vector<pair<T,size_t>> r;
	for(size_t i=0;i<a.size();i++) r|=make_pair(a[i],i);
	return r;
}

vector<Current_standings> possible(Current_standings standings,Schedule matches){
	//first, convert the team numbers to aliases that are densely in the range 0-(num teams-1)
	auto teams=to_vec(to_set(keys(standings))|appearing_teams(matches));
	PRINT(teams.size());

	//indexed by the team's location in 'teams'
	Outcome r;
	for(auto team:teams){
		r|=[&](){
			auto f=standings.find(team);
			if(f==standings.end()){
				return 0;
			}
			return f->second;
		}();
	}

	auto to_ind2=[&](Team t)->Team{
		for(auto p:enumerate(teams)){
			if(p.second==t) return p.first;
		}
		nyi
	};

	auto to_ind1=[&](Alliance a)->Alliance{
		return to_alliance(MAP(to_ind2,a));
	};

	auto to_ind=[&](Match a)->Match{
		return MAP(to_ind1,a);
	};

	Schedule matches_ind=MAP(to_ind,matches);

	//vector<Outcome> possible_by_index=update_rankings(r,matches_ind);

	//vector<Outcome> possible_by_index;
	//visit_result([&](Outcome a){ possible_by_index|=a; },r,matches_ind);

	//could decide to do more of the processing in this mode.

	/*vector<vector<Rank>> rankings;
	for(auto team:teams) rankings|={};

	for(auto outcome:possible_by_index){
		auto p=swap_pairs(enumerate(outcome));
		nyi
	}*/

	auto from_ind=[&](Outcome a)->Current_standings{
		Current_standings r;
		for(auto p:enumerate(a)){
			auto team=teams[p.first];
			auto rp=p.second;
			r[team]=rp;
		}
		return r;
	};

	{
		vector<vector<Rank>> ranks;//by team list of the rankings that have got
		for(auto team:teams) ranks|=vector<Rank>{};
		visit_result(
			[&](Outcome a){
				auto s=enumerate_from(//rank,(rp,team ind)
					1,
					sorted(//(rp,team ind) in the right order
						swap_pairs(//(rp,team ind)
							enumerate(a) //(team ind,rp)
						)
						//enumerate_back(a)
					)
				);
				for(auto p:s){
					auto rank=p.first;
					auto team=p.second.second;
					assert(team>=0 && team<teams.size());
					ranks[team]|=rank;
				}
				return 0;
			},
			r,
			begin(matches_ind),
			end(matches_ind)
		);

		for(auto p:enumerate(teams)){
			auto i=p.first;
			auto team=p.second;
			cout<<"Team "<<team<<":"<<min(ranks[i])<<" "<<median(ranks[i])<<" "<<max(ranks[i])<<"\n";
		}

		exit(0);
	}

	/*{
		vector<Current_standings> out;
		visit_result([&](Outcome a){ out|=from_ind(a); },r,matches_ind);
		return out;
	}*/

	//return mapf(from_ind,possible_by_index);
	/*vector<Current_standings> r;
	for(auto outcome:possible_by_index){
		Current_standings st;
		
		r|=st;
	}*/

	//team index->list of rankings
	/*vector<vector<Result>> r;
	for(auto out:possible_by_index){
		
	}*/
	/*PRINT(x)
	for(auto a:x){
		nyi
	}*/
	nyi
}

int main(){
	auto current=rand((Current_standings*)0);
	auto remaining1=rand((Schedule*)nullptr);
	PRINT(current);
	//PRINT(remaining);
	//PRINT(play_match(current,remaining1[0]));
	//auto x=remaining(current,remaining1);
	auto x=possible(current,remaining1);
	PRINT(x.size())
	//PRINT(x)
	//PRINT(typeid(MAP(keys,x)).name());
	auto teams=to_set(flatten(MAP(keys,x)));
	//PRINT(teams);
	map<Team,vector<Rank>> finishes;

	for(auto result:x){
		//sort the results and then assign that number to each team
		vector<pair<Ranking_points,Team>> r;
		for(auto p:result){
			r|=make_pair(p.second,p.first);//reverse(p);
		}
		auto s=sorted(r);
		for(auto p:enumerate_from(1,s)){
			auto rank=p.first;
			auto team=p.second.second;
			finishes[team]|=rank;
		}
	}

	for(auto team:teams){
		//PRINT(team);
		auto places=finishes[team];/*mapf(
			[team](auto const& a)->int{
				auto f=a.find(team);
				if(f==a.end()) return a.size();//if not found then say lower than everyone else
				return f->second;
			},
			x
		);*/
		cout<<"Team "<<team<<": "<<min(places)<<" "<<median(places)<<" "<<max(places)<<"\n";
		//PRINT(sorted(places))
	}
}
