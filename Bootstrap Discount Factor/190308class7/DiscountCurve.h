/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////

#pragma once
#include "CubicSpline.h" // Cubic spline based on https://en.wikipedia.org/wiki/Spline_(mathematics)#Algorithm_for_computing_natural_cubic_splines

class DiscountCurve
{
public:
	DiscountCurve() {
		add(0.0, 1.0);
	}
	virtual ~DiscountCurve() {}
	void add(double Year, double DiscountFactor);
	double DiscountFactor(double Year);

private:
	CubicSpline mDiscountCurveData;
};