#include<iostream>
#include<set>
#include<vector>
#include<stdlib.h>
#include<array>
#include<algorithm>
#include<cassert>
#include<sstream>
#include<map>

using namespace std;

/*
Simplifying assumptions
only two actions are scoring balls & crossing barriers
they just take time

todo list:
-make the distribution of team capbilit
*/

#define nyi { cout<<"NYI "<<__LINE__<<"\n"; exit(44); }

string as_string(auto a){
	stringstream ss;
	ss<<a;
	return ss.str();
}

template<typename K,typename V>
ostream& operator<<(ostream& o,map<K,V> const& m){
	o<<"{ ";
	for(auto const& a:m) o<<a<<" ";
	return o<<"}";
}

template<typename T>
vector<T>& operator|=(vector<T>& a,T t){
	a.push_back(t);
	return a;
}

template<typename A,typename B>
auto zip(A a,B b)->vector<pair<ELEM(a),ELEM(b)>>{
	auto ai=begin(a);
	auto bi=begin(b);
	using P=pair<ELEM(a),ELEM(b)>;
	vector<P> r;
	for(;ai!=end(a) && bi!=end(b);ai++,bi++){
		r|=P(*ai,*bi);
	}
	return r;
}

template<typename T>
T max(vector<T> v){
	assert(v.size());
	T r=v[0];
	for(auto elem:v) r=max(r,elem);	
	return r;
}

template<typename T>
T min(vector<T> v){
	assert(v.size());
	T r=v[0];
	for(auto elem:v) r=min(r,elem);
	return r;
}

/*auto max(auto c)->ELEM(c){
	nyi
}*/

/*template<typename T>
vector<T> sorted(vector<T> t){
	sort(begin(t),end(t));
	return t;
}*/

template<typename T>
T sorted(T t){
	sort(begin(t),end(t));
	return t;
}

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> p){
	o<<"(";
	o<<p.first<<","<<p.second;
	return o<<")";
}

template<typename T>
ostream& operator<<(ostream& o,vector<T> const& v){
	o<<"[";
	for(auto elem:v) o<<elem;
	return o<<"]";
}

template<typename Func,typename Collection>
auto mapf(Func f,Collection c){
	using T=decltype(f(*begin(c)));
	vector<T> r;
	for(auto a:c) r|=f(a);
	return r;
}

#define INSTANTIATE(A,B) A B;

#define COMPARE(A,B) if(a.B<b.B) return 1; if(b.B<a.B) return 0;
#define COMPARE_TYPE(NAME,MEMBERS) bool operator<(NAME a,NAME b){\
	MEMBERS(COMPARE)\
	return 0;\
}

#define PRINT(A,B) o<<""#B<<":"<<a.B<<" ";

vector<unsigned> range(unsigned lim){
	vector<unsigned> r;
	for(unsigned i=0;i<lim;i++) r|=i;
	return r;
}

template<typename T>
auto sum(T c)->ELEM(c){
	ELEM(c) total{};
	for(auto elem:c) total+=elem;
	return total;
}

template<typename T>
auto mean(vector<T> c)->ELEM(c){
	assert(c.size());
	return sum(c)/c.size();
}

template<typename Collection>
auto median(Collection c){
	assert(c.size());
	return sorted(c)[c.size()/2];
}

template<typename T>
T q1(vector<T> v){
	assert(v.size());
	return sorted(v)[v.size()/4];
}

template<typename T>
T q3(vector<T> v){
	assert(v.size());
	return sorted(v)[v.size()*3/4];
}

template<typename T>
T mode(vector<T> v){
	auto m=to_multiset(move(v));
	auto cnt=max(mapf([&](auto elem){ return m.count(elem); },m));
	for(auto elem:m){
		if(m.count(elem)==cnt) return elem;
	}
	assert(0);
}

//Game-specific stuff starts here
using Ball_count=unsigned;
using Crossing_count=unsigned;

#define ROBOT_ITEMS(X) X(Ball_count,balls) X(Crossing_count,crossings)

struct Robot{
	ROBOT_ITEMS(INSTANTIATE)
};

COMPARE_TYPE(Robot,ROBOT_ITEMS)

#define EQ(A,B) if(a.B!=b.B) return 0;

bool operator==(Robot a,Robot b){
	ROBOT_ITEMS(EQ)
	return 1;
}

ostream& operator<<(ostream& o,Robot const& a){
	o<<"Robot( ";
	ROBOT_ITEMS(PRINT)
	return o<<")";
}

