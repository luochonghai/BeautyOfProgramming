#include"stdafx.h"
#include <iostream>
#include<random>
#include <cassert>
#include <cstdio>
#include<cstdlib>
#include<ctime>
#define random(x) (rand()%x)

using namespace std;
int tables[19] = {0,1,
				3,4,5,
				7,8,9,10,11,
				13,14,15,16,17,18,19,20,
				22};

class laobing
{
private:
	int *m_CakeArray;	// 烙饼信息数组
	int  m_nCakeCnt;	// 烙饼个数
	int  m_nMaxSwap;	// 最多交换次数。根据前面的推断，这里最多为
						// m_nCakeCnt * 2 
	int *m_SwapArray;	// 交换结果数组

	int *m_ReverseCakeArray;	// 当前翻转烙饼信息数组
	int *m_ReverseCakeArraySwap;	// 当前翻转烙饼交换结果数组
	int  m_nSearch;	// 当前搜索次数信息

public:
	laobing()
	{
		m_nCakeCnt = 0;
		m_nMaxSwap = 0;
	}
	~laobing()
	{
		if (m_CakeArray != NULL)
			delete m_CakeArray;

		if (m_SwapArray != NULL)
			delete m_SwapArray;

		if (m_ReverseCakeArray != NULL)
			delete m_ReverseCakeArray;

		if (m_ReverseCakeArraySwap != NULL)
			delete m_ReverseCakeArraySwap;

	}

	//
	// 计算烙饼翻转信息
	// @param
	// pCakeArray	存储烙饼索引数组
	// nCakeCnt	烙饼个数
	//
	void Run(int* pCakeArray, int nCakeCnt)
	{
		Init(pCakeArray, nCakeCnt);
		m_nSearch = 0;
		Search(0);
	}

	void mOutput(int* CakeArray, int nCakeCnt, int *m_SwapArray, int m_nMaxSwap)
	{
		int t;
		for (int i = 0; i < m_nMaxSwap; i++)//swap times
		{
			for (int j1 = 0, j2 = m_SwapArray[i]; j1<j2; j1++, j2--) //reverse array
			{
				t = CakeArray[j1];
				CakeArray[j1] = CakeArray[j2];
				CakeArray[j2] = t;
			}

			for (int k = 0; k<nCakeCnt; ++k)
				printf("%d ", CakeArray[k]);
			printf("\n");

		}
	}
	void Output()// 输出烙饼具体翻转的次数
	{
		for (int i = 0; i < m_nMaxSwap; i++)
		{
			printf("%d ", m_SwapArray[i]);
		}

		printf("\n|Search Times| : %d\n", m_nSearch);
		printf("Total Swap times = %d\n", m_nMaxSwap);

		mOutput(m_CakeArray, m_nCakeCnt, m_SwapArray, m_nMaxSwap);//输出交换过程
	}
private:
	//
	// 初始化数组信息
	// @param
	// pCakeArray	存储烙饼索引数组
	// nCakeCnt	烙饼个数
	//
	void Init(int* pCakeArray, int nCakeCnt)
	{
		assert(pCakeArray != NULL);
		assert(nCakeCnt > 0);

		m_nCakeCnt = nCakeCnt;

		// 初始化烙饼数组
		m_CakeArray = new int[m_nCakeCnt];
		assert(m_CakeArray != NULL);
		for (int i = 0; i < m_nCakeCnt; i++)
		{
			m_CakeArray[i] = pCakeArray[i];
		}
		// 设置最多交换次数信息
		m_nMaxSwap = UpBound(m_nCakeCnt);
		// 初始化交换结果数组 
		m_SwapArray = new int[m_nMaxSwap + 1];
		assert(m_SwapArray != NULL);
		// 初始化中间交换结果信息
		m_ReverseCakeArray = new int[m_nCakeCnt];
		for (int i = 0; i < m_nCakeCnt; i++)
		{
			m_ReverseCakeArray[i] = m_CakeArray[i];
		}
		m_ReverseCakeArraySwap = new int[m_nMaxSwap];
	}


	int UpBound(int nCakeCnt)// 寻找当前翻转的上界
	{
		/*第三次优化处*/
		//return nCakeCnt * 2;
		/*第四次优化处*/
		//return (5 * nCakeCnt + 5) / 3;
		return tables[nCakeCnt - 1];
	}
	int LowerBound(int* pCakeArray, int nCakeCnt) // 寻找当前翻转的下界
	{
		int t, ret = 0;
		// 根据当前数组的排序信息情况来判断最少需要交换多少次
		for (int i = 1; i < nCakeCnt; i++)
		{
			// 判断位置相邻的两个烙饼，是否为尺寸排序上相邻的
			t = pCakeArray[i] - pCakeArray[i - 1];
			if ((t == 1) || (t == -1))
			{
			}
			else
			{
				ret++;
			}
		}

		/*第二次优化处*/
		if (pCakeArray[nCakeCnt - 1] != nCakeCnt - 1)
			ret++;
		return ret;
	}
	// 排序的主函数
	void Search(int step)
	{
		int i, nEstimate;
		m_nSearch++;
		// 估算这次搜索所需要的最小交换次数
		nEstimate = LowerBound(m_ReverseCakeArray, m_nCakeCnt);
		/*第一次优化处*/
		//if (step + nEstimate > m_nMaxSwap)
		if (step + nEstimate >= m_nMaxSwap)
			return;

		// 如果已经排好序，即翻转完成，输出结果
		if (IsSorted(m_ReverseCakeArray, m_nCakeCnt))
		{
			if (step < m_nMaxSwap)
			{
				m_nMaxSwap = step;
				for (i = 0; i < m_nMaxSwap; i++)
					m_SwapArray[i] = m_ReverseCakeArraySwap[i];
			}
			return;
		}
		// 递归进行翻转
		for (i = 1; i < m_nCakeCnt; i++)
		{
			Revert(0, i);//反转
			m_ReverseCakeArraySwap[step] = i; //第一步 反转的哪一个
			Search(step + 1);
			Revert(0, i);
		}
	}
	//
	// true : 已经排好序
	// false : 未排序
	//
	bool IsSorted(int* pCakeArray, int nCakeCnt)
	{
		for (int i = 1; i < nCakeCnt; i++)
		{
			if (pCakeArray[i - 1] > pCakeArray[i])
			{
				return false;
			}
		}
		return true;
	}

	//
	// 翻转烙饼信息
	//    
	void Revert(int nBegin, int nEnd)
	{
		assert(nEnd > nBegin);
		int i, j, t;

		// 翻转烙饼信息
		for (i = nBegin, j = nEnd; i < j; i++, j--)
		{
			t = m_ReverseCakeArray[i];
			m_ReverseCakeArray[i] = m_ReverseCakeArray[j];
			m_ReverseCakeArray[j] = t;
		}
	}
};
int main()
{
	srand((int)time(0));
	int pancake_num;
	scanf_s("%d",&pancake_num);
	laobing ll;//这里ll 不可以加括号
	laobing *l = new laobing();
	int *aa = new int[pancake_num];
	//随机生成一个序列
	for (int i = 0; i < pancake_num; ++i)
		aa[i] = i;

	//洗扑克牌算法
	for (int i = 0; i < pancake_num; ++i)
		swap(aa[i], aa[random(pancake_num - i) + i]);

	l->Run(aa, pancake_num);
	l->Output();

	ll.Run(aa, pancake_num);
	return 0;
}
