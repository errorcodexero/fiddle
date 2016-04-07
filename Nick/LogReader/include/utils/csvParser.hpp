#ifndef _CSVPARSER_H_
#define _CSVPARSE_H_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <map>

#include "utils/math.hpp"

std::vector<std::string> sGetCSVHeader(std::ifstream& _ifFile);

std::string sGetElement(std::ifstream& _ifFile);

std::string sGetElement(std::vector<std::vector<std::string>> _vsInput, int _iLineNumber, int _iElementNumber);

std::string sGetElement(std::ifstream& _ifFile, int _iLineNum, int _iColNum);

std::map<std::string, unsigned int> vecToMap(std::vector<std::string>);

std::vector<std::string> vsBreakLine(std::string);

std::vector<std::string> vsReadFile(std::ifstream& _ifFile);

std::vector<std::string> vsGetColumn(std::vector<std::vector<std::string>> _vsFile, int _iColNum);

std::vector<std::string> vsGetColumn(std::ifstream& _ifFile, int _iColNum);

std::vector<float> vfConvertVector(std::vector<std::string>);

#endif /* _CSVPARSER_H_ */
