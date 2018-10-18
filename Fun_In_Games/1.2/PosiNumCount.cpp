#include<cstdio>

int main()//counter变量是用来显示打印的内容的，在实际情况下可以省略
{
	int counter = 1;
	for (int i = 0; i < 81; ++i)
	{
		if (i % 9 % 3 != i / 9 % 3)
		{
			printf("%d: (%d, %d)\n", counter, i % 9, i / 9);
			counter++;
		}
	}
	return 0;
}
