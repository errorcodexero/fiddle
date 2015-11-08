#include <cv.h>
#include <highgui.h>
#include<iostream>
#include<functional>
//#include "../util.h"

using namespace cv;
using namespace std;

#define nyi { std::cout<<"NYI "<<__FILE__<<":"<<__LINE__<<"\n"; exit(44); }

template<typename T>
std::vector<T>& operator|=(std::vector<T>& v,T t){
	v.emplace_back(std::move(t));
	return v;
}

template<typename Func,typename Collection>
auto mapf(Func f,Collection const& c)->std::vector<decltype(f(*std::begin(c)))>{
	std::vector<decltype(f(*std::begin(c)))> r;
	for(auto a:c) r|=f(a);
	return r;
}

vector<string> split(string s){
	vector<string> r;
	stringstream ss;
	auto push=[&](){
		if(ss.str().size()){
			r|=ss.str();
			ss.str("");
		}
	};
	for(auto c:s){
		if(isblank(c)){
			push();
		}else{
			ss<<c;
		}
	}
	push();
	return r;
}

vector<string> split(char c,string s){
	vector<string> r;
	stringstream ss;
	auto push=[&](){
		r|=ss.str();
		ss.str("");
	};
	for(auto here:s){
		if(here==c){
			push();
		}else{
			ss<<here;
		}
	}
	push();
	return r;
}

//size of the monitor in px
Size display_size(){
	const char *command="xrandr|grep '*'";
	FILE *fpipe=popen(command,"r");
	char line[256];
	vector<string> r;
	while(fgets(line,sizeof(line),fpipe)){
		r|=string(line);
	}
	pclose(fpipe);
	assert(r.size()==1);//not dealing w/ 0 or multi-screen setups at this time
	auto sp=split(r[0]);
	assert(sp.size());
	auto sp2=split('x',sp[0]);
	assert(sp2.size()==2);
	auto x=atoi(sp2[0].c_str());
	auto y=atoi(sp2[1].c_str());
	assert(x);
	assert(y);
	return Size(x,y);
}

Size operator/(Size a,unsigned u){
	assert(u);
	return {(int)(a.width/u),(int)(a.height/u)};
}

#define DIRECTIONS X(N) X(S) X(E) X(W)

#define X(NAME) NAME,
enum class Dir{DIRECTIONS};
#undef X

ostream& operator<<(ostream& o,Dir a){
	#define X(NAME) if(a==Dir::NAME) return o<<""#NAME;
	DIRECTIONS
	#undef X
	assert(0);
}

//the labeled data
static const map<string,Dir> CORRECT{
	{"IMAG0817.jpg",Dir::W},
	{"IMAG0818.jpg",Dir::W},
	{"IMAG0819.jpg",Dir::W},
	{"IMAG0820.jpg",Dir::N},
	{"IMAG0821.jpg",Dir::N},
	{"IMAG0822.jpg",Dir::N},
	{"IMAG0823.jpg",Dir::N},
	{"IMAG0824.jpg",Dir::E},
	{"IMAG0825.jpg",Dir::E},
	{"IMAG0826.jpg",Dir::E},
	{"IMAG0827.jpg",Dir::E},
	{"IMAG0828.jpg",Dir::E},
	{"IMAG0834.jpg",Dir::S},
	{"IMAG0835.jpg",Dir::S},
	{"IMAG0836.jpg",Dir::S},
	{"IMAG0837.jpg",Dir::S},
	{"IMAG0838.jpg",Dir::S},
	{"IMAG0839.jpg",Dir::S},
	{"IMAG0840.jpg",Dir::S},
	{"IMAG0841.jpg",Dir::N},
	{"IMAG0842.jpg",Dir::S},
	{"IMAG0843.jpg",Dir::N}
};

static const vector<string> files=mapf(
	[](pair<string,Dir> p){
		stringstream ss;
		//TODO: Change this.
		ss<<"/home/eric/1425/halberd/doc/Pictures/"<<p.first;
		return ss.str();
	},
	CORRECT
);

unsigned checksum(Mat a){
	CV_Assert(a.depth()==CV_8U);
	auto channels=a.channels();
	switch(channels){
		case 3:{
			//there must be some sort of 'pixel adapter' that does this automatically
			auto at=a.begin<Vec3b>();
			auto end=a.end<Vec3b>();
			unsigned t=0;
			for(;at!=end;++at){
				auto px=*at;
				//cout<<"px:"<<px<<"\n";
				t+=px[0];
				t+=px[1];
				t+=px[2];
			}
			return t;
		}
		default:nyi
	}
	return 0;
}

/*
plan of attack:
1) attempt to classify each of the images correctly
2) show onscreen what the probabilities calculated for each of them are
3) test the classifier w/ slightly chaged tints, slight rotation, etc.
would be nice to see areas that are highlighted by different sorts of filters
-need to figure out how to display text
-need to figure out how to draw stuff (lines, boxes, etc)
-change the image that's being shown

method of classifying images:
1) recognized 'blue' areas that looks like banners & count them

*/

using CB=std::function<void(int,void*)>;
//std::function<void(int,void*)> current_callback;
vector<CB> callbacks;

void* add_callback(CB cb){
	auto r=callbacks.size();
	callbacks|=cb;
	return (void*)r;
}

