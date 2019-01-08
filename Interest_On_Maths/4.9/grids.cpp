#include"grids.h"
using namespace std;

int trans(int ranks)
{
	int x = ranks / 3,
		y = ranks % 3;
	return y * 3 + x;
}

Sudoku::Sudoku(int i) :ranks(i)//0-8
{
	int sta = trans(i);//0-8
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			tables[i][j] = (sta + i * 3 + j) % 9;
	}
}

void Sudoku::read_data(int& ran,int ta[N][N])
{
	ran = ranks;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			ta[i][j] = tables[i][j];
		}
	}
}

void Sudoku::rewrite(int ran,int ta[N][N])
{
	ranks = ran;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			tables[i][j] = ta[i][j];
		}
	}
}

void Sudoku::output(int r)
{
	for (int i = 0; i < N; ++i)
	{
		cout << tables[r][i] << " ";
	}
}

Grids::Grids()
{
	for (int i = 0; i < LEN; ++i)
	{
		Sudoku res(i);
		stars.push_back(res);//0-8
	}
}

void Grids::row_swap(int a,int b)
{
	int ra,rb, ta[N][N],tb[N][N];
	for (int i = 0; i < N; ++i)
	{
		stars[N*a+i].read_data(ra, ta);
		stars[N*b+i].read_data(rb, tb);
		stars[N*b+i].rewrite(ra,ta);
		stars[N*a+i].rewrite(rb,tb);
	}
}


void Grids::output()
{
	for (int gi = 0; gi < N; ++gi)
	{
		for (int gj = 0; gj < N; ++gj)
		{
			for(int si = 0;si < N;++si)
				stars[gi*N + si].output(gj);
			cout << endl;
		}
	}
}