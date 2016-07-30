#include<iostream>
#include<map>
#include<vector>
#include<cassert>

using namespace std;

/*
This is for calculating odds that teams can make it over an obstacle, with partial information
*/

#define nyi { cout<<"NYI "<<__LINE__<<"\n"; exit(44); }

#define RM_REF(X) typename remove_reference<X>::type
#define ELEM(X) RM_REF(decltype(*begin(X)))
#define PRINT(X) cout<<""#X<<":"<<X<<"\n";

template<typename Func,typename Collection>
auto filter(Func f,Collection c)->vector<ELEM(c)>{
	vector<ELEM(c)> r;
	for(auto elem:c){
		if(f(elem)) r|=elem;
	}
	return r;
}

template<typename T>
void print_lines(T t){
	for(auto a:t) cout<<a<<"\n";
}

template<typename T>
vector<T>& operator|=(vector<T>& v,T t){
	v.push_back(t);
	return v;
}

template<typename T>
auto firsts(T c)->vector<decltype(begin(c)->first)>{
	vector<decltype(begin(c)->first)> r;
	for(auto elem:c) r|=elem.first;
	return r;
}

template<typename T>
auto seconds(T c)->vector<decltype(begin(c)->second)>{
	vector<decltype(begin(c)->second)> r;
	for(auto elem:c) r|=elem.second;
	return r;
}

template<typename T>
T sum(vector<T> v){
	T r=0;
	for(auto i:v) r+=i;
	return r;
}

template<typename T>
ostream& operator<<(ostream& o,vector<T> const& v){
	o<<"[ ";
	for(auto a:v) o<<a<<" ";
	return o<<"]";
}

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> const& p){
	o<<"("<<p.first<<","<<p.second<<")";
}

template<typename K,typename V>
ostream& operator<<(ostream& o,map<K,V> const& m){
	o<<"{";
	for(auto p:m) o<<p;
	return o<<"}";
}

#define PIT_REPORT X(NONE) X(GOOD) X(BAD)

#define X(NAME) NAME,
enum Pit_report{PIT_REPORT};
#undef X

ostream& operator<<(ostream& o,Pit_report a){
	#define X(NAME) if(a==Pit_report::NAME) return o<<""#NAME;
	PIT_REPORT
	#undef X
	assert(0);
}

#define X(NAME) Pit_report::NAME,
static const vector<Pit_report> REPORTS{PIT_REPORT};
#undef X

//prior beleif about the rate at which robots will be able to pass the defense
static const float BASE_RATE=.2;

int basic(){
	int others_known_to_pass=2;
	int others_known_to_fail=1;
	int event_size=32;

	auto expected_pass=BASE_RATE*event_size;
	auto expected_fail=(1-BASE_RATE)*event_size;
	auto expected_pass_left=max(0.0f,(expected_pass-others_known_to_pass));
	auto expected_fail_left=max(0.0f,(expected_fail-others_known_to_fail));
	auto total_left=expected_pass_left+expected_fail_left;
	if(total_left==0){
		cout<<"Error: all robots accounted for!\n";
		return 1;
	}
	auto residual_pass_rate=expected_pass_left/total_left;
	cout<<"residual pass:"<<residual_pass_rate<<"\n";
	return 0;
}

using Perf=Pit_report;

struct Team_category{
	Perf perf;
	Pit_report pit;
};

bool operator<(Team_category const& a,Team_category const& b){
	if(a.perf<b.perf) return 1;
	if(b.perf<a.perf) return 0;
	return a.pit<b.pit;
}

ostream& operator<<(ostream& o,Team_category const& a){
	o<<"(perf:"<<a.perf<<" pit:"<<a.pit<<")";
	return o;
}

