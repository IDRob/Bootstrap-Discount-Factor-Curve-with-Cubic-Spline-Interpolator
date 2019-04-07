/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////

#pragma once
#include <map>
#include "DiscountCurve.h"


using namespace std;

class Swap
{
public:
	Swap(int Year, int F, double SwapRate) : mYear(Year), mF(F), mSwapRate(SwapRate) {}
	~Swap() {}
	double CalcFixedLeg(DiscountCurve &DiscountObject) const;
	double CalcFloatLeg(DiscountCurve &DiscountObject) const;
	double Price(DiscountCurve &DiscountObject) const;
	double CalcParRate(DiscountCurve &DiscountObject) const;
	double Maturity() const;
private:
	
	unsigned int mYear;
	double mSwapRate;
	unsigned int mF;
};
