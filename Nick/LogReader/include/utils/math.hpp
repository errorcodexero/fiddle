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
#endif /*_MATH_HPP_*/
