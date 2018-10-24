#include"stdafx.h"
#include <iostream>
#include<random>
#include<algorithm>
#include<windows.h>
#include<map>
#include<ctime>
using namespace std;

int main()
{
	int N = 5,champ,champ_seat;
	srand(int(time(NULL)));
	//index ranges from 0 to i-1
	for (int i = N,pc; i < N*2; ++i)
	{
		int *fly_seat = new int[i-1];
		int *counter = new int[i - 1];
		int *fly_map = new int[i - 1];
		int *seat_map = new int[i - 1];
		map<int, int>find_seat;
		//这里金刚在队伍中的序号是先验知识，所以是提前生成，而无需遍历的
		champ = rand() % (i-1);
		//initialize the index array and the corrensponding pc
		for (int j = 0; j < i - 1; ++j)
			counter[j] = 0;
		
		//但是金刚选择座位这个过程是整个实验的一个部分，所以需要做遍历
		for (int cs = 0; cs < i; ++cs)
		{
			champ_seat = cs;
			//initialize the index array and the corrensponding pc
			for (int j = 0; j < i - 1; ++j)
				fly_seat[j] = j;

			//construct 2 mapping
			for (int j = 0; j < i; ++j)
			{
				if (j < champ)
					fly_map[j] = j;
				else if (j > champ)
					fly_map[j - 1] = j;
				if (j < champ_seat)
					seat_map[j] = j;
				else if (j > champ_seat)
					seat_map[j - 1] = j;
			}
			for (int j = 0; j < i - 1; ++j)
				find_seat.insert({ fly_map[j],seat_map[j] });

			pc = 0;
			do
			{
				for (int j = 0, k; j < i - 1; ++j)
				{
					k = fly_seat[j];
					if (find_seat[fly_map[fly_seat[j]]] == seat_map[j])
						counter[k]++;
				}
				pc++;
			} while (next_permutation(fly_seat, fly_seat + i - 1));
		}
		cout << "seat number is: " << i << endl<<"total permutation is: "<<i*pc<<endl;
		for (int j = 0; j < i-1; ++j)
			cout << counter[j] <<" ";
		cout << endl<<endl;
	}

	return 0;
}
