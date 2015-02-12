#include <array>
#include <iostream>

std::array<float,3> findHeight(bool is_can, bool on_step,bool placed_on_scoring,float stacted_bins){
	const float HEIGHT_OF_SCORING_PLATFORM = 1.96;
	const float HEIGHT_OF_BIN = 12.1;
	const float HEIGHT_OF_CAN = 29;//18
	const float HEIGHT_OF_STEP = 6.25;
	float max_height =0;
	float min_height =0;
	float TARGET = HEIGHT_OF_BIN/2;	
	if(placed_on_scoring){
		max_height += HEIGHT_OF_SCORING_PLATFORM;
		min_height += max_height;
		TARGET += max_height;
	}else if(on_step){
		max_height += HEIGHT_OF_STEP;
		min_height += max_height;
		TARGET += max_height;
	}
	max_height += (stacted_bins* HEIGHT_OF_BIN)-2;
	min_height += max_height-HEIGHT_OF_BIN+2;
	TARGET += min_height;
	if(is_can){
		max_height += HEIGHT_OF_CAN;
		min_height += HEIGHT_OF_CAN;
		TARGET += HEIGHT_OF_CAN;
	}
	std::array<float,3> x = {max_height,min_height,TARGET};
	return x;
}

int main(){
	std::array<float,3> x = findHeight(true,false,false,1);
	std::cout<<"Max Height: "<<x[0]<<" Min Height: "<<x[1]<<" Target "<<x[2];

}

