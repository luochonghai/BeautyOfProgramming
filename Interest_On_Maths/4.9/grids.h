#pragma once
#define N 3
#define LEN N*N

#include<iostream>
#include<vector>
using namespace std;

class Sudoku
{
public:
	Sudoku(int);
	void rewrite(int,int [N][N]);
	void output(int r);
	void read_data(int&,int [N][N]);
private:
	int ranks;
	int tables[N][N];
};

class Grids
{
public:
	Grids();
	void row_swap(int a, int b);//0-2
	void col_swap(int a, int b);//0-2
	void rot_cwise();
	void rot_acwise();
	void transpose();
	void output();
private:
	vector<Sudoku>stars;
};



int trans(int);