static const map<Team_category,int> teams_by_category{
	{
		{Perf::NONE,Pit_report::NONE},
		20
	},
	{
		{Perf::NONE,Pit_report::GOOD},
		1
	},
	{
		{Perf::NONE,Pit_report::BAD},
		1
	},
	{
		{Perf::GOOD,Pit_report::NONE},
		1,
	},
	{
		{Perf::GOOD,Pit_report::GOOD},
		2
	},
	{
		{Perf::GOOD,Pit_report::BAD},
		0
	},
	{
		{Perf::BAD,Pit_report::GOOD},
		1
	},
	{
		{Perf::BAD,Pit_report::NONE},
		0
	},
	{
		{Perf::BAD,Pit_report::BAD},
		0
	}
};
int pitted(){
	int total_teams=sum(seconds(teams_by_category));
	if(total_teams<=0){
		cout<<"Error: total_teams:"<<total_teams<<"\n";
		return 1;
	}

	cout<<"Input data:\n";
	print_lines(teams_by_category);
	cout<<"\n";

	for(auto report:REPORTS){
		cout<<"Pit reported:"<<report<<"\n";
		auto f=filter([&](pair<const Team_category,int> p){ return p.first.pit==report; },teams_by_category);
		//cout<<f<<"\n";
		map<Pit_report,int> by_perf;
		for(auto a:f){
			by_perf[a.first.perf]=a.second;
		}
		auto total=sum(seconds(by_perf));
		map<Pit_report,float> odds;
		for(auto a:REPORTS){
			odds[a]=(0.0+by_perf[a])/total;
		}
		auto good=by_perf[Perf::GOOD];
		auto bad=by_perf[Perf::BAD];
		auto seen=good+bad;
		cout<<"\tcounts:  "<<by_perf<<"\n";
		cout<<"\tfraction:"<<odds<<"\n";
		if(seen){
			cout<<"\tof those seen:"<<(0.0+good)/seen<<"\n";
		}else{
			cout<<"\tnone actually seen\n";
		}
	}
	return 0;
}

template<typename T>
vector<float> products(vector<T> v){
	vector<float> r;
	for(auto p:v) r|=p.first*p.second;
	return r;
}

int combo(){
	int total_teams=sum(seconds(teams_by_category));
	if(total_teams<=0){
		cout<<"Error: total_teams:"<<total_teams<<"\n";
		return 1;
	}

	cout<<"Input data:\n";
	print_lines(teams_by_category);
	cout<<"\n";

	map<Pit_report,pair<int,float>> unknowns;

	for(auto report:REPORTS){
		cout<<"Pit reported:"<<report<<"\n";
		auto f=filter([&](pair<const Team_category,int> p){ return p.first.pit==report; },teams_by_category);
		//cout<<f<<"\n";
		map<Pit_report,int> by_perf;
		for(auto a:f){
			by_perf[a.first.perf]=a.second;
		}
		auto total=sum(seconds(by_perf));
		map<Pit_report,float> odds;
		for(auto a:REPORTS){
			odds[a]=(0.0+by_perf[a])/total;
		}
		auto good=by_perf[Perf::GOOD];
		auto bad=by_perf[Perf::BAD];
		auto seen=good+bad;
		cout<<"\tcounts:  "<<by_perf<<"\n";
		cout<<"\tfraction:"<<odds<<"\n";
		float est=0;
		if(seen){
			est=(0.0+good)/seen;
			cout<<"\tof those seen:"<<est<<"\n";
		}else{
			cout<<"\tnone actually seen\n";
		}
		unknowns[report]=make_pair(by_perf[Perf::NONE],est);
	}

	auto u=sum(firsts(seconds(unknowns)));
	auto known_good=sum(seconds(filter([&](pair<const Team_category,int> p){ return p.first.perf==Perf::GOOD; },teams_by_category)));
	auto known_bad=sum(seconds(filter([&](pair<const Team_category,int> p){ return p.first.perf==Perf::BAD; },teams_by_category)));

	auto expected_good=total_teams*BASE_RATE;
	auto expected_bad=total_teams*(1-BASE_RATE);

	auto residual_good=max(0.0f,expected_good-known_good);
	auto residual_bad=max(0.0f,expected_bad-known_bad);
	auto residual_total=residual_good+residual_bad;
	auto residual_rate=residual_total ? (residual_good/residual_total) : 0;

	auto unconditional_expected_good=sum(products(seconds(unknowns)));
	auto effective_unconditional_rate=unconditional_expected_good/sum(firsts(seconds(unknowns)));
	auto adjustment_constant=BASE_RATE/effective_unconditional_rate;

	map<Pit_report,float> adjusted_result;
	for(auto a:REPORTS){
		adjusted_result[a]=unknowns[a].second*adjustment_constant;
	}

	/*cout<<"Unknown robots:"<<u<<"\n";
	PRINT(known_good);
	PRINT(known_bad);
	PRINT(expected_good)
	PRINT(residual_rate)
	//PRINT(expected_bad)
	PRINT(unknowns)
	PRINT(unconditional_expected_good)
	PRINT(effective_unconditional_rate)
	PRINT(adjustment_constant)*/
	cout<<"Estimated probabilities, assuming the basic rate:\n";
	PRINT(adjusted_result)

	return 0;
}

int main(){
	//return basic();
	//return pitted();
	return combo();
}
