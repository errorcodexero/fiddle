#include<iostream>

using namespace std;

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

int main(int argc,char **argv){
	if(argc!=2){
		cout<<"Requires max stack height\n";
		return 1;
	}
	int max_height=atoi(argv[1]);
	static const int MAX_CANS=7;
	cout<<"\t\tcans\n\t";
	for(unsigned i=0;i<=MAX_CANS;i++){
		cout<<"\t"<<i;
	}
	cout<<"\n";

	bool marginal=0;
	for(unsigned i=0;i<=60;i++){
		if(!i) cout<<"boxes";
		cout<<"\t"<<i<<"\t";
		for(unsigned cans=0;cans<=MAX_CANS;cans++){
			if(marginal){
				auto base=max_pts(i,cans,max_height);
				auto tote=max_pts(i+1,cans,max_height)-base;
				auto can=max_pts(i,cans+1,max_height)-base;
				cout<<tote<<","<<can<<"\t";
			}else{
				cout<<max_pts(i,cans,max_height)<<"\t";
			}
		}
		cout<<"\n";
	}
	return 0;
}
