#include"stdafx.h"
#include <iostream>
#include<random>
#include<ctime>
#include<queue>
#define N 21
using namespace std;

double dp[N][N][N][N][N];

void transfer_min(int *temp,int d1,int d2,int d3,int d4,int d5)
{
	temp[0] = d1, temp[1] = d2, temp[2] = d3, temp[3] = d4, temp[4] = d5;
	sort(temp, temp + 5);
}

int main()
{
	int book_num[5],temp_num[5];
	srand(int(time(NULL)));
	for (int i = 0; i < 5; ++i)
		book_num[i] = rand() % 20;

	sort(book_num, book_num + 5);

	dp[0][0][0][0][0] = 0;
	for (int d5 = 1; d5 <= book_num[4]; ++d5)
	{
		for (int d4 = 0; d4 <= min(book_num[3],d5); ++d4)
		{
			for (int d3 = 0; d3 <= min(book_num[2],d4); ++d3)
			{
				for (int d2 = 0; d2 <= min(book_num[1],d3); ++d2)
				{
					for (int d1 = 0; d1 <= min(book_num[0],d2); ++d1)
					{
						transfer_min(temp_num,d1,d2,d3,d4,d5-1);
						dp[d1][d2][d3][d4][d5] = 8.0 + dp[temp_num[0]][temp_num[1]][temp_num[2]][temp_num[3]][temp_num[4]];

						if (d4)
						{
							transfer_min(temp_num,d1,d2,d3,d4-1,d5-1);
							dp[d1][d2][d3][d4][d5] = min(dp[d1][d2][d3][d4][d5],15.2+dp[temp_num[0]][temp_num[1]][temp_num[2]][temp_num[3]][temp_num[4]]);
						}
						if (d3)
						{
							transfer_min(temp_num, d1, d2, d3 - 1, d4 - 1, d5 - 1);
							dp[d1][d2][d3][d4][d5] = min(dp[d1][d2][d3][d4][d5], 21.6 + dp[temp_num[0]][temp_num[1]][temp_num[2]][temp_num[3]][temp_num[4]]);
						}
						if (d2)
						{
							transfer_min(temp_num, d1, d2-1, d3 - 1, d4 - 1, d5 - 1);
							dp[d1][d2][d3][d4][d5] = min(dp[d1][d2][d3][d4][d5], 25.6 + dp[temp_num[0]][temp_num[1]][temp_num[2]][temp_num[3]][temp_num[4]]);
						}
						if (d1)
						{
							transfer_min(temp_num, d1-1, d2 - 1, d3 - 1, d4 - 1, d5 - 1);
							dp[d1][d2][d3][d4][d5] = min(dp[d1][d2][d3][d4][d5], 30.0 + dp[temp_num[0]][temp_num[1]][temp_num[2]][temp_num[3]][temp_num[4]]);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 5; ++i)
		cout <<"number of book "<<i+1<<": "<< book_num[i] <<endl;
	cout <<"the minimal value is: "<<dp[book_num[0]][book_num[1]][book_num[2]][book_num[3]][book_num[4]] << endl;
	return 0;
}
