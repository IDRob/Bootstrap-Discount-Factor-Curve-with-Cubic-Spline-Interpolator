/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////

#pragma once
#include "DiscountCurve.h"
#include "Swap.h" 
#include "Solver.h" //Solver developed from Numberical Methods in Finance by M.J. Capinski and T. Zastawniak

class BootStrapper
{
public:
	void BootStrapCompute(DiscountCurve &CurveA, vector <Swap> &swaps) const;
private:

};