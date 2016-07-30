#include <iostream>
#include <map>
#include <cassert>
#include <algorithm>
#include "common.h"

using namespace std;

#define RM_CONST(X) typename std::remove_const<X>::type
#define ELEM(X) RM_CONST(typename std::remove_reference<decltype(*begin(X))>::type)

template<typename T>
std::ostream& operator<<(std::ostream& o,std::vector<T> const& v){
        o<<"[";
        for(typename std::vector<T>::const_iterator at=v.begin();at!=v.end();++at){
                o<<*at;
                if(at+1!=v.end()) o<<",";
        }
        return o<<"]";
}

template<typename A,typename B>
std::ostream& operator<<(std::ostream& o,std::pair<A,B> const& p){
        return o<<"("<<p.first<<","<<p.second<<")";
}

template<typename Func,typename Collection>
auto mapf(Func f,Collection const& c)->std::vector<decltype(f(*begin(c)))>{
        std::vector<decltype(f(*begin(c)))> r;
        for(auto &e:c) r|=f(e);
        return r;
}

//This macro exists to work around the fact that mapf won't work right for functions that have multiple definitions depending on the type.
#define MAP(func,collection) mapf( \
        [&](typename std::remove_reference<decltype(*begin(collection))>::type const& x){ return func(x); }, \
                collection \
                        )

template<typename T>
auto take(unsigned lim,T const& v)->std::vector<ELEM(v)>{
        std::vector<ELEM(v)> r;
        auto at=begin(v);
        auto end=std::end(v);
        for(unsigned i=0;i<lim && at!=end;i++,++at){
                r|=*at;
        }
        return r;
}

template<typename T>
std::vector<T> skip(unsigned i,std::vector<T> const& v){
        std::vector<T> r;
        for(;i<v.size();i++) r|=v[i];
        return r;
}

template<typename T>
T sum(std::vector<T> const& v){
        T t=0;
        for(auto &a:v) t+=a;
        return t;
}

template<typename T>
T mean(std::vector<T> const& v){
        assert(v.size());
        return sum(v)/v.size();
}

template<typename T>
vector<T> choose(vector<T> v,size_t len){
	assert(len<=v.size());
	vector<T> r;
	while(len){
		auto i=rand()%v.size();
		r|=v[i];
		v.erase(v.begin()+i);
		len--;
	}
	return r;
}

std::vector<unsigned> range(unsigned u){
        std::vector<unsigned> r;
        for(unsigned i=0;i<u;i++){
                r|=i;
        }
        return r;
}

template<typename T>
void print_lines(T t){
	for(auto elem:t) std::cout<<elem<<"\n";
}

template<typename A,typename B,typename C,typename D>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C,D> const& t){
        return o<<"("<<std::get<0>(t)<<","<<std::get<1>(t)<<","<<std::get<2>(t)<<","<<get<3>(t)<<")";
}

template<typename A,typename B,typename C,typename D,typename E>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C,D,E> const& t){
        return o<<"("<<std::get<0>(t)<<","<<std::get<1>(t)<<","<<std::get<2>(t)<<","<<get<3>(t)<<","<<get<4>(t)<<")";
}

template<typename T>
auto enumerate(T v)->std::vector<std::pair<size_t,typename std::remove_reference<decltype(*begin(v))>::type>>{
        std::vector<std::pair<size_t,typename std::remove_reference<decltype(*begin(v))>::type>> r;
        size_t i=0;
        for(auto a:v){
                r|=std::make_pair(i,a);
                i++;
        }
        return r;
}

template<typename A,typename B,typename C,typename D,typename E>
tuple<A,B,C,D,E> flatten(pair<A,tuple<B,C,D,E>> p){
	return make_tuple(p.first,get<0>(p.second),get<1>(p.second),get<2>(p.second),get<3>(p.second));
}

template<typename T>
std::vector<T> sorted(std::vector<T> in){
        sort(begin(in),end(in));
        return in;
}

int main(){
	srand(time(NULL));

	static const int teams=10;
	const auto team_ids=range(teams);
	static const int matches=5;
	using Team=unsigned int;
	map<Team,int> skill_levels;
	for(auto team:team_ids){
		skill_levels[team]=rand()%5;
	}

	auto alliance_score=[&](vector<Team> v){
		return sum(mapf([&](auto t){ return skill_levels[t]; },v));
	};

	using Alliance=vector<Team>;
	using Score=int;
	vector<tuple<Alliance,Alliance,Score,Score>> match_results;
	for(auto i:range(matches)){
		auto t=choose(team_ids,6);
		auto t1=take(3,t);
		auto t2=skip(3,t);
		auto t1_score=alliance_score(t1);
		auto t2_score=alliance_score(t2);
		match_results|=make_tuple(t1,t2,t1_score,t2_score);
	}

	cout<<"True skill levels:\n";
	print_lines(skill_levels);

	cout<<"\nMatch outcomes:\n";
	print_lines(MAP(flatten,enumerate(match_results)));
	//	cout<<i<<"\t"<<t1<<"\t"<<t2<<"\t"<<t1_score<<"\t"<<t2_score<<"\n";

	//first, make pairs of alliance and score
	//then make pairs of team and score
	//then sort by team & find averages
	map<Team,vector<Score>> by_team;
	for(auto m:match_results){
		auto a1=get<0>(m);
		auto a2=get<1>(m);
		auto a1_score=get<2>(m);
		auto a2_score=get<2>(m);
		auto add_alliance=[&](auto alliance,auto score){
			for(auto team:alliance) by_team[team]|=score;
		};
		add_alliance(a1,a1_score);
		add_alliance(a2,a2_score);
	}
	cout<<"\nResults by team:\n";
	print_lines(by_team);

	vector<pair<int,Team>> v;
	for(auto p:by_team){
		auto team=p.first;
		auto values=p.second;
		//cout<<team<<"\t"<<mean(values)<<"\n";
		v|=make_pair(mean(values),team);
	}
	cout<<"\naverage scores:\n";
	print_lines(sorted(v));
}