static const auto BALL_LIMIT=6;
static const auto CROSS_LIMIT=8;

Robot robot_random(){
	return Robot{Ball_count(rand()%BALL_LIMIT),Crossing_count(rand()%CROSS_LIMIT)};
}

set<Robot> calc_robots(){
	set<Robot> r;
	for(auto balls:range(BALL_LIMIT)) for(auto crossings:range(CROSS_LIMIT)){
		r|=Robot{Ball_count(balls),Ball_count(crossings)};
	}
	return r;
}

static const set<Robot> ROBOTS=calc_robots();

//using Alliance=array<Robot,3>;

template<typename T,size_t LEN>
class sorted_array{
	public:
	using inner=array<T,LEN>;
	using iterator=typename inner::iterator;

	private:
	inner data_;

	public:
	sorted_array(inner a):data_(sorted(a)){}

	inner const& data()const{ return data_; }

	iterator begin(){ return ::begin(data_); }
	iterator end(){ return ::end(data_); }

	T const& operator[](size_t i)const{ return data_[i]; }
};

template<typename T,size_t LEN>
bool operator<(sorted_array<T,LEN> const& a,sorted_array<T,LEN> const& b){
	return a.data()<b.data();
}

template<typename T,size_t LEN>
bool operator==(sorted_array<T,LEN> const& a,sorted_array<T,LEN> const& b){
	return a.data()==b.data();
}

template<typename T,size_t LEN>
ostream& operator<<(ostream& o,sorted_array<T,LEN> const& a){
	return o<<a.data();
}

using Alliance=sorted_array<Robot,3>;

Alliance alliance_random(){
	return Alliance{{robot_random(),robot_random(),robot_random()}};
}

set<Alliance> calc_alliances(){
	set<Alliance> r;
	for(auto a:ROBOTS) for(auto b:ROBOTS) for(auto c:ROBOTS){
		r|=Alliance{{a,b,c}};
	}
	return r;
}

static const set<Alliance> ALLIANCES=calc_alliances();

struct Robot_strategy{
	ROBOT_ITEMS(INSTANTIATE)
};

COMPARE_TYPE(Robot_strategy,ROBOT_ITEMS)

ostream& operator<<(ostream& o,Robot_strategy a){
	o<<"Robot_strategy( ";
	ROBOT_ITEMS(PRINT)
	return o<<")";
}

set<Robot_strategy> strategies(Robot a){
	set<Robot_strategy> r;
	if(a.balls){
		for(Ball_count balls=0;balls<=a.balls;balls++){
			auto frac=(a.balls-balls)/float(a.balls);
			r|=Robot_strategy{balls,Crossing_count(frac*a.crossings)};
		}
	}else{
		r|=Robot_strategy{0,a.crossings};
	}
	return r;
}

using Alliance_strategy=array<Robot_strategy,3>;

template<typename T>
vector<vector<T>> cross(vector<vector<T>> const& v){
	vector<vector<T>> r;
	nyi
	return r;
}

template<typename A,typename B>
auto cross(A,B){ return 0; }

template<typename A,typename B,typename C>
vector<array<Robot_strategy,3>> cross(A a,B b,C c){
	vector<array<Robot_strategy,3>> r;
	for(auto a1:a) for(auto b1:b) for(auto c1:c){
		r|=Alliance_strategy{a1,b1,c1};
	}
	return r;
}

set<Alliance_strategy> strategies(Alliance a){
	auto m=MAP(strategies,a);
	auto c=cross(move(m[0]),move(m[1]),move(m[2]));
	return to_set(move(c));
}

#define MATCH_RESULT_ITEMS(X) X(unsigned,ranking_points) X(int,score)

struct Match_result{
	MATCH_RESULT_ITEMS(INSTANTIATE)
};

COMPARE_TYPE(Match_result,MATCH_RESULT_ITEMS)

#define PLUS_EQ(A,B) a.B+=b.B;

Match_result& operator+=(Match_result& a,Match_result b){
	MATCH_RESULT_ITEMS(PLUS_EQ)
	return a;
}

Match_result operator-(Match_result a,Match_result b){
	#define X(A,B) a.B-=b.B;
	MATCH_RESULT_ITEMS(X)
	#undef X
	return a;
}

#define DIV_EQ(A,B) a.B/=b;

Match_result operator/(Match_result a,auto b){
	MATCH_RESULT_ITEMS(DIV_EQ)
	return a;
}

