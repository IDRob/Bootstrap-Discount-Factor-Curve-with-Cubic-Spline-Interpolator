/////////////////////////////////////////////
// Based on Non Linear Solver from Numberical Methods in Finance by M.J. Capinski and T. Zastawniak
// Uses Bisection method.
// Written by Iain Robertson
/////////////////////////////////////////////

#pragma once
#include <math.h>


//Base class which acts as interface for solver. Derive class with function "Function" to use solver.
class Solver
{
public:
	Solver() {}
	~Solver() {}
	virtual double Function(double V) = 0;
private:
};

double inline SolveByBisect(Solver *Fct, double Target, double Left, double Right, double Accuracy)
{
	double L = Left, R = Right;
	double Mid = (Left + Right) / 2;
	double Difference = 1;
	while (fabs(Difference) > Accuracy)
	{
		double FunctionMid = Fct->Function(Mid);
		if (FunctionMid - Target < 0)
		{
			L = Mid;
		}
		else
		{
			R = Mid;
		}
		Mid = (R + L) / 2;
		Difference = Mid - L;
	}
	return Mid;
}

