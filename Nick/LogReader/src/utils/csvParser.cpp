#include <utils/csvParser.hpp>

using namespace std;

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
    _ifFile.clear();
    _ifFile.seekg(0, _ifFile.beg);
    return sLineText_;

}

vector<string> vsReadFile(ifstream& _ifFile) {
	vector<string> vsOutput;
	string sTempString;
	while ( _ifFile.good() && !_ifFile.eof()) {
		getline(_ifFile, sTempString);
		vsOutput.push_back(sTempString);
	}
	return vsOutput;
}

vector<string> vsBreakLine(string _sLine) {
	char c;
	string sTruncatedLine;
	vector<string > vsOutput_;
	int iCurrentVec = 0;
	unsigned int i = 0;
	do {
			c = _sLine[i];
			if (c == ',' || c == '\n') {
				vsOutput_.push_back(sTruncatedLine);
				sTruncatedLine = "";
				iCurrentVec++;
			} else {
				sTruncatedLine.push_back(c);
				iCurrentVec++;
			}
			i++;
		} while (i < _sLine.length());
		return vsOutput_;
}

vector <string > sGetCSVHeader(ifstream& _ifFile) {

    _ifFile.clear();
    _ifFile.seekg(0, _ifFile. beg);

    int iIndex = 0;
    unsigned int iCharNum = 0;

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
            sOutLine = "";
        }
        else
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

    int iIndex = 1;

    char tmp;

    string sLine = sReadLine( _ifFile, _iLineNum);
    if (sLine == "ERROR")
    	return "ERROR";
    #ifdef DEBUG
    //cout << "String Contains " << sLine << "\n";
    #endif
    string sOutLine_;

    for (unsigned int i = 0; i <= sLine.size(); i++) {
        tmp = sLine[i];
        if ((tmp == ',' || tmp == '\n') && iIndex == _iColNum) {
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

string sGetElement(vector<vector<string>> _vsInput, int _iLineNumber, int _iElementNumber) {
	cout << _vsInput[_iLineNumber][_iElementNumber] << "\n";
	return _vsInput.at(_iLineNumber).at(_iElementNumber);
}

map <string, unsigned int> vecToMap(vector <string> vsVec) {
	map <string, unsigned int> m;
	for (unsigned int i = 0; i < vsVec.size(); i++) {
		m[vsVec[i]] = i+1;
		//cout << i << " = " << vsVec[i] << "\n";
	}
	return m;

}

vector<string> vsGetColumn(ifstream& _ifFile, int _iColNum) {
	string sTempLine;
	vector<string> vsColData;
	int i = 0;

	while (_ifFile.good() && !_ifFile.eof()) {
		sTempLine = sGetElement(_ifFile, i, _iColNum);

		vsColData.push_back(sTempLine);
		i++;
	}
	return vsColData;
}

vector<string> vsGetColumn (vector<vector<string> > _vsFile, int _iColNum) {

	vector<string> vsColData;

	string sTempLine;
	unsigned int i = 0;

	while (i < _vsFile.size()) {
		//cout << i << "\n";
		sTempLine = _vsFile[i][_iColNum];
		//cout << sTempLine << "\n";
		vsColData.push_back(sTempLine);
		i++;
		//cout << i << " : " << sTempLine << "\n";
	}
	return vsColData;
}

vector<float> vfConvertVector(vector<string> vsData) {
	vector<float> vfData;
	unsigned int i = 0;
	float fTempFloat = 0;
	string sTempLine;
	while (i < vsData.size()) {
		sTempLine = vsData[i];
		if (sTempLine != "ERROR") {
			//cout << fLastFloat;
			if(sscanf(sTempLine.c_str(), "%f", &fTempFloat) < 1) {
				fTempFloat = 0.00000;
				vfData.push_back(fTempFloat);
			}
			else {
				//cout << fTempFloat << " : ";
				vfData.push_back(fTempFloat);
				//fLastFloat = fTempFloat;
			}
			i++;
			//cout << " : " << fTempFloat << "\n";
		}
	}
	return vfData;
}
