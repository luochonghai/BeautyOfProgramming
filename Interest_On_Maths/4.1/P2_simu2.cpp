#include"stdafx.h"
#include <iostream>
#include<random>
#include<algorithm>
#include<windows.h>
#include<map>
#include<set>
#include<ctime>
using namespace std;

int main()
{
	int N = 5,champ,champ_seat;
	srand(int(time(NULL)));
	//index ranges from 0 to i-1
	for (int i = 3,pc; i < 8; ++i)
	{
		int *fly_seat = new int[i];
		int *counter = new int[i];
		int *isvisit = new int[i];
		map<int, int>find_seat;
		pc = 0;
		for (int j = 0; j < i; ++j)
			counter[j] = 0;

		//这里金刚在队伍中的序号是先验知识，所以是提前生成，而无需遍历的
		for (int ch = 0; ch < i; ++ch)
		{
			champ = ch;
			//champ = rand() % (i - 1);
			//initialize the index array and the corrensponding pc

			//但是金刚选择座位这个过程是整个实验的一个部分，所以需要做遍历
			set<int>not_mul;
			for (int cs = 0, signals; cs < i; ++cs)
			{
				champ_seat = cs;
				//initialize the index array and the corrensponding pc
				for (int j = 0; j < i; ++j)
					fly_seat[j] = j + 1;
				do
				{
					for (int ji = 0; ji < i; ++ji)
						isvisit[ji] = 0;
					isvisit[champ_seat] = 1;//has been visited
					if (fly_seat[champ] - 1 != champ_seat)//to check the 1st rule
						continue;
					signals = 1;//to record whether the following ends in break or not
					//check whether the permutation satisfies the request
					for (int ji = 0, k; ji < i; ++ji)
					{
						k = fly_seat[ji] - 1;//the ji-th person's seat number
						if (ji < champ)
						{
							if (isvisit[ji])//the ji-th seat has been visited
							{
								isvisit[k] = 1;//visit k-th seat
								continue;
							}
							else//must equal to ji
							{
								if (k != ji)//data of this round is wrong
								{
									signals = 0;
									break;
								}
							}
						}
						else if (ji > champ)
						{
							if (isvisit[ji])
							{
								isvisit[k] = 1;
								continue;
							}
							else
							{
								if (k != ji)
								{
									signals = 0;
									break;
								}
							}

						}
					}
					if (signals)
					{
						int res = 0;
						for (int ji = 0; ji < i; ++ji)
						{
							res *= 10;
							res += fly_seat[ji];
						}
						if (not_mul.count(res) == 0)
						{
							not_mul.insert(res);
							for (int ji = 0; ji < i; ++ji)
							{
								if (ji != champ && fly_seat[ji] - 1 == ji)
									counter[ji]++;
							}
							pc++;
						}
					}

				} while (next_permutation(fly_seat, fly_seat + i));
			}
		}
		cout << "N: " << i << " pc: "<<pc<<endl;
		for (int j = 0; j < i; ++j)
		{
			//if(j != champ)
				cout << counter[j] << " ";
		}
		cout << endl<<endl;
	}

	return 0;
}
