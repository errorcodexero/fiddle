#include<iostream>
#include<set>
#include<vector>
#include<cassert>
#include<sstream>

using namespace std;

template<typename T>
set<T>& operator|=(set<T> &s,T t){
	s.insert(t);
	return s;
}

template<typename T>
vector<T>& operator|=(vector<T>& v,T t){
	v.push_back(t);
	return v;
}

vector<unsigned> range(unsigned lim){
	vector<unsigned> r;
	for(unsigned i=0;i<lim;i++){
		r|=i;
	}
	return r;
}

template<typename T>
T max(set<T> s){
	assert(s.size());
	T r=*begin(s);
	for(auto elem:s){
		r=max(r,elem);
	}
	return r;
}

template<typename T>
T min(set<T> s){
	assert(s.size());
	T r=*begin(s);
	for(auto elem:s) r=min(r,elem);
	return r;
}

template<typename Func>
void write_image1(ostream& o,Func f){
	static const unsigned X=50,Y=8;
	set<unsigned> values;
	for(auto x:range(X)) for(auto y:range(Y)){
		values|=f(x,y);
	}
	auto full_scale=max(values);

	o<<"P6\n"<<X<<" "<<Y<<"\n255\n";
	for(unsigned y=0;y<Y;y++){
		for(unsigned x=0;x<X;x++){
			unsigned char t=max(0u,f(x,y))/(float)full_scale*255;
			cerr<<(int)t<<"\n";
			o<<t;
			o<<t;
			o<<(unsigned char)(255-t);
		}
	}
}

string first_word(string s){
	stringstream ss;
	for(unsigned i=0;i<s.size() && s[i]!=' ';i++){
		ss<<s[i];
	}
	return ss.str();
}

struct Tag{
	string name;

	explicit Tag(string s):name(first_word(s)){
		cout<<"<"<<s<<">\n";
	}

	~Tag(){ cout<<"</"<<name<<">\n"; }
};

char to_hex_dig(unsigned u){
	assert(u<16);
	if(u<10) return '0'+u;
	return 'a'-10+u;
}

string to_hex_char(unsigned char c){
	stringstream ss;
	ss<<to_hex_dig(c/16)<<to_hex_dig(c%16);
	return ss.str();
}

string take(unsigned i,string s){
	return s.substr(0,i);
}

template<typename Func>
void write_image(ostream& o,Func f){
	static const unsigned X=8,Y=40;
	set<decltype(f(1,2))> values;
	for(auto x:range(X)) for(auto y:range(Y)){
		values|=f(y,x);
	}
	auto min_val=min(values);
	auto full_scale=max(values);
	auto span=full_scale-min_val;

	//o<<"P6\n"<<X<<" "<<Y<<"\n255\n";
	Tag a("html");
	Tag b("body");
	Tag c("table border");
	{
		Tag a("tr");
		{
			Tag a("td colspan=2 rowspan=2");
		}
		Tag b("td colspan="+to_string(X));
		cout<<"Cans";
	}
	{
		Tag a("tr");
		for(auto x:range(X)){
			Tag a("td");
			cout<<x;
		}
	}
	for(unsigned y=0;y<Y;y++){
		Tag d("tr");
		if(y==0){
			Tag x("td rowspan="+to_string(Y));
			cout<<"Boxes";
		}
		{
			Tag x("td");
			cout<<y;
		}
		for(unsigned x=0;x<X;x++){
			auto val=f(y,x);
			unsigned char t=(val-min_val)/(float)span*255;
			
			Tag e(
				"td bgcolor=#"+
				to_hex_char((t<128)?255:(255-2*t))+
				"00"+
				to_hex_char((t<128)?(2*t):255)+
				" align=right"
			);
			o<<take(4,to_string(val))<<"\n";
			//o<<t;
			//o<<t;
			//o<<(unsigned char)(255-t);
		}
	}
}

unsigned max_pts(unsigned totes,unsigned cans,unsigned max_stack_height){
	unsigned r=0;
	while(totes && max_stack_height){
		auto stack_height=min(totes,max_stack_height);
		totes-=stack_height;
		r+=2*stack_height;
		if(cans){
			r+=4*stack_height;
			cans--;
		}
	}
	return r;
}

unsigned max_pts_spotted(unsigned boxes,unsigned cans,unsigned max_stack_height){
	//assume that you've been given two stacks of 2 and a stack of 3 to begin with.
	unsigned two_stacks=3;
	unsigned three_stacks=1;

	unsigned total=0;
	auto score_stack=[&](unsigned height){
		if(cans){
			total+=6*height;
			cans--;
		}else{
			total+=2*height;
		}
	};

	while((boxes&&max_stack_height) || two_stacks || three_stacks){
		auto stack_height=min(boxes,max_stack_height);
		if(three_stacks && stack_height<=3){
			three_stacks-=1;
			score_stack(3);
			continue;
		}
		if(two_stacks && stack_height<=2){
			two_stacks--;
			score_stack(2);
			continue;
		}
		score_stack(stack_height);
		boxes-=stack_height;
	}
	return total;
}

int main(int argc,char **argv){
	unsigned max_height=6;
	bool starter=0;
	bool marginal=0;
	bool differential=0;
	bool image=0;

	for(int i=1;i<argc;i++){
		if(argv[i]==string("--max_height")){
			i++;
			max_height=atoi(argv[i]);
		}else if(argv[i]==string("--starter")){
			starter=1;
			//does nothing at the moment.
		}else if(argv[i]==string("--marginal")){
			marginal=1;
		}else if(argv[i]==string("--differential")){
			differential=1;
			marginal=0;
		}else if(argv[i]==string("--demo")){
			image=1;
		}else{
			cout<<"Argument not understood:"<<argv[i]<<"\n";
			return 1;
		}
	}

	auto max_pts1=[=](unsigned boxes,unsigned cans){
		if(starter) return max_pts_spotted(boxes,cans,max_height);
		return max_pts(boxes,cans,max_height);
	};

	auto differential1=[=](unsigned boxes,unsigned cans){
		auto base=max_pts1(boxes,cans);
		auto tote=max_pts1(boxes+1,cans)-base;
		auto can=max_pts1(boxes,cans+1)-base;
		return (int)can-(int)tote;
		//return (float)can/tote;
	};

	if(image){
		if(differential){
			write_image(cout,differential1);
		}else{
			write_image(cout,max_pts1);
		}
		return 0;
	}

	static const unsigned int MAX_CANS=7;
	unsigned max_can_row=marginal?(MAX_CANS-1):MAX_CANS;
	cout<<"\t\tcans\n\t";
	for(unsigned i=0;i<=max_can_row;i++){
		cout<<"\t"<<i;
	}
	cout<<"\n";

	for(unsigned i=0;i<=60;i++){
		if(!i) cout<<"boxes";
		cout<<"\t"<<i<<"\t";
		for(unsigned cans=0;cans<=max_can_row;cans++){
			auto base=max_pts1(i,cans);
			auto tote=max_pts1(i+1,cans)-base;
			auto can=max_pts1(i,cans+1)-base;
			if(marginal){
				cout<<tote<<","<<can<<"\t";
			}else if(differential){
				cout<<(int)can-(int)tote<<"\t";
			}else{
				cout<<base<<"\t";
			}
		}
		cout<<"\n";
	}
	return 0;
}