ostream& operator<<(ostream& o,Match_result a){
	o<<"Match_result( ";
	MATCH_RESULT_ITEMS(PRINT)
	return o<<")";
}

Match_result value(unsigned opponent_score,Alliance_strategy a){
	auto balls=a[0].balls+a[1].balls+a[2].balls;
	Crossing_count crossings=a[0].crossings+a[1].crossings+a[2].crossings;
	auto counted_crossings=min(Crossing_count(10),crossings);
	static const unsigned BALL_VALUE=5;//2=low goal, 5=high goal
	int score=5*counted_crossings+balls*BALL_VALUE;
	unsigned ranking_points=(score>opponent_score)*2+(crossings>=8)+(balls>=8);
	return Match_result{ranking_points,score};
}

template<typename C>
void print_lines(C c){
	for(auto a:c){
		cout<<a<<"\n";
	}
}

template<typename A,typename B>
void print_lines(pair<A,B> const& p){
	cout<<p.first<<"\n";
	cout<<p.second<<"\n";
}

auto value_and_how(unsigned opponent_score,Alliance a){
	return max(mapf(
		[=](auto x){ return make_pair(value(opponent_score,x),x); },
		strategies(a)
	));
}

Match_result value(unsigned opponent_score,Alliance a){
	return max(mapf(
		[=](auto x){ return value(opponent_score,x); },
		strategies(a)
	));
}

Robot improve_ball(Robot r){
	nyi
}

Robot improve_crossing(Robot r){
	nyi
}

array<Alliance,6> improved(Alliance a){
	return array<Alliance,6>{
		Alliance{{improve_ball(a[0]),a[1],a[2]}},
		Alliance{{a[0],improve_ball(a[1]),a[2]}},
		Alliance{{a[0],a[1],improve_ball(a[2])}},
		Alliance{{improve_crossing(a[0]),a[1],a[2]}},
		Alliance{{a[0],improve_crossing(a[1]),a[2]}},
		Alliance{{a[0],a[1],improve_crossing(a[2])}},
	};
}

#define LIST(A,B) B,
enum class Robot_ability{ ROBOT_ITEMS(LIST) };

ostream& operator<<(ostream& o,Robot_ability a){
	#define X(A,B) if(a==Robot_ability::B) return o<<""#B;
	ROBOT_ITEMS(X)
	#undef X
	assert(0);
}

static const vector<Robot_ability> ROBOT_ABILITIES{
	#define X(A,B) Robot_ability::B,
	ROBOT_ITEMS(X)
	#undef X
};

#define ALLIANCE_IMPROVEMENT_ITEMS(X) X(unsigned,robot) X(Robot_ability,ability)

struct Alliance_improvement{
	ALLIANCE_IMPROVEMENT_ITEMS(INSTANTIATE)
};

using Alliance_ability=Alliance_improvement;

#define OUT(NAME,MEMBERS) ostream& operator<<(ostream& o,NAME const& a){\
	o<<""#NAME<<"(";\
	MEMBERS(PRINT)\
	return o<<")";\
}

OUT(Alliance_improvement,ALLIANCE_IMPROVEMENT_ITEMS)

COMPARE_TYPE(Alliance_improvement,ALLIANCE_IMPROVEMENT_ITEMS)

vector<Alliance_improvement> alliance_improvements(){
	vector<Alliance_improvement> r;
	for(auto robot:range(3)){
		for(auto ability:ROBOT_ABILITIES){
			r|=Alliance_improvement{robot,ability};
		}
	}
	return r;
}

unsigned get(Robot_ability ability,Robot robot){
	#define X(A,B) if(ability==Robot_ability::B) return robot.B;
	ROBOT_ITEMS(X)
	#undef X
	assert(0);
}

unsigned get(Alliance_ability imp,Alliance a){
	return get(imp.ability,a[imp.robot]);
}

Robot set1(Robot_ability ab,unsigned value,Robot r){
	#define X(A,B) if(ab==Robot_ability::B){ r.B=value; return r; }
	ROBOT_ITEMS(X)
	#undef X
	assert(0);
}

Alliance set1(Alliance_ability ab,unsigned value,Alliance a){
	//a[ab.robot]=set1(ab.ability,value,a[ab.robot]);
	auto in=a.data();
	in[ab.robot]=set1(ab.ability,value,a[ab.robot]);
	return Alliance{in};
/*	cout<<"x:"<<x<<"\n";
	a[ab.robot]=x;
	cout<<"to ret:"<<a<<"\n";
	return a;*/
}

