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
using namespace std;

//problem 1: to count the number of 0 after N!
int count_factorial_zero(int n)
{
	int res = 0;
	while (n)
	{
		n /= 5;
		res += n;
	}
	return res;
}

//problem 2: to find the last bit of 1
int find_last_one(int n)
{
	int res = 0;
	while (n)
	{
		n >>= 1;
		res += n;
	}
	return res;
}

//problem 3: to check whether x is powers of 2
bool check_2_pow(int x)
{
	return x > 0 && (x&(x - 1) == 0);
}

int main()
{
	//generate data
	srand((unsigned)time(NULL));
	int x = rand() % N;
	cout << "x: "<<x<<" "<<count_factorial_zero(x) <<" "<<find_last_one(x)<<" "<<check_2_pow(x)<< endl;
}
