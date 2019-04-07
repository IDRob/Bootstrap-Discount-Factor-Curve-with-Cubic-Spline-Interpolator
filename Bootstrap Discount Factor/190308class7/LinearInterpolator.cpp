#include <iostream>
#include <math.h>
#include "LinearInterpolator.h"
#include <map>

using namespace std;

void LinearInterpolator::add(double x, double y)
{
	if (DataPoints.count(x) != 0)
	{
		map<double, double>::iterator it = DataPoints.find(x);
		it->second = y;
	}
	DataPoints.insert(pair<double, double>(x, y));
}

double LinearInterpolator::value(double x)
{
	if (DataPoints.empty())
	{
		cout << "No prior data entered." << endl;
		system("pause");
		exit(EXIT_FAILURE);
		//return 0; // I'm not sure of a good way for me to exit the program from a double function.
	}
	if (DataPoints.begin()->first > x)
	{
		cout << "Inputted x is outside current data points. Clostest data point: ";
		return DataPoints.begin()->second;
	}
	map<double, double>::iterator it;

	it = DataPoints.find(x);
	if (it != DataPoints.end())
	{
		return it->second;
	}
	//typedef map<double, double> Datapoints;
	else
	{
		for (it = DataPoints.begin(); it != DataPoints.end(); ++it)
		{
			if (it->first >= x)
			{
				double XUpper = it->first;
				double YUpper = it->second;
				--it;
				double XLower = it->first;
				double YLower = it->second;
				return ((YUpper - YLower) / (XUpper - XLower))*(x - XLower) + YLower;
			}
		}
		map<double, double>::iterator it = DataPoints.end();
		--it;
		cout << "Inputted data in outside current data points. Closest data point: ";
		return it->second;
	}
}