map<Alliance_improvement,Match_result> marginal_utility(Alliance a){
	auto value1=[](auto a){ return value(33,a); };
	map<Alliance_ability,Match_result> r;
	auto im=alliance_improvements();
	for(auto item:im){
		auto g=get(item,a);
		//cout<<"alliance:"<<a<<"\n";
		//cout<<"getting:"<<item<<" value:"<<g<<"\n";
		auto after=set1(item,g+1,a);
		//cout<<"after:"<<after<<"\n";
		if(after==a)nyi
		auto improvement=value1(after)-value1(a);
		r[item]=improvement;
	}
	return r;
}

struct Tree{
	string data;
	vector<Tree> in;
};

template<typename A,typename B>
Tree as_tree(pair<A,B> p){
	return Tree{"pair",{as_tree(p.first),as_tree(p.second)}};
}

template<typename T,size_t LEN>
Tree as_tree(array<T,LEN> const& a){
	return Tree{"array",MAP(as_tree,a)};
}

template<typename T,size_t LEN>
Tree as_tree(sorted_array<T,LEN> const& a){
	return as_tree(a.data());
}

Tree as_tree(unsigned i){
	return Tree{as_string(i),{}};
}

#define AS_TREE(A,B) Tree{""#B,{as_tree(a.B)}},

Tree as_tree(Robot_ability a){ return Tree{as_string(a),{}}; }

#define AS_TREE_MAC(NAME,MEMBERS) Tree as_tree(NAME const& a){\
	return Tree{""#NAME,{MEMBERS(AS_TREE)}};\
}

AS_TREE_MAC(Alliance_ability,ALLIANCE_IMPROVEMENT_ITEMS)
AS_TREE_MAC(Match_result,MATCH_RESULT_ITEMS)
AS_TREE_MAC(Robot,ROBOT_ITEMS)
AS_TREE_MAC(Robot_strategy,ROBOT_ITEMS)

template<typename K,typename V>
Tree as_tree(map<K,V> const& m){
	return Tree{
		"map",
		MAP(as_tree,m)
	};
}

template<typename T>
Tree as_tree(vector<T> const& v){
	return Tree{"vector",MAP(as_tree,v)};
}

template<typename A,typename B,typename C>
Tree as_tree(tuple<A,B,C> const& t){
	return Tree{
		"tuple",
		{as_tree(get<0>(t)),as_tree(get<1>(t)),as_tree(get<2>(t))}
	};
}

template<typename A,typename B,typename C,typename D,typename E>
Tree as_tree(tuple<A,B,C,D,E> const& t){
	return Tree{
		"tuple",
		{
			as_tree(get<0>(t)),
			as_tree(get<1>(t)),
			as_tree(get<2>(t)),
			as_tree(get<3>(t)),
			as_tree(get<4>(t))
		}
	};
}

/*Tree as_tree(auto a){
	cout<<decltype(a)<<"\n";
	nyi
}*/

void print_tree(unsigned indent,Tree const& t){
	for(auto _:range(indent)) cout<<"\t";
	cout<<t.data<<"\n";
	for(auto a:t.in){
		print_tree(indent+1,a);
	}
}

void print_tree(auto a){
	print_tree(0,as_tree(a));
}

template<typename K,typename V>
vector<pair<K,V>> to_pairs(map<K,V> m){
	vector<pair<K,V>> r;
	for(auto p:m) r|=make_pair(p.first,p.second);
	return r;
}

template<typename A,typename B>
vector<pair<B,A>> swap_pairs(vector<pair<A,B>> v){
	vector<pair<B,A>> r;
	for(auto p:v) r|=make_pair(p.second,p.first);
	return r;
}

template<typename K,typename V>
K max_value_key(map<K,V> const& m){
	assert(m.size());
	return max(swap_pairs(to_pairs(m))).second;
}

Alliance inc(Alliance alliance,Alliance_ability ab){
	return set1(ab,get(ab,alliance)+1,alliance);
}

template<typename A,typename B,typename C>
ostream& operator<<(ostream& o,tuple<A,B,C> const& a){
	return o<<"("<<get<0>(a)<<","<<get<1>(a)<<","<<get<2>(a)<<")";
}

template<typename A,typename B,typename C,typename D,typename E>
ostream& operator<<(ostream& o,tuple<A,B,C,D,E> const& a){
	o<<"("<<get<0>(a)<<","<<get<1>(a)<<","<<get<2>(a);
	return o<<","<<get<3>(a)<<","<<get<4>(a)<<")";
}

