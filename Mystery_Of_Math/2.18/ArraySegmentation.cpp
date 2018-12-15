#include"stdafx.h"
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<math.h>
#include<vector>
#include<time.h>
#include<string.h>
#include<set>
#define NUM 5
using namespace std;

//method1: enumeration--O(4^N) 
//这个算法不用担心元素重复的问题。
void closest_subset_e(int *dat,int N,int &res,int half_sum)
{
	vector<set<int> >subsum;
	for (int i = 0; i <= N; ++i)
	{
		subsum.push_back(set<int>{});
	}
	subsum[0].insert(0);
	for (int i = 0,i_max; i < 2*N; ++i)
	{
		i_max = min(i, N - 1);
		for (int k = i_max; k >= 0; --k)
		{
			for (auto v : subsum[k])
			{
				int temp = v + dat[i];
				if(temp <= half_sum)
					subsum[k + 1].insert(temp);
			}
		}
	}

	for (auto i : (subsum[N]))
	{
		res = max(res, i);
	}
}

//method2: number_dp--O(N*N*sum)
//当元素允许重复的时候，编程之美给出的算法是有问题的，因为它没有考虑元素的重复使用的问题。
//睡了一觉以后，我发现问题是当遍历到第k个元素的时候，它忽略了：
//当这个元素在第i次里面已经被使用了，在第(i+1)次的时候就不能再次用它了，也就是说需要额外开一个动态规划数组
void closest_subset_n(int *dat, int N, int &res, int half_sum)
{
	bool **dp = new  bool*[N+1];
	bool **dpt = new bool*[N+1];
	for (int k = 0; k <= N; ++k)
	{
		dp[k] = new bool[half_sum+1];
		for (int j = 0; j <= half_sum; ++j)
			dp[k][j] = false;
	}
	for (int k = 0; k <= N; ++k)
	{
		dpt[k] = new bool[half_sum + 1];
		for (int j = 0; j <= half_sum; ++j)
			dpt[k][j] = false;
	}
	dp[0][0] = dpt[0][0] = true;
	for (int k = 0; k < 2 * N; ++k)
	{

		//前k个元素中，取任意i个，i的数目不超过N
		for (int i = 1; (i <= k+1 && i <= N); ++i)
		{
			for (int v = 0; v <= half_sum; ++v)
			{
				//如果在前(k-1)个元素中，(i-1)个元素之和符合要求
				if (dp[i - 1][v] && v+dat[k] <= half_sum)
					dpt[i][v + dat[k]] = true;
			}
		}
		for (int s = 0; s <= N; ++s)
		{
			for (int t = 0; t <= half_sum; ++t)
			{
				dp[s][t] |= dpt[s][t];
				dpt[s][t] = dp[s][t];
			}
		}
		
	}
	for (int i = 0; i <= N; ++i)
	{
		for (int j = 0; j <= half_sum; ++j)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = half_sum; i >= 0; --i)
	{
		if (dp[N][i])
		{
			res = i;
			return;
		}
	}
}

int main()
{
	srand(int(time(NULL)));
	int res = 0, res2 = 0,sums = 0;
	do {
		res = 0, sums = 0, res2 = 0;
		int N = 2 * (rand() % NUM + 1);
		int *dat = new int[N];
		int min_num = INT_MAX;
		for (int i = 0; i < N; ++i)
		{
			dat[i] = rand() % (NUM)+NUM;
			min_num = min(min_num, dat[i]);
			sums += dat[i];
		}
		//如果有元素小于0，就加上一个偏置量使它大于零。
		if (min_num < 0)
		{
			for (int i = 0; i < N; ++i)
			{
				dat[i] -= min_num;
				sums -= min_num;
			}
		}
		sort(dat, dat + N);
		closest_subset_e(dat, N / 2, res, sums / 2);
		closest_subset_n(dat, N / 2, res2, sums / 2);
		for (int i = 0; i < N; ++i)
			cout << dat[i] << " ";
		cout << endl << "The data array's size is: " << N << endl;
		cout << "Closest subset's distance is:" << sums - 2 * res << " " << sums - 2 * res2 << endl;
	} while (res == res2);
	//int test[4] = { 0,2,3,3 }, res_t = 0;
	//closest_subset_n(test,2,res_t,4);
	//cout << res_t<<endl;
	return 0;
}
