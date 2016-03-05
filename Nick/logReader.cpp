#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

#define VERSION "V0.01"

#include "utils/math.hpp"

using namespace std;

enum State { IDLE, PROCESSING, FINISHED};

enum Command {GETSTAT, GETAVG, GETMAX, GETMIN, GETDAT, ABOUT, DISPFILE, QUIT};

void printTitle () {
        cout <<"  _                          \n | |   ___  __ _             \n | |__/ _ \\/ _` |            \n |____\\___/\\__, | _          \n | _ \\___ _|___/_| |___ _ _  \n |   / -_) _` / _` / -_) '_| \n |_|_\\___\\__,_\\__,_\\___|_|   \n                             \n\n\n";
        
        }

struct logStats {
	int iNumOfLines;
	int iNumOfElements;
};

string sReadLine( ifstream& _ifFile, int _iLineNum) {
    
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    string sLineText_;
    for (int i = 0; i < _iLineNum; i++) {
        getline(_ifFile, sLineText_);
        if(!_ifFile.good()) {
        	return "ERROR";
#ifdef DEBUG
            cerr << "Invalid Line in File\n";
#endif
        }
    }
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    return sLineText_;
    
}

vector <string > sGetCSVHeader(ifstream _ifFile) {
    
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile. beg);
    
    int iIndex = 0;
    int iCharNum = 0;
    
    char tmp;
    
    string sLine;
    string sOutLine;
    string sTempString;
    
    vector <string > sOutput_; 
    
    sLine = sReadLine(_ifFile, 1);
    do {
        
        tmp = sLine[iCharNum];
        if (tmp == ',' || tmp == '\n') {
            sOutput_.push_back(sOutLine);
            iIndex++;
        }
        sOutLine += tmp;
        iCharNum++;
    }
    while (iCharNum <= sLine.size());
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    return sOutput_;
}

string sGetElement(ifstream& _ifFile, int _iLineNum, int _iColNum) {
    
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    
    int iCurrCharNum = 0;
    int iIndex = 1;
    
    char tmp;
    
    string sLine = sReadLine( _ifFile, _iLineNum);
    if (sLine == "ERROR")
    	return "ERROR";
    #ifdef DEBUG
    cout << "String Contains " << sLine << "\n";
    #endif
    string sOutLine_;
    
    for (int i = 0; i <= sLine.size(); i++) {
        tmp = sLine[i];
        if (tmp == ',' && iIndex == _iColNum) {
        	return sOutLine_;
                } else if (tmp == ',') {
                	iIndex++;
                	sOutLine_ = "";
        } else {
        		sOutLine_ += tmp;
        	}

        }
    //_ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    return sOutLine_;
    
}