pair<int,int> as_pair(Match_result a){
	return make_pair(a.ranking_points,a.score);
}

int main_multi(){
	/*auto a=alliance_random();
	cout<<a<<"\n";
	auto b=strategies(a);
	cout<<b.size()<<"\n";
	auto s=sorted(zip(MAP([](auto x){ return value(33,x); },b),b));*/
	//cout<<s<<"\n";
	//print_lines(s);
//	print_lines(alliances());
	cout<<"Alliances:"<<ALLIANCES.size()<<"\n";

	auto run=[&](unsigned opponent_score){
		auto m=mapf([=](auto x){ return value(opponent_score,x); },ALLIANCES);
		#define X(NAME) cout<<pad_to_width(7,""#NAME)<<NAME(m)<<"\n";
		X(min)
		X(q1) X(median) X(q3)
		X(max)
		X(mean)
		X(mode)
		#undef X
		return mean(m).score;
	};

	cout<<"Maximizing scores:\n";
	auto r=run(0);
	cout<<"\nMaximizing rank:\n";
	run(r);

	auto m2=zip(MAP(marginal_utility,ALLIANCES),ALLIANCES);
	auto m3=mapf(
		[=](auto p){
			auto util=p.first;
			auto base=p.second;
			auto best_change=max_value_key(util);
			auto best=inc(base,best_change);
			return make_tuple(
				value(r,best)-value(r,base),
				base,
				max_value_key(util),
				value_and_how(r,best),
				value_and_how(r,base)
			);
		},
		m2
	);
	//cout<<m3<<"\n";
//	print_tree(m3);
	print_tree(max(m3));

	//calculate the average change for each of the change types
	map<Alliance_ability,vector<Match_result>> by_change;
	for(auto p:m2){
		auto m=p.first;
		auto base=p.second;
		//auto result_change=get<0>(x);
		//auto input_change=get<2>(
		for(auto p1:m){
			by_change[p1.first]|=p1.second;
		}
	}
	for(auto p:by_change){
		auto k=p.first;
		auto v=p.second;
		cout<<k<<"\t"<<as_pair(mean(v))<<" "<<as_pair(median(v))<<"\n";
	}

	//print_lines(max(m3));
	//auto m3=max(m2);
	//cout<<"orig value:"<<value(33,m3);
	//print_lines(max(m2));
	//print_tree(max(m2));

	//limits, what is the average score & what is the average number of ranking points
	//for each of them, what is the marginal value of one extra ball shot or one extra barrier breached for an individual robot (on average or for an average robot)

	//cout<<"v0:"<<value_and_how(33,Alliance{{Robot{0,7},Robot{0,7},Robot{5,2}}})<<"\n";
	//cout<<"v1:"<<value_and_how(33,Alliance{{Robot{1,7},Robot{0,7},Robot{5,2}}})<<"\n";

}

template<typename Func>
void disp(Func func){
	int cross_lim=14;
	int ball_lim=cross_lim+10;
	cout<<"\t\tCrossings\n";
	cout<<"\t\t";
	for(auto i:range(cross_lim)) cout<<i<<"\t";
	cout<<"\n";

	for(auto balls:range(ball_lim)){
		if(balls==0){
			cout<<"Balls";
		}
		cout<<"\t";
		cout<<balls<<"\t";
		for(auto crossings:range(cross_lim)){
			cout<<func(balls,crossings)<<"\t";
		}
		cout<<"\n";
	}
}

void single_bot(){
	auto par=33;
	cout<<"Total result:\n";
	disp([=](Ball_count balls,Crossing_count crossings){
		Alliance a{{Robot{balls,crossings},Robot{0,0},Robot{0,0}}};
		return as_pair(value(par,a));
	});
	cout<<"Value of extra ball:\n";
	disp([=](Ball_count balls,Crossing_count crossings){
		Alliance a{{Robot{balls,crossings},Robot{0,0},Robot{0,0}}};
		Alliance b{{Robot{balls+1,crossings},Robot{0,0},Robot{0,0}}};
		return as_pair(value(par,b)-value(par,a));
	});
	cout<<"Value of extra crossing:\n";
	disp([=](Ball_count balls,Crossing_count crossings){
		Alliance a{{Robot{balls,crossings},Robot{0,0},Robot{0,0}}};
		Alliance b{{Robot{balls,crossings+1},Robot{0,0},Robot{0,0}}};
		return as_pair(value(par,b)-value(par,a));
	});
}

int main(){
	single_bot();
	//main_multi();
	return 0;
}
