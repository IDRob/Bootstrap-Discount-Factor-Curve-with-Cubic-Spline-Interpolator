#include "Swap.h"


double Swap::CalcFixedLeg(DiscountCurve &DiscountObject) const
{
	double P = 0;
	for (unsigned int i = 1; i <= mYear * mF; ++i)
	{
		P = P + DiscountObject.DiscountFactor(static_cast<double>(i) / mF);
	}
	return P;
}

double Swap::CalcFloatLeg(DiscountCurve &DiscountObject) const
{
	return 1 - DiscountObject.DiscountFactor(mYear);
}

double Swap::Price(DiscountCurve &DiscountObject) const
{
	double FixedLeg = CalcFixedLeg(DiscountObject);
	double FloatLeg = CalcFloatLeg(DiscountObject);

	return (mSwapRate / mF)*FixedLeg - FloatLeg;
}

double Swap::CalcParRate(DiscountCurve &DiscountObject) const
{
	double FixedLeg = CalcFixedLeg(DiscountObject);
	double FloatLeg = CalcFloatLeg(DiscountObject);
	return FloatLeg / FixedLeg * mF;
}

double Swap::Maturity() const
{
	return mYear;
}