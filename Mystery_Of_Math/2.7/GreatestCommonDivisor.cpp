#include <iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<math.h>
#include<vector>
#include<time.h>
#include<string.h>
#define N 100
using namespace std;

int gcd_module(int x, int y)
{
	if (x > y)
		return gcd_module(y, x);
	if (!x)
		return y;
	return gcd_module(y%x, x);
}

int gcd_subtract(int x, int y)
{
	if (x > y)
		return gcd_subtract(y, x);
	if (!x)
		return y;
	return gcd_subtract(x,y-x);
}

int gcd_log2(int x, int y)
{
	if (x > y)
		return gcd_log2(y, x);
	if (!x)
		return y;
	if (x & 1)
	{
		if (y & 1)
			return gcd_log2(x, y - x);
		else
			return gcd_log2(x, y >> 1);
	}
	else if (y & 1)
		return gcd_log2(x >> 1, y);
	else
		return 2*gcd_log2(x >> 1, y >> 1);
}

int main()
{
	//generate data
	srand((unsigned)time(NULL));
	int x = rand() % N, y = rand() % N;
	cout << "gcd(" << x << "," << y << ") = "<<gcd_module(x, y)<<endl;
	cout << "gcd(" << x << "," << y << ") = " << gcd_module(x, y) << endl;
	cout << "gcd(" << x << "," << y << ") = " << gcd_log2(x, y) << endl;
}
