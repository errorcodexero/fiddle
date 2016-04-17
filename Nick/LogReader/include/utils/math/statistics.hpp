#ifndef _MATH_STATISTICS_H_
#define _MATH_STATISTICS_H_

#include "utils/math/math.hpp"

static const double e = 2.71828182845904523536028747135266249775724709369995;
static const double pi = 3.14159265358979323846264338327950288419716939937510;

template <class T >
T getMin (std::vector < T> input) {
	size_t i;
	T minimum = 0;
	T minimum_out = 0;
	if (input.size() == 0)
		return 360;
	if (input.size() == 1)
		return input[0];
	else{
		minimum = std::numeric_limits< T>::max();
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
T getMax (std::vector <T> input) {
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
			if (maximum < std::fabs(input[i])) {
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
T getAvg(std::vector<T> vInputData) {
	double sum = 0;
	double average = 0;
	for (unsigned int i = 0; i < vInputData.size(); i++) {
		sum += vInputData[i];
	}
	average = sum / (double) vInputData.size();

	return average;
}

template<class T>
double variance(std::vector<T> _vData) {

	double average = getAvg(_vData);

	double difference = 0;

	for (unsigned int i = 0; i < _vData.size(); i++) {
		difference += pow((average - _vData[i]), 2.0);
	}

	return difference;
}

template <class T>
double standardDeviation(std::vector<T> _vData) {
	double average = getAvg(_vData);
	double standardDeviation = 0;

	double difference = 0;

	for (unsigned int i = 0; i < _vData.size(); i++) {
		difference += pow((average - _vData[i]), 2.0);
	}

	standardDeviation = sqrt(fabs(difference));
	return standardDeviation;
}

template <class T>
double correlationCoefficient(std::vector<T> _vDataX, std::vector<T> _vDataY) {

	double coefficient = 0;

	double sumX = 0;
	double sumY = 0;

	double sumX2 = 0;
	double sumY2 = 0;

	double averageSize = (_vDataX.size() + _vDataY.size()) / 2;

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

double normalDistribution(int x,double standardDeviation, double variance, double average) {
	double p = (pow(e, (-1) * pow((x - average), 2.0) / (2 * variance))) / (standardDeviation * sqrt(2 * pi));
	return p;
}

#endif /* _MATH_STATISTIC_H_ */
