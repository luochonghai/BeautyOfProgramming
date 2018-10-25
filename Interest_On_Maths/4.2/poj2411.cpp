#include"stdafx.h"
#include <iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
int n, m, w;
const int maxn = 15;
long long d[maxn][1 << 15];
int path[5000000][2];

void get(int c, int pre, int now)
{
	if (c > m)
		return;
	else if (c == m)
	{
		path[w][0] = pre;
		path[w++][1] = now;
		return;
	}
	get(c + 1, (pre << 1) |1,now << 1);
	get(c + 1, (pre << 1), (now << 1) | 1);
	get(c + 2, (pre << 2) | 3, (now << 2) | 3);
}

int main()
{
	while (scanf_s("%d%d", &n, &m), n&&m)
	{
		w = 0;
		if (m > n)
			swap(n, m);
		if (m % 2 && n % 2)
		{
			printf("%d\n", 0);
			continue;
		}
		get(0, 0, 0);
		memset(d, 0, sizeof(d));
		d[0][(1 << m) - 1] = 1;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < w; ++j)
			{
				d[i + 1][path[j][1]] += d[i][path[j][0]];
			}
		}
		printf("%I64d\n",d[n][(1<<m)-1]);

	}
}
