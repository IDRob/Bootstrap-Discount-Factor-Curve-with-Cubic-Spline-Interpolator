/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////


#include <iostream>
#include <cmath>
#include <map>
#include <iomanip>
#include "Swap.h"
#include "BootStrapper.h"

using namespace std;

int main()
{
	//
	// Define current market rates for semi annual par interest rate swaps.
	//

	unsigned const int F = 2;
	vector <Swap> swaps;
	swaps.push_back(Swap(1, F, 0.0264));
	swaps.push_back(Swap(2, F, 0.0306));
	swaps.push_back(Swap(3, F, 0.0342));
	swaps.push_back(Swap(5, F, 0.0411));
	swaps.push_back(Swap(7, F, 0.0456));
	swaps.push_back(Swap(10, F, 0.0497));

	//
	// Define discount curve to be bootstrapped
	//
	DiscountCurve CurveA;
	
	//
	// Use market rates to bootstrap discount curve.
	//
	BootStrapper BootStrapA;
	BootStrapA.BootStrapCompute(CurveA, swaps);


	//
	// Discount factor / Price of zero coupon bond for multiple years.
	// 
	cout << fixed << setprecision(6);
	cout << "The discount factor for year 1 is: " << CurveA.DiscountFactor(1) << endl;
	cout << "The discount factor for year 2 is: " << CurveA.DiscountFactor(2) << endl;
	cout << "The discount factor for year 6 is: " << CurveA.DiscountFactor(6) << endl;
	cout << "The discount factor for year 8 is: " << CurveA.DiscountFactor(8) << endl;

	//
	// Two year deposit rate
	//
	cout << "The two year deposit rate is : " << -100 * log(CurveA.DiscountFactor(2)) / 2 << "%" << endl;

	//
	// Price new 7 year swap.
	//
	cout << "The price of a 7 year swap at rate 4.42% is : " << Swap(7, 2, 0.0442).Price(CurveA) << endl;

	//
	// Par interest rate swap with 9 year maturity
	//
	cout << "The par rate with maturity at 9 years is: " << Swap(9, 2, 0.0).CalcParRate(CurveA) << endl;


	system("pause");
}


// Programme output
/*
The discount factor for year 1 is: 0.974060
The discount factor for year 2 is: 0.940979
The discount factor for year 6 is: 0.768271
The discount factor for year 8 is: 0.681124
The two year deposit rate is : 3.041723%
The price of a 7 year swap at rate 4.42% is : -0.008397
The par rate with maturity at 9 years is: 0.048900
*/