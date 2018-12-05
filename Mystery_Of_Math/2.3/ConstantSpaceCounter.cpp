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

void find_3_num(vector<int> dat,vector<int> &nums)
{
	vector<int>res = { 0,0,0 };
	for (int i = 0,signal; i < dat.size(); ++i)
	{
		signal = 0;
		//check whether any one equals to it first
		for (int j = 0; j < 3; ++j)
		{
			if (dat[i] == nums[j])
			{
				res[j]++;
				signal = 1;
				break;
			}
		}
		//check whether 0 exists in res
		if (signal == 0)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (res[j] == 0)
				{
					res[j]++, nums[j] = dat[i];
					signal = 1;
					break;
				}
			}
		}
		//if 0 not exist
		if (signal == 0)
		{
			for (int j = 0; j < 3; ++j)
			{
				res[j]--;
			}
		}
	}
}

int main()
{
	//generate data
	vector<int>tests = { 1,2,3,1,2,4,2,3,1,4,2,3,1,3,4,2,1,2,3,1,3,3,2,1,1,2,3,1,2,3,3,2,1,4 },
		nums = { -1,-2,-3 };
	find_3_num(tests,nums);
	find_3_num(tests, nums);
	find_3_num(tests, nums);
	for (int i = 0; i < nums.size(); ++i)
		cout << nums[i] << endl;
}