void callback(int a,void* b){
	size_t index=(size_t)b;
	assert(callbacks.size()>index);
	callbacks[index](a,b);
}

Size fit_into(Size orig,Size box){
	auto a=box.width/(float)orig.width;
	auto b=box.height/(float)orig.height;
	double scale_factor=min(a,b);
	return Size{(int)(orig.width*scale_factor),(int)(orig.height*scale_factor)};
}

int main( int argc, char** argv ){
	/*if(argc!=2){
		std::cerr<<"no filename specified\n";
		exit(1);
	}
	const char* imageName = argv[1];

	Mat image;
	image = imread( imageName, 1 );

	if( argc != 2 || !image.data ){
		printf( " No image data \n " );
		return -1;
	}
	Mat gray_image;
	cvtColor( image, gray_image, CV_BGR2GRAY );*/

	//imwrite( "../../images/Gray_Image.jpg", gray_image );
	//auto out=imwrite( "Gray_Image.jpg", gray_image );
	//std::cout<<"out:"<<out<<"\n";
	//cout<<"chk:"<<checksum(image)<<"\n";

	//namedWindow( imageName, CV_WINDOW_AUTOSIZE );
	//namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

	//namedWindow(imageName,WINDOW_NORMAL);
	//namedWindow("Gray image",WINDOW_NORMAL);
	//imshow( imageName, image );
	//imshow( "Gray image", gray_image );

	//waitKey(0);

	namedWindow("f1",0);
	auto d=display_size();
	//take lower right 1/4 of window
	auto quarter_size=[&](string name){ resizeWindow(name,d.width/2,d.height/2); };
	quarter_size("f1");
	moveWindow("f1",d.width/2,d.height/2);

	namedWindow("f2",0);
	quarter_size("f2");
	moveWindow("f2",d.width/2,0);

	int hue_lower=77,hue_upper=149;
	int sat_min=0,sat_max=255;
	int lum_min=0,lum_max=255;

	for(auto file:files){
		Mat in;
		in=imread(file,1);
		if(!in.data){
			cerr<<"Could not read image:"<<file<<"\n";
			return 1;
		}
		auto d=display_size();
		resize(in,in,fit_into(in.size(),d/2));//approx right
		//Mat after;
		//cvtColor(in,after,CV_BGR2GRAY);

		Mat hsv_im;
		cvtColor(in,hsv_im,COLOR_BGR2HSV);
		Mat lower_red_hue_range,upper_red_hue_range,blue;
		auto run1=[&](){
			//inRange(hsv_im,Scalar(0,100,100),Scalar(10,255,255),lower_red_hue_range);
			//inRange(hsv_im,Scalar(160,100,100),Scalar(179,255,255),upper_red_hue_range);
			//inRange(hsv_im,Scalar(100,0,10),Scalar(179,255,150),blue);
			//inRange(hsv_im,Scalar(hue_lower,0,0),Scalar(hue_upper,255,100),blue);
			inRange(
				hsv_im,
				Scalar(hue_lower,sat_min,lum_min),
				Scalar(hue_upper,sat_max,lum_max),
				blue
			);
			//blur( blue, blue, Size(3,3) );
			//Mat contours,heirarchy;
			//OutputArrayOfArrays contours;
			//int mode=CV_RETR_LIST,method=CV_CHAIN_APPROX_NONE;
			//findContours(blue,contours,mode,method);
			Mat colorized;
			cvtColor(blue,colorized,CV_GRAY2RGB);//seems like this is actually going to bgr.

			SimpleBlobDetector detector;
			vector<KeyPoint> keypoints;
			detector.detect(blue,keypoints);
			Mat im_with_keypoints;
			drawKeypoints(blue,keypoints,im_with_keypoints,Scalar{0,0,255},DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
			colorized=im_with_keypoints;

			static const auto RED=Scalar{0,0,255};
			circle(colorized,{200,200},100,RED);
			line(colorized,{200,200},{400,300},RED,10);
			static const auto BLUE=Scalar{255,50,50};
			putText(colorized,"This is some text",{10,350},FONT_HERSHEY_DUPLEX,1,BLUE);

			imshow("f2",colorized);
		};
		run1();
		//int max_thresh=255;
		/*auto thresh_callback=[&](int,void*){
			run1();
		};*/
		//current_callback=thresh_callback;
		//createTrackbar( "hue min", "f1", &hue_lower, max_thresh,callback,add_callback(thresh_callback));
		auto hue_max=[&](int,void*){
			run1();
		};
		//createTrackbar("hue max","f1",&hue_upper,255,callback,add_callback(hue_max));
		auto a=[&](string name,int* value){
			createTrackbar(name,"f1",value,255,callback,add_callback(hue_max));
		};
		a("hue min",&hue_lower);
		a("hue max",&hue_upper);
		a("sat min",&sat_min);
		a("sat max",&sat_max);
		a("lum min",&lum_min);
		a("lum max",&lum_max);
		imshow("f1",in);
		quarter_size("f1");
		
		//imshow("f2",hsv_im);
		//imshow("f2",lower_red_hue_range);//seems to pick out the flag well.
		//imshow("f2",upper_red_hue_range);//seems to get the rest of the red
		//waitKey(100);
		char c=waitKey(0);
		//cout<<"got:"<<c<<"\n";
		if(c=='q' || c=='Q') return 0;
	}

	return 0;
}
