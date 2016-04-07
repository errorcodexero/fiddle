#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <cmath>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
template <class T >
T getMin (vector < T> input) {
	size_t i;
	T minimum = 0;
	T minimum_out = 0;
	if (input.size() == 0)
		return 360;
	if (input.size() == 1)
		return input[0];
	else{
		minimum = numeric_limits< T>::max();
		for (i = 0; i < input.size(); i++) {
			if (minimum > fabs(input[i])) {
				minimum = fabs(input[i]);
				minimum_out = input[i];
			}
		}
	}
	return minimum_out;
}
template <class T >
T getMax (vector <T> input) {
	size_t i;
	T maximum = 0;
	T maximum_out = 0;
	if (input.size() == 0)
		return 0;
	if (input.size() == 1)
		return input[0];
	else{
		maximum = 0;
		for (i = 0; i < input.size(); i++) {
			if (maximum < fabs(input[i])) {
				maximum = fabs(input[i]);
				maximum_out = input[i];
			}
		}
	}
	return maximum_out;
}
template <class T>
int approx(T input, T target, T range);

template <class T>
T getAvg(vector<T> vInputData) {
	T sum = 0;
	T average = 0;
	for (unsigned int i = 0; i < vInputData.size(); i++) {
		sum += vInputData[i];
	}
	average = sum / (float) vInputData.size();

	return average;
}
template <class T>
T standardDeviation(vector<T> _vData) {
	T average = getAvg(_vData);
	T standardDeviation = 0;

	T difference = 0;

	for (unsigned int i = 0; i < _vData.size(); i++) {
		difference += pow((average - _vData[i]), 2.0);
	}

	standardDeviation = sqrt(abs(difference));
	return standardDeviation;
}

template <class T>
T correlationCoefficient(vector<T> _vDataX, vector<T> _vDataY) {

	T coefficient = 0;

	T sumX = 0;
	T sumY = 0;

	T sumX2 = 0;
	T sumY2 = 0;

	float averageSize = (_vDataX.size() + _vDataY.size()) / 2;

	for (unsigned int i = 0; i < _vDataX.size(); i++)
		sumX += _vDataX[i];
	for (unsigned int i = 0; i < _vDataY.size(); i++)
		sumY += _vDataY[i];
	for (unsigned int i = 0; i < _vDataX.size(); i++)
		sumX2 += pow(_vDataX[i], 2.0);
	for (unsigned int i = 0; i < _vDataY.size(); i++)
		sumY2 += pow(_vDataY[i], 2.0);

	//Pardon the large equation. It does, however work

	coefficient = (averageSize * (sumX * sumY) - (sumX * sumY)) / (sqrt(averageSize * sumX2 - pow(sumX, 2.0)) * sqrt(averageSize * sumY2 - pow(sumY, 2.0)));

	return coefficient;
}


#endif /*_MATH_HPP_*/
