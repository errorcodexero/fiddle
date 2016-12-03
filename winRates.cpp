#include <iostream>
#include <vector>
using namespace std;

struct team {
        float winRate;

        team (float rate) {
                winRate = rate;
        }
};

struct event {
	vector<float> winRates = {};
	float avg;
	
	void addTeam(team newTeam) {
		winRates.push_back(newTeam.winRate);
		float sum = 0;
		for(int i = 0; i < winRates.size(); i++) {
			sum += winRates[i];
		}
		avg = sum / winRates.size();
	}
	void addTeam(vector<team> newTeams) {
		for(int i = 0; i < newTeams.size(); i++) {
			winRates.push_back(newTeams[i].winRate);
		}
		float sum = 0;
                for(int i = 0; i < winRates.size(); i++) {
                        sum += winRates[i];
                }
                avg = sum / winRates.size();
	}
};

int main() {
	event wilsonville;
	vector<team> wilTeams = {team(33.3)/*nerds of the north*/, team(52.8)/*high desert droids*/, team(45.8)/*phred*/, team(50)/*cv robotics*/, team(33.3)/*swarm*/, team()/*spartan robotics*/};
	wilsonville.addTeam(wilTeams);
	cout<<"The average win rate of the teams at the 2017 Wilsonville event is "<<wilsonville.avg<<"%\n";
}
