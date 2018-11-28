#include"stdafx.h"
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<math.h>
#include<vector>
#include<time.h>
#include<string.h>
#define N 10
using namespace std;

//method 1: O(N^2)
int sort_common(int *ori_data)
{
	int **dp = new int*[N+1];
	for (int i = 0; i < 1+N; ++i)
	{
		dp[i] = new int[N];
		for (int j = 0; j < 1+N; ++j)
			dp[i][j] = 0;
	}
	int sort_data[N];
	for (int i = 0; i < N; ++i)
		sort_data[i] = ori_data[i];
	sort(sort_data, sort_data + N);
	int new_len = 1,now_i = 0;
	for (int i = 1; i < N; ++i)
	{
		if (sort_data[i] != sort_data[now_i])
		{
			sort_data[now_i+1] = sort_data[i];
			now_i++;
			new_len++;
		}
	}
	for (int i = 0; i < new_len; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (sort_data[i] == ori_data[j])
			{
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}
			else
			{
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}
	return dp[new_len][N];
}

//method 2: O(N^2)
int ai_end_longest(int *ori_data)
{
	int end_long[N],res = 0;
	memset(end_long, 0, sizeof(end_long));
	for (int i = 0; i < N; ++i)
	{
		end_long[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (ori_data[i] > ori_data[j] && end_long[j] + 1 > end_long[i])
				end_long[i] = end_long[j] + 1;
		}
	}
	for (int i = 0; i < N; ++i)
		res = max(res, end_long[i]);
	return res;
}

//method 3: O(N*lg(N))
int search(vector<int>num, int target)
{
	int len = num.size();
	int head = 0, tail = len - 1;
	while (head < tail)
	{
		int median = (head + tail + 1) / 2;
		if (num[median] == target)
			return median;
		else if (num[median] < target)
			head = median + 1;
		else
			tail = median - 1;
	}
	if (num[head] < target)
		return head + 1;
	return head;
}

int LengthI_EndNumMinimum(int *ori_data)
{
	vector<int>mini_ele(1, ori_data[0]);
	for (int i = 1; i < N; ++i)
	{
		if (ori_data[i] > *(mini_ele.end() - 1))//input the newly-generated array's largest number into the recording dataset
			mini_ele.push_back(ori_data[i]);
		else//change the least number of the array recorded in the recording dataset whose last nubmer is larger than the newly-visited number
			mini_ele[search(mini_ele, ori_data[i])] = ori_data[i];
	}
	return mini_ele.size();
}

int main()
{
	//generate data
	srand((unsigned)time(NULL));
	int data_list[N];
	for (int i = 0; i < N; ++i)
	{
		data_list[i] = rand() % N;
		cout << data_list[i] << endl;
	}
	cout << endl;
	cout << sort_common(data_list) << endl;
	cout << ai_end_longest(data_list) << endl;
	cout << LengthI_EndNumMinimum(data_list) << endl;
}
