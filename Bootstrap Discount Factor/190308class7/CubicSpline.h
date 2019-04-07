/////////////////////////////////////////////////
// Cubic Spline based on https://en.wikipedia.org/wiki/Spline_(mathematics)#Algorithm_for_computing_natural_cubic_splines implementation
//
// The 'add' function orders coordinates in size of x value - making a well defined function.
// Written by Iain Robertson
/////////////////////////////////////////////////

#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <iostream>

using namespace std;

class CubicSpline
{
public:
	CubicSpline() {}
	~CubicSpline() {}
	void add(double x, double y);
	void UpdateSpline();
	double FindValue(double x);
private:
	map <double, double> mCoordinates;
	vector <double> ma;
	vector<double> mb;
	vector<double> md;
	vector<double> mc;
	vector<vector <double> > mOutputMatrix;
};
