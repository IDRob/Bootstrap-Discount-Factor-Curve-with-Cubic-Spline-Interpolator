/////////////////////////////////////////////////////
// Discount Factor Curve Bootstrapping
// Based on Coursework 7, MTH773P, Advanced Computing in Finance, Queen Mary University
// Updated to use Cubic Spline interpolation instead of linear interpolation.
// Source notes by Michael J Phillips, M.J. Capinski and T. Zastawniak
// Written by Iain Robertson
/////////////////////////////////////////////////////

#include "BootStrapper.h"


void BootStrapper::BootStrapCompute(DiscountCurve &CurveA, vector <Swap> &swaps) const
{
	for (vector <Swap>::iterator it = swaps.begin(); it != swaps.end(); ++it)
	{
		const double Right = 1; // Highest possible value for discount factor.
		const double Left = 0; //Lowest possible value for discount factor.
		const double Target = 0; // Target price for solver. Set at zero due in being a to par swap.
		const double Accuracy = 0.0001; // Accuarcy of solver.

		//
		//Private class used as interface for solver. Includes Function method used in solver class.
		//

		class SolverInterface : public Solver
		{
		public:
			SolverInterface(const Swap &swap, DiscountCurve &CurveA) : mswap(swap), mCurve(CurveA) {}
			double Function(double DF)
			{
				mCurve.add(mswap.Maturity(), DF);
				return mswap.Price(mCurve);
			}

		private:
			Swap mswap;
			DiscountCurve mCurve;
		}ps(*it, CurveA);

		double DF = SolveByBisect(&ps, Target, Left, Right, Accuracy);
		CurveA.add(it->Maturity(), DF);
	}
}