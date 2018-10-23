#include"stdafx.h"
#include <iostream>
#include<random>
#include<windows.h>
#include<ctime>
using namespace std;

int BitCount_0(int dat)//a better method
{
	int res = 0;
	while (dat)
	{
		dat &= dat - 1;
		res++;
	}
	return res;
}

int BitCount_1(int n)
{
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
	return n;
}

int BitCount_2(int n)
{
	int temp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
	return ((temp + (temp >> 3)) & 030707070707)%63;
}

struct _byte
{
	unsigned a : 1;
	unsigned b : 1;
	unsigned c : 1;
	unsigned d : 1;
	unsigned e : 1;
	unsigned f : 1;
	unsigned g : 1;
	unsigned h : 1;
};

long get_bit_count(unsigned char b)
{
	struct _byte *by = (struct _byte*)&b;
	return (by->a + by->b + by->c + by->d + by->e + by->f + by->g + by->h);
}

int trans_digit(int a, int b)//求a与b的二进制表示有多少位不同
{
	return BitCount_0(a^b);
}

int main()
{
	//time_t sta_t = GetTickCount();
	//srand(int(time(NULL)));
	//for (int i = 0; i < 50000000; ++i)
	//{
	//	BitCount_2(rand() % INT_MAX);
	//}
	//time_t end_t = GetTickCount();
	//cout << end_t - sta_t << endl;
	cout << trans_digit(5,15)<<endl;
	return 0;
}
