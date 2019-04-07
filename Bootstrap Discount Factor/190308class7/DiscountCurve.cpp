/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////

#include "DiscountCurve.h"

void DiscountCurve::add(double Year, double DiscountFactor)
{
	mDiscountCurveData.add(Year, DiscountFactor);
	return;
}

double DiscountCurve::DiscountFactor(double Year)
{
	// Uses cubic spline interpolation.

	return mDiscountCurveData.FindValue(Year);
}