int main (int argc, char *argv[] ) {
    string sTestString = "--TEST";
	if ( argc > 1 && argv[1] == sTestString) {
			cout << "Yay Test\n";
			exit(1);
		}

    int iLines = 0;
    int iElementsInLines = 0;
    int iCurrentColumn = 0;
    int iOption;
    int iMaxFileChoice;
    
    bool bIsEvent = false;
    bool bFirstRun = true;
    bool bFileOpen = false;
    
    char * szInput[256];
    char c;
    string sLine;
    string sInput;
    string sFileName;
    string sContinue;
    string sFileChoice;
    string sTemp;
    
    Command Command = GETSTAT;

    State State = IDLE;
    
    vector <string > vsColumn;
    vector <string > vsFiles;    
        
    string sData;
    
    ifstream ifFile;

    do {
    	system("clear");
    	printTitle();
    	cout << "Please Enter a File Name, With the Extension\n\n";
    	cin >> sFileName;
    	ifFile.open(sFileName);
            
    	if (!ifFile.good()) {
    		cout << "Invalid File or Cannot Open File.\n";
    		system("clear");
    	}
    	else {
    		bFileOpen = true;
    	}
	}

    while (!bFileOpen);
    ifFile.clear();
    ifFile.seekg(0, ifFile.beg);

#ifdef DEBUG
    cout <<iLines << " Line\n";
#endif
    while (true ) {
    	switch (State) {
        case IDLE:
        {
        	ifFile.clear();
        	ifFile.seekg(0, ifFile. beg);
            if (bFirstRun){
                cout << "Welcome to LogReader V0.01."; 
                }
                bFirstRun = false;
            
            
            cout << "\n\n Please enter an option.\n\n1) Get Log Statistics (WIP) \n2) Get Average\n3) Get Maximum\n4) Get Minimum\n5) Get Data Element\n6) About\n7) Display File\n8) Quit\n\n";
            
            /**************************************************************
           
            Welcome to LogReader V0.01. Please enter an option.
            
            1) Get Log Statistics
            2) Get Average
            3) Get Maximum
            4) Get Minimum
            5) Get Data Element
            6) About
            
            
            
            **************************************************************/
            
            cin >> sInput;
            size_t lastChar;
            int i;
            if (sscanf(sInput.c_str(), "%d", &i) <1) {
                cout << "Error: Invalid input. Please input a number within the range below\n\n";
                break;
            }
            iOption = stoi(sInput, &lastChar, 10);
            
            if (iOption > 8 || iOption < 1)
            {
                cout << "Please pick a valid option\n";
                system("clear");
                break;
            } else if (iOption == 1) {
                State = PROCESSING;
                Command = GETSTAT;
                cout << "\n\n";
                system("clear");
                break;
            } else if (iOption == 2) {
                State = PROCESSING;
                Command = GETAVG;
                cout << "\n\n";
                system("clear");
                break;
            } else if (iOption == 3) {
                State = PROCESSING;
                Command = GETMAX;
                cout << "\n\n";
                system("clear");
                break;
            } else if (iOption == 4) {
                State = PROCESSING;
                Command = GETMIN;
                cout << "\n\n";
                system("clear");
                break;
            } else if (iOption == 5) {
                State = PROCESSING;
                Command = GETDAT;
                cout << "\n\n";
                system("clear");
                break;
            }  else if (iOption == 6) {
                State = PROCESSING;
                Command = ABOUT;
                cout << "\n\n";
                system("clear");
                break;
            } else if (iOption == 7) {
                State = PROCESSING;
                Command = DISPFILE;
                cout << "\n\n";
                system("clear");
                break;
                } if (iOption == 8) {
                State = FINISHED;
                }
                break;
        }
        case PROCESSING:
        {
        	switch (Command) {
        	case GETSTAT:
 			{
 				cout << "WIP\n";
 				State = FINISHED;
 				break;
 			}
        	case GETAVG:
        	{
        		int iIsFloat;
        		int iColNum;
        		int i = 1;

        		float fTempFloat = 0;
        		float fAvgFloat = 0;
        		float fSum = 0;

        		string sTempLine;
        		string sColNum;

        		size_t lastChar;

        		vector <float > vfColData;

        		cout << "What Column Number?\n\n";
        		cin >> sColNum;

        		iColNum = stoi(sColNum, &lastChar, 10);

        		ifFile.clear();
        		ifFile.seekg(0, ifFile.beg);
        		while (ifFile.good() && !ifFile.eof()) {
        			sTempLine = sGetElement(ifFile, i, iColNum);
        			if (sTempLine != "ERROR") {
        				if(sscanf(sTempLine.c_str(), "%f", &fTempFloat) < 1) {
        					fTempFloat = 0.00000;
        					vfColData.push_back(fTempFloat);
        				}
        				else
        					vfColData.push_back(fTempFloat);
        				i++;
        			}
        		}

        		for (int i = 0; i < vfColData.size(); i++) {
        			fSum += vfColData[i];
        		}
        		fAvgFloat = fSum / (float) vfColData.size();
        		if (fSum == 0 || fAvgFloat == 0)
        			cout << "Either your lines are full of strings, or you have all 0s in your column\n\n";
        		else
        			cout << "Average Data in Column is " << fAvgFloat << ".\n\n";


        		State = FINISHED;
        		break;
        	}
        	case GETMAX:
        	{

        		int iIsFloat;
        		int iColNum;
    			int i = 1;

        		float fTempFloat;
        		float fMaxFloat;

        		string sTempLine;
        		string sColNum;

        		size_t lastChar;

        		vector <float > vfColData;

        		cout << "What Column Number?\n\n";
        		cin >> sColNum;

        		iColNum = stoi(sColNum, &lastChar, 10);

        		ifFile.clear();
        		ifFile.seekg(0, ifFile.beg);
        		while (ifFile.good() && !ifFile.eof()) {
        			sTempLine = sGetElement(ifFile, i, iColNum);
        			if (sTempLine != "ERROR") {
        				if(ifFile.eof() || ifFile.bad())
        					break;
        				if(sscanf(sTempLine.c_str(), "%f", &fTempFloat) < 1) {
        					fTempFloat = 0.00000;
        					vfColData.push_back(fTempFloat);
        				}
        				else
        					vfColData.push_back(fTempFloat);
        				i++;
        			}
        		}

        		fMaxFloat = getMax(vfColData);
        		cout << "Maximum Data in Column is " << fMaxFloat << ".\n\n";
        		State = FINISHED;
        		break;
        	}
        	case GETMIN:
        	{

        		int iIsFloat;
        		int iColNum;
    			int i = 1;

        		float fTempFloat;
        		float fMinFloat;

        		string sTempLine;
        		string sColNum;

        		size_t lastChar;

        		vector <float > vfColData;

        		cout << "What Column Number?\n\n";
        		cin >> sColNum;

        		iColNum = stoi(sColNum, &lastChar, 10);

        		//ifFile.clear();
        		ifFile.seekg(0, ifFile.beg);
        		while (ifFile.good() && !ifFile.eof()) {
        			sTempLine = sGetElement(ifFile, i, iColNum);
        			if (sTempLine != "ERROR") {
        				if(sscanf(sTempLine.c_str(), "%f", &fTempFloat) >= 1)
        					vfColData.push_back(fTempFloat);
        				i++;
        			}
        		}

        		fMinFloat = getMin(vfColData);
        		cout << "Minimum Data in Column is " << fMinFloat << ".\n\n";

        		//cout << "WIP\n";
        		State = FINISHED;
        		break;
        	}
        	case GETDAT:
        	{
        		int iLineNum = 0;
        		int iColNum = 0;

        		string sLineNum;
        		string sColNum;
        		string sLineOut;

        		size_t lastChar;

        		cout << "What Line?\n\nLine: ";
        		cin >> sLineNum;

        		if (sscanf(sLineNum.c_str(), "%d", &iLineNum) <1) {
        			cout << "Error: Invalid input.\n\n";
        		}


        		cout << "What Column?\n\nColumn: ";
        		cin >> sColNum;

        		if (sscanf(sColNum.c_str(), "%d", &iColNum) <1) {
        			cout << "Error: Invalid input.\n\n";
        		}
        		iLineNum = stoi(sLineNum, &lastChar, 10);
        		iColNum = stoi(sColNum, &lastChar, 10);
        		try {
        			sData = sGetElement(ifFile, iLineNum, iColNum );
        			cout << "The data on line " << iLineNum <<", Column " << iColNum << " is " << sData << "\n\n";

        			State = FINISHED;
        			break;
        			throw 20;

        		}
        		catch (int e) {
        			cout << "Error: Error encountered whilst getting column data\n";
        			State = FINISHED;
        			break;

        		}


        		State = FINISHED;
        		break;
        	}
        	case DISPFILE:
        	{
        		cout << "\n\n";
        		ifFile.clear();
        		ifFile.seekg(0, ifFile.beg);
        		while (!ifFile.eof() && ifFile.good()) {
        			getline(ifFile, sLine);
        			cout << sLine << "\n";

        		}
        		break;
        	}
        	case ABOUT:
        	{

        		cout << "LogReader Version " << VERSION << ", Written By Nicholas Burrell\nPlease Note: The CSV Header MUST Have the Data Type Contained Inside of it, Seperated By Spaces\n e.g.)\n    int CarYear, string CarModel, string Company\n";

 			/*****************************************************

                LogReader Version V0.1 Written By Nicholas Burrell

                Please Note: The CSV Header MUST Have the Data Type Contained Inside of it, Seperated By Spaces

                Example)

                    int CarYear, string CarModel, string Company


    
    
                *****************************************************/
                
        		State = IDLE;
        		break;
        	}
        	case QUIT:
        	{
        		State = FINISHED;
        		break;
        	}
        }

        case FINISHED:
        	{
 			cout << "Would You Like To Quit?\n\n[Y/n] ";
 			cin >> sContinue;
 			if (sContinue == "y" || sContinue == "Y" || sContinue == "yes" || sContinue == "YES" || sContinue == "Yes" ) {

 				cout << "Good Bye\n\n";
 				system("clear");
 				exit (1);

                		}
                	else if (sContinue == "n" || sContinue == "N" || sContinue == "no" || sContinue == "NO" || sContinue == "No" ) {

                		State = IDLE;
                		system("clear");
                		break;

                	}
            
            
    			}
        	}
    	}
    }
}
