#include "CubicSpline.h"


// Add function uses map vector and orders inputted coordinates.
void CubicSpline::add(double x, double y)
{
	map<double, double>::iterator it = mCoordinates.find(x);
	if (it != mCoordinates.end())
	{
		it->second = y;
	}
	else
	{
		mCoordinates.insert(pair<double, double>(x, y));
	}
}

// Update spline calculates coefficients a, b, c, d for each polynomial piece. Y_i(t)=a_i+b_i*t+c_i*t^2+d_i*t^3.
void CubicSpline::UpdateSpline()
{
	int n = static_cast<int> (mCoordinates.size());
	int Counter = 0;
	ma.resize(n + 1);
	mb.resize(n);
	md.resize(n);
	vector<double> mu;
	mu.resize(n);
	vector<double> h;
	h.resize(n);
	for (map<double, double>::iterator it = mCoordinates.begin(); it != mCoordinates.end();)
	{
		ma[Counter] = it->second;
		double xlow = it->first;
		++it;
		if (it != mCoordinates.end())
		{
			double xhigh = it->first;
			h[Counter] = xhigh - xlow;
		}
		++Counter;
	}
	vector<double> beta;
	beta.resize(n - 1); //beta run from k = 1, n -1. Thats why all other vectors have been added 1 extra.

	for (int i = 0; i <= n - 2;++i)
	{
		beta[i] = 3 * (ma[i + 2] - ma[i + 1]) / h[i + 1] - 3 * (ma[i + 1] - ma[i]) / h[i];
	}
	mc.resize(n + 1);
	vector<double> l;
	l.resize(n + 1);
	vector<double> z;
	z.resize(n + 1);
	l[0] = 1;
	mu[0] = 0;
	z[0] = 0;
	
	int Counter2 = 1;
	for (map<double, double>::iterator it = mCoordinates.begin(); it != mCoordinates.end();)
	{
		double xmin1 = it->first;
		++it;
		++it;
		if (it != mCoordinates.end())
		{
			double xplus1 = it->first;
			--it;
			l[Counter2] = 2 * (xplus1 - xmin1) - h[Counter2 - 1] * mu[Counter2 - 1];
		}
		++Counter2;
	}

	for (int i = 1; i < n - 1; ++i)
	{
		mu[i] = h[i] / l[i];
		z[i] = (beta[i-1] - h[i - 1] * z[i - 1]) / l[i]; //Take one from betam because it starts at 1 instead of 0;
	}
	l[n] = 1;
	z[n] = 0;
	mc[n] = 0;

	for (int i = n - 2; i >= 0; --i)
	{
		mc[i] = z[i] - mu[i] * mc[i + 1];
		mb[i] = (ma[i + 1] - ma[i]) / h[i] - h[i] * (mc[i + 1] + 2 * mc[i]) / 3;
		md[i] = (mc[i + 1] - mc[i]) / 3 * h[i];
	}

	mOutputMatrix.resize(n, vector<double>(4, 0)); //Initialising output matrix. Each row is one spline polynomial.
	

	for (int i = 0; i < n - 1; ++i)
	{
		mOutputMatrix[i] = { ma[i], mb[i], mc[i], md[i] };
	}
}

double CubicSpline::FindValue(double x)
{
	UpdateSpline();
	int TermNum = 0;
	map <double, double>::iterator it = mCoordinates.begin();
	if (x < it->first)
	{
		exit(EXIT_FAILURE);
	}
	for ( ; it != mCoordinates.end();)
	{
		++it;
		if (x == it->first)
		{
			return it->second;
		}
		else if (x < it->first)
		{
			--it;
			return ma[TermNum] + mb[TermNum] * (x - it->first) +
				mc[TermNum] * pow(x - it->first, 2) + md[TermNum] * 
				pow(x - it->first, 2);
		}
		++TermNum;

	}
		exit(EXIT_FAILURE);
}