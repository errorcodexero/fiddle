#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define GETSTAT 0
#define GETAVG 1
#define GETMAX 2
#define GETMIN 3
#define GETDAT 4
#define ABOUT 5
#define QUIT 7
#define DISPFILE 6

#define VERSION "V0.01"

using namespace std;

enum State { idle, processing, finished};

void clearScreen() {
    
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";   
}

void printTitle () {
        cout <<"  _                          \n | |   ___  __ _             \n | |__/ _ \\/ _` |            \n |____\\___/\\__, | _          \n | _ \\___ _|___/_| |___ _ _  \n |   / -_) _` / _` / -_) '_| \n |_|_\\___\\__,_\\__,_\\___|_|   \n                             \n\n\n";
        
        }

string sReadLine( ifstream& _ifFile, int _iLineNum) {
    
    _ifFile.seekg(0, _ifFile.beg);
    string sLineText_;
    for (int i = 0; i < _iLineNum; i++) {
        getline(_ifFile, sLineText_);
        if(!_ifFile.good()) {
            cerr << "Invalid Line in File\n";
            
        }
    }
    _ifFile.seekg(0, _ifFile.beg);
    return sLineText_;
    
}
/*
int iGetDir(string sDir, vector <string > &sFiles) {
    
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
    
}
*/
bool bContText(string _sStringIn, string _sInText) {
    
    char cTempIn;
    char cTempCurr;
    for (int i = 0; i <= _sStringIn.size(); i++ ) {
            
        
    } 
    
}

vector <string > sGetCSVHeader(ifstream _ifFile) {
    
    _ifFile.seekg(0, _ifFile.beg);
    
    int iIndex = 0;
    int iCharNum = 0;
    
    char tmp;
    
    string _sLine;
    string _sOutLine;
    string _sTempString;
    
    vector <string > sOutput_; 
    
    _sLine = sReadLine(_ifFile, 1);
    do {
        
        tmp = _sLine[iCharNum];
        if (tmp == ',' || tmp == '\n') {
            sOutput_.push_back(_sOutLine);
            iIndex++;
        }
        _sOutLine += tmp; 
        iCharNum++;
    }
    while (iCharNum <= _sLine.size());
    _ifFile.seekg(0, _ifFile.beg);
    return sOutput_;
}

string getColumn(ifstream& _ifFile, int _iLineNum, int _iColNum) {
    
    _ifFile.seekg(0, _ifFile.beg);
    
    int iCurrCharNum = 0;
    int index = 0;
    
    char tmp;
    
    string _sLine = sReadLine( _ifFile, _iLineNum);
    #ifdef DEBUG
    cout << "String Contains " << _sLine << "\n";
    #endif
    string sOutLine_;
    
    for (int i = 0; i <= _sLine.size(); i++) {
        tmp = _sLine[i];
        if (tmp == ',')
            index++;
        else if (tmp == ',' && index == _iColNum) {
            return sOutLine_; 
        }
        
        sOutLine_ += tmp;
    }
    _ifFile.seekg(0, _ifFile.beg);
    return sOutLine_;
    
}


