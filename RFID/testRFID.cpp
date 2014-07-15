/*
 • Project: A draft for an RFID input based attendance program. 
 • Author(s): Adrian Hardt and Logan Traffas.
 • Description: A program that will take an input identification from an RFID tag and set up a sign in time and sign out time for the person.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

string setTheDay(){//Sets the day the people signed in.
	bool outputDay=1;
	string day;
	string dayOfSigningIn;
	time_t beginningDay;
	struct tm* startDay;
	time(&beginningDay);
	startDay=localtime(&beginningDay);
	dayOfSigningIn=asctime(startDay);
	dayOfSigningIn.replace(24,2,"");
	dayOfSigningIn.replace(10,9, "");
	day=dayOfSigningIn;
	string findDay;
	ifstream searchForDay;
	searchForDay.open("peopleList.txt");
	while(!searchForDay.eof()){
		string line;
		getline(searchForDay,line);
		char firstCharOfLine=line[0];
		string findDay=line.substr(11,day.length());
		if(firstCharOfLine=='O'){
			if(day!=findDay){
				ofstream peopleList;
				peopleList.open("peopleList.txt",ios::app);
				peopleList<<"\r\n"<<"Of the day "<<day<<": ";
				peopleList.close();
				outputDay=0;
				break;
			}
			else{
				outputDay=0;
			}
		}
	}
	if(outputDay==1){
		ofstream peopleList;
		peopleList.open("peopleList.txt",ios::app);
		peopleList<<"\r\n"<<"Of the day "<<day<<": ";
		peopleList.close();
	}
	searchForDay.close();
	return day;
}

string inTime(){//Sets the time the people signed in.
	string signInTime;
	time_t beginningTime;
	struct tm* startTime;
	time(&beginningTime);
	startTime=localtime(&beginningTime);
	signInTime=asctime(startTime);
	signInTime.replace(24,2,"");
	signInTime.replace(0,11,"");
	signInTime.replace(8,5,"");
	return signInTime;
}

string outTime(){//Sets the time the people signed out.
	string signOutTime;
	time_t finishTime;//Sets the time for when the person signed out.
	struct tm* endTime;
	time(&finishTime);
	endTime=localtime(&finishTime);
	signOutTime=asctime(endTime);
	signOutTime.replace(24,2,"");
	signOutTime.replace(0,11,"");
	signOutTime.replace(8,5,"");
	return signOutTime;
}

string getName(string RFIDin){//Sets the name of the person signing in.
	string name;
	string tempName;
	string tempId;
	ifstream inputName;
	inputName.open("IdAndNames.txt");
	while(!inputName.eof()){
		string line;
		string addLetter;
		unsigned int findEqualSign=0;
		string equalSign;
		getline(inputName,line);
		tempId=line;
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
			tempName=line;	
			tempName.replace(0,locationOfLetter,"");
			for(locationOfLetter; locationOfLetter<=tempName.length(); locationOfLetter++){
				addLetter=tempName[locationOfLetter];
				name.append(addLetter);
			}
			break;
		}
	}
	if(RFIDin!=tempId){
		cout<<"That id is not associated with a name yet. Please add a name to associate with the id "<<RFIDin<<"?: ";
		string nameToAdd;
		while(nameToAdd==""){
			getline(cin,nameToAdd);
		}
		ofstream addNewName;
		addNewName.open("IdAndNames.txt",ios::app);
		addNewName<<"\r\n"<<RFIDin<<"="<<nameToAdd;
		addNewName.close();
	}
	name=tempName;
	name.replace(name.length()-1,2,"");
	inputName.close();
	return name;
}

void outputAttendance(string name, string signOutTime, string signInTime, string signInOrOut, string day){//Outputs the attendance to the corresponding file.
	if(signInOrOut=="1"){
		ofstream peopleList;
		peopleList.open("peopleList.txt",ios::app);
		peopleList<<"\r\n        • "<<name<<" was here from: "<<signInTime<<" to: ";
		peopleList.close();
	}
	else if(signInOrOut=="2"){
		ofstream peopleList;
		peopleList.open("peopleList.txt",ios::app);
		peopleList<<signOutTime;
		peopleList.close();
	}
}

int main(){
	bool setDay=1;
	
	while(true){//Input the RFID.
		string signInOrOut="0";
		cout<<"Enter \"1\" to sign in, enter \"2\" to sign out, or enter \"3\" to exit: ";
		cin>>signInOrOut;
		if(signInOrOut=="3"){
			break;
		}
		else if(signInOrOut!="1" && signInOrOut!="2"){
			break;
		}
		else{
			string day;
			string name;
			string RFIDin;
			string signInTime;
			string signOutTime;
			if(setDay==1){
				setTheDay();
				setDay=0;
			}
			bool inputId=0;
			while(signInOrOut=="1"){//Signing in RFID input.
				if(inputId==1){
					break;
				}
				else{
					cout<<"You are signing in. What is your id? ";
					cin>>RFIDin;
					getName(RFIDin);
					cout<<endl;
					if(inputId!=1){
						name=getName(RFIDin);
						signInTime=inTime();
						signOutTime="";
						outputAttendance(name, signOutTime, signInTime, signInOrOut, day);
						inputId=1;
					}
				}
			}
			inputId=0;
			while(signInOrOut=="2"){//Signing out RFID input.
				string RFIDin;
				cout<<"You are signing out. What is your id? ";
				cin>>RFIDin;
				cout<<endl;
				if(inputId!=1){
					name=getName(RFIDin);
					signInTime=inTime();
					signOutTime=outTime();
					outputAttendance(name, signOutTime, signInTime, signInOrOut, day);
					inputId=1;
				}
				else if(inputId==1){
					break;
				}
			}
		}
	}
	return 0;
}