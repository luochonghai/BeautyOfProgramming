#include"stdafx.h"
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<math.h>
#include<vector>
#include<time.h>
#include<string.h>
#define N 100
#define Err 1e-3
using namespace std;

int cross_product(double p1,double p2, double q1, double q2)
{
	return (p1 * q2 > p2 * q1)?1:-1;
}

bool p_in_tri_CP(vector<double> points, double p1, double p2)
{
	int signal = cross_product(p1,p2,points[0],points[1]),p_num = points.size()/2;
	for (int i = 1,temp_sig; i < p_num; ++i)
	{
		temp_sig = cross_product(p1- points[(2 * i + 2) % (2 * p_num)], p2- points[(2 * i + 3) % (2 * p_num)], 
			points[(2 * i)%(2*p_num)]- points[(2 * i+2) % (2 * p_num)], points[2 * i + 1]- points[(2 * i + 3) % (2 * p_num)]);
		cout << temp_sig << ":" << signal << endl;
		if (temp_sig != signal)
		{
			signal = 0;
			break;
		}
	}
	return signal == 0?false:true;
}

bool p_in_tri_SIZE(vector<double> points,double p1,double p2)
{
	vector<double>Pe,Te,Ts;
	int p_num = points.size()/2;
	for (int i = 0; i < p_num; ++i)
	{
		double Px = p1 - points[2 * i], Py = p2 - points[2 * i + 1],
			Tx = points[2 * i % (2 * p_num)] - points[2 * (i + 1) % (2 * p_num)],
			Ty = points[(2 * i+1) % (2 * p_num)] - points[(2*i + 3) % (2 * p_num)];
		Pe.push_back(sqrt(Px*Px+Py*Py));
		Te.push_back(sqrt(Tx*Tx + Ty * Ty));
	}

	for (int i = 0; i < p_num; ++i)
	{
		double Pp = (Pe[i%p_num]+Pe[(i+1)%p_num]+Te[i])/2.0;
		Ts.push_back(sqrt(Pp*(Pp- Pe[i%p_num])*(Pp- Pe[(i+1)%p_num])*(Pp-Te[i])));
	}
	double PT = (Te[0] + Te[1] + Te[2]) / 2.0,
		TS = sqrt(PT*(PT-Te[0])*(PT-Te[1])*(PT-Te[2]));
	return fabs(Ts[0] + Ts[1] + Ts[2] - TS) <= Err;
}

//Given convex polygon A1...An(the order of points is given in
//clockwise or counterclockwise direction) and point P(p1,p2), 
//check whether P is in the polygon or not.
bool p_in_pol_SIZE(vector<double> points, double p1, double p2)
{
	vector<double>Pe, Oe, Os, Te, Ts;
	int p_num = points.size() / 2;
	double O1 = 0, O2 = 0;
	for (int i = 0; i < p_num; ++i)
	{
		O1 += points[2 * i];
		O2 += points[2 * i + 1];
	}
	O1 /= (p_num + .0);
	O2 /= (p_num + .0);

	for (int i = 0; i < p_num; ++i)
	{
		double Px = p1 - points[2 * i], Py = p2 - points[2 * i + 1],
			Tx = points[2 * i % (2 * p_num)] - points[2 * (i + 1) % (2 * p_num)],
			Ty = points[(2 * i + 1) % (2 * p_num)] - points[(2 * i + 3) % (2 * p_num)],
			Ox = O1-points[2*i],Oy = O2-points[2*i+1];
		Pe.push_back(sqrt(Px*Px + Py * Py));
		Te.push_back(sqrt(Tx*Tx + Ty * Ty));
		Oe.push_back(sqrt(Ox*Ox+Oy*Oy));
	}

	for (int i = 0; i < p_num; ++i)
	{
		double Pp = (Pe[i%p_num] + Pe[(i + 1) % p_num] + Te[i]) / 2.0,
			Op = (Oe[i%p_num]+Oe[(i+1)%p_num]+Te[i])/2.0;
		Ts.push_back(sqrt(Pp*(Pp - Pe[i%p_num])*(Pp - Pe[(i + 1) % p_num])*(Pp - Te[i])));
		Os.push_back(sqrt(Op*(Op - Oe[i%p_num])*(Op - Oe[(i + 1) % p_num])*(Op - Te[i])));
	}
	double PT = 0, OT = 0;
	for (int i = 0; i < p_num; ++i)
	{
		PT += Ts[i];
		OT += Os[i];
	}
	return fabs(PT - OT) <= Err;
}

bool p_in_pol_CP(vector<double> points, double p1, double p2)
{
	int signal = cross_product(p1, p2, points[0], points[1]), p_num = points.size() / 2;
	for (int i = 1, temp_sig; i < p_num; ++i)
	{
		temp_sig = cross_product(p1 - points[(2 * i + 2) % (2 * p_num)], p2 - points[(2 * i + 3) % (2 * p_num)],
			points[(2 * i) % (2 * p_num)] - points[(2 * i + 2) % (2 * p_num)], points[2 * i + 1] - points[(2 * i + 3) % (2 * p_num)]);
		if (temp_sig != signal)
		{
			signal = 0;
			break;
		}
	}
	return signal == 0 ? false : true;
}

double tri_size(double p1, double p2, double p3, double p4, double p5, double p6)
{
	return p1 * p4 + p3 * p6 + p5 * p2 - p1 * p6 - p3 * p2 - p5 * p4;
}

bool p_in_pol_DET(vector<double>points, double p1, double p2)
{
	int p_num = points.size() / 2,
		signal = tri_size(p1, p2, points[0], points[1], points[2], points[3]) > 0.?1:-1;
	for (int i = 1,new_sig; i < p_num; ++i)
	{
		double sig = tri_size(p1,p2,points[2*i],points[2*i+1],points[(2*i+2)%(2*p_num)],points[(2*i+3)%(2*p_num)]);
		if (fabs(sig) < Err)
			return false;
		else if (sig > 0. && signal < 0)
			return false;
		else if (sig < 0. && signal > 0)
			return false;
	}
	return true;
}

int main()
{
	//generate data
	srand(time(NULL));
	int signal = 0,signal_2 = 0;
	do {
		vector<double>tests;
		for (int i = 0; i < 6; ++i)
		{
			tests.push_back((rand() % 10 - 2.0) / ((rand() % 1 + 1.0)));
			cout << tests[i] << " ";
			if (i % 2)
				cout << endl;
		}
		double p1 = (rand() % 10 - 2.0) / ((rand() % 1 + 1.0)),
			p2 = (rand() % 10 - 2.0) / ((rand() % 1 + 1.0));
		cout << p1 << "    " << p2 << endl;
		signal = p_in_pol_SIZE(tests, p1, p2);
		signal_2 = p_in_pol_DET(tests, p1, p2);
		cout<<"res:"<<signal<<" "<<signal_2 << endl;
	} while (!signal_2);
}
