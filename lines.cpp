//TODO: File breakdown percentages
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	//Only cpp files
	vector<string> files = {"to_crio.cpp","dio_control.cpp","lift_sim.cpp","dio_control.h","jag_control.cpp","jag_control.h","control/height.cpp","control/height.h","control/autonomous.cpp","control/toplevel_mode.cpp","control/toplevel_mode.h","control/pump.cpp","control/pump.h","control/main.cpp","control/main.h","control/monitor.cpp","control/monitor.h","control/can_grabber.cpp","control/can_grabber.h","control/combo_lift.cpp","control/combo_lift.h","control/tote_sensors.cpp","control/tote_sensors.h","control/lift.cpp","control/lift.h",	"control/force_interface.cpp","control/force_interface.h","control/toplevel.cpp","control/toplevel.h","control/force.cpp","control/force.h","control/drivebase.cpp","control/drivebase.h","control/motor_check.cpp","control/motor_check.h","control/kicker.cpp","control/kicker.h","control/formal.h","util/util.cpp","util/util.h","util/perf_tracker.cpp","util/perf_tracker.h","util/bound_tracker.cpp","util/bound_tracker.h","util/posedge_toggle.cpp","util/posedge_toggle.h","util/point.cpp","util/point.h","util/jag_interface.cpp","util/jag_interface.h","util/negedge_trigger.cpp","util/negedge_trigger.h","util/posedge_trigger.cpp","util/posedge_trigger.h","util/countdown_timer.cpp","util/countdown_timer.h","util/input.cpp","util/input.h","util/interface.cpp","util/interface.h","util/logger.cpp","util/countup_timer.cpp","util/countup_timer.h","util/driver_station_interface.cpp","util/driver_station_interface.h","util/output.cpp","util/output.h","util/settable_toggle.cpp","util/settable_toggle.h","util/maybe.h","util/maybe_inline.h","util/quick.h","input/util.cpp","input/util.h","input/panel2015.cpp","input/panel2015.h","input/joystick_linux.cpp","input/joystick_linux.h","input/range_finder.cpp"};
	vector<int> file_lines;
	vector<pair<float,int>> file_percentages;
	vector<int> lines; //0 is overall, 1 is .cpp files, 2 is .h files
	static const unsigned FILE_TYPES = 2;
	int current_lines = 0;
	for (unsigned int i=0;i<(FILE_TYPES+1);i++) {
		lines.push_back(current_lines);
	}
	string type_flag="-t";
	string file_flag="-f";
	bool do_types = false;
	bool do_files = false;
	if (argc>2) {
		do_types = (argv[1]==type_flag||argv[2]==type_flag);	
		do_files = (argv[1]==file_flag||argv[2]==file_flag);
	} else if (argc>1) {
		do_types = (argv[1]==type_flag);
		do_files = (argv[1]==file_flag);	
	}
	int file_type = 0; //0 is cpp, 1 is h
	string placeholder;
	ifstream current_file;
	for (unsigned int i=0;i<files.size();i++) {
		current_file.open("fourteentwentyfive.sting/"+files[i]);
		current_lines = 0;
		if (files[i].find(".cpp")!=string::npos) file_type = 0;
		else if (files[i].find(".h")!=string::npos) file_type = 1;
		else assert(0);
		while (!current_file.eof()) {
			getline(current_file, placeholder);
			current_lines++;
			if (do_types) {
				switch (file_type) {
					case 0:
						lines[1]++;
						break;
					case 1:
						lines[2]++;
						break;
					default:
						assert(0);
				}
			}
		}
		lines[0]+=current_lines;
		if (do_files) {
			file_lines.push_back(current_lines);
		}
		current_file.close();
	}
	cout<<"Total lines of code: "<<lines[0]<<endl;
	if (do_types) {
		cout<<"CPP file lines: "<<lines[1]<<endl;
		cout<<"Header file lines: "<<lines[2]<<endl;
	}
	if (do_files) {
		for(unsigned int i=0;i<files.size();i++) {
			pair<float, int> new_pair;
			new_pair.first=100*(file_lines[i]/i);
			new_pair.second=i;
			file_percentages.push_back(new_pair);
		}
		vector<pair<float,int>> v;
		for(unsigned int i=0;i<files.size();i++) {
			pair<float,int> f;
			f.first=0;
			f.second=0;
			v.push_back(f);
		}
		for(unsigned int i=0;i<files.size();i++) {
			for(unsigned int j=0;j<v.size();j++) {
				if (file_percentages[i].first>v[j].first) {
					v[j]=file_percentages[i];
					break;
				}
			}
		}
		cout<<"Breakdown by file:"<<endl;
		for(unsigned int i=0;i<files.size();i++) {
			cout<<"	"<<files[i]<<": "<<file_lines[i]<<" lines, "<<file_percentages[i].first<<"% of total lines"<<endl;
		}
	}
	return 1;
}