int main (int argc, char *argv[] ) {
    
    int iLines = 0;
    int iElementsInLines = 0;
    int iCurrentColumn = 0;
    int iEventID;
    int iOption;
    int iMaxFileChoice;
    
    bool bIsEvent = false;
    bool bFirstRun = true;
    
    char * szInput[256];
    
    string sLine;
    string sInput;
    string sFileName;
    string sContinue;
    string sFileChoice;
    
    State State = idle;
    
    vector <string > vsColumn;
    vector <string > vsFiles;    
        
    string sData;
    
    ifstream ifFile;
    openFile:
    system("clear");
    printTitle();
    //iGetDir("")
    cout << "Please Enter a File Name, With the Extension\n\n";
    //for (int i = 0)
    cin >> sFileName;
    ifFile.open(sFileName);
            
    if (!ifFile.good()) {
        cout << "Invalid File or Cannot Open File.\n";
        system("clear");
        goto openFile;
    }
            
    //ifFile.open(sFileName);
    while (true ) {
        begin:
        if (State == idle) {
            if (bFirstRun){
                cout << "Welcome to LogReader V0.01."; 
                }
                bFirstRun = false;
            
            
            cout << "\n\n Please enter an option.\n\n1) Get Log Statatistics (WIP)\n2) Get Average (WIP)\n3) Get Maximum (WIP)\n4) Get Minimum (WIP)\n5) Get Data Element\n6) About\n7) Display File (Broken)\n8) Quit\n\n";
            
            /**************************************************************
           
            Welcome to LogReader V0.01. Please enter an option.
            
            1) Get Log Statatistics
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
                goto begin;
            }
            iOption = stoi(sInput, &lastChar, 10);
            
            if (iOption > 8 || iOption < 1)
            {
                cout << "Please pick a valid option\n";
                system("clear");
                goto begin;
            } else if (iOption == 1) {
                State = processing;
                iEventID = GETSTAT;
                cout << "\n\n";
                system("clear");
                goto begin;
            } else if (iOption == 2) {
                State = processing;
                iEventID = GETAVG;
                cout << "\n\n";
                system("clear");
                goto begin;
            } else if (iOption == 3) {
                State = processing;
                iEventID = GETMAX;
                cout << "\n\n";
                system("clear");
                goto begin;
            } else if (iOption == 4) {
                State = processing;
                iEventID = GETMIN;
                cout << "\n\n";
                system("clear");
                goto begin;
            } else if (iOption == 5) {
                State = processing;
                iEventID = GETDAT;
                cout << "\n\n";
                system("clear");
                goto begin;
            }  else if (iOption == 6) {
                State = processing;
                iEventID = ABOUT;
                cout << "\n\n";
                system("clear");
                goto begin;
            } else if (iOption == 7) {
                State = processing;
                iEventID = DISPFILE;
                cout << "\n\n";
                system("clear");
                goto begin;
                } if (iOption == 8) {
                State = finished;
                goto begin;
            }
        } else if (State == processing) {
             if (iEventID == GETSTAT) {
                
                
                
                
                
                State = finished;
                goto begin; 
            } else if (iEventID == GETAVG) {

                State = finished;
                goto begin;
            } else if (iEventID == GETMAX) {

                State = finished;
                goto begin;
            } else if (iEventID == GETMIN) {

                State = finished;
                goto begin;
            } else if (iEventID == GETDAT) {
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
                        sData = getColumn(ifFile, iLineNum, iColNum );
                        cout << "The data on line " << iLineNum <<", Column " << iColNum << " is " << sData << "\n\n"; 
                        //cout << "Press any key to continue\n";
                        //cin;
                        State = finished;
                        goto begin;
                        throw 20;
                    
                    }
                    catch (int e) {
                        cout << "Error: Error encountered whilst getting column data\n";
                        //cout << "Press any key to continue\n";
                        //cin;
                        State = finished;
                        goto begin;
                    
                    }
            
                
                    State = finished;
                    goto begin;
                
                
            } else if (iEventID == DISPFILE) {
                 cout << "\n\n";
                 while (ifFile.eof() && ifFile.good()) {
                     ifFile >> sLine;
                     cout << sLine << "\n";
                     
                 }
                 
            } else if (iEventID == ABOUT) {

                cout << "LogReader Version " << VERSION << ", Written By Nicholas Burrell\nPlease Note: The CSV Header MUST Have the Data Type Contained Inside of it, Seperated By Spaces\n e.g.)\n    int CarYear, string CarModel, string Company\n";
                
                /*****************************************************
    
                LogReader Version V0.1 Written By Nicholas Burrell
    
                Please Note: The CSV Header MUST Have the Data Type Contained Inside of it, Seperated By Spaces
    
                Example)
     
                    int CarYear, string CarModel, string Company
    
    
    
    
                *****************************************************/
                
                State = idle;
                goto begin;
                
        }
    } else if (State == finished) {
            cout << "Would You Like To Quit?\n\n[Y/n] ";
            cin >> sContinue;
            if (sContinue == "y" || sContinue == "Y" || sContinue == "yes" || sContinue == "YES" || sContinue == "Yes" ) {
                
                cout << "Good Bye\n\n";
                system("clear");
                exit (1);
                
            }
            else if (sContinue == "n" || sContinue == "N" || sContinue == "no" || sContinue == "NO" || sContinue == "No" ) {
                
                State = idle;
                goto begin;

            }
            
            
        }
    }
    
    
}
