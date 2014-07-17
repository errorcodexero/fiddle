// • Project: A draft for an RFID input based attendance program. 
// • Author(s): Adrian Hardt and Logan Traffas. FIRST Team #1425 "ERROR CODE XERO".
// • Description: A program that will take an input identification from an RFID tag and input it into a log.

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void memberRead(string name){//Reads out (from the log) the time the person was present.
}

string inTime(){//Sets the time the people signed in.
	string signInTime;
	time_t beginningTime;
	struct tm* startTime;
	time(&beginningTime);
	startTime=localtime(&beginningTime);
	signInTime=asctime(startTime);
	signInTime.erase(24,2);
	string moveYear=signInTime.substr(19,5);
	signInTime.erase(19,5);
	signInTime.insert(10,moveYear);
	return signInTime;
}

string getName(string RFIDin){//Sets the name of the person signing in.
	string name;
	string tempId;
	ifstream inputName;
	inputName.open("IdAndNames.txt");
	while(!(inputName.eof())){
		string line;
		getline(inputName,line);
		tempId=line;
		string equalSign;
		unsigned int findEqualSign=0;
		for(findEqualSign; findEqualSign<=tempId.length(); findEqualSign++){
			equalSign=tempId[findEqualSign];
			if(equalSign=="="){
				tempId.replace(findEqualSign,1,"");
				break;
			}
		}
		unsigned int tempIdLength=tempId.length();
		tempId.replace(findEqualSign,tempIdLength,"");
		unsigned int locationOfLetter=findEqualSign+1;
		if(RFIDin==tempId){
			string tempName;
			tempName=line;	
			tempName.replace(0,locationOfLetter,"");
			string addLetter;
			for(locationOfLetter; locationOfLetter<=tempName.length(); locationOfLetter++){
				addLetter=tempName[locationOfLetter];
				name.append(addLetter);
			}
			name=tempName;
			name.replace(name.length()-1,2,"");
			break;
		}
	}
	inputName.close();
	if(RFIDin!=tempId){
		cout<<endl<<"That id is not associated with a name yet. Please add a name to associate with the id \""<<RFIDin<<"\": ";
		string nameToAdd;
		while(nameToAdd==""){
			getline(cin,nameToAdd);
		}
		ofstream addNewName;
		addNewName.open("IdAndNames.txt",ios::app);
		addNewName<<"\r\n"<<RFIDin<<"="<<nameToAdd;
		addNewName.close();
		name=nameToAdd;
	}
	return name;
}

void outputAttendance(string RFIDin, string name, string signInTime){//Outputs the attendance to the corresponding file.
	ofstream logOfTimes;
	logOfTimes.open("logOfTimes.txt",ios::app);
	logOfTimes<<name<<"="<<RFIDin<<"="<<signInTime<<"\r\n";
	logOfTimes.close();
}

int main(){//Input the RFID.
	while(1){
		string name;
		string RFIDin;
		string signInTime;
		cout<<"Please input your id.(Input 0 to exit): ";
		cin>>RFIDin;
		if(RFIDin=="0")break;
		cout<<endl;
		name=getName(RFIDin);
		signInTime=inTime();
		outputAttendance(RFIDin, name, signInTime);
	}
	return 0;
}