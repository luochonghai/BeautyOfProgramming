#include <windows.h>
#include <math.h>

const int SAMPLING_COUNT = 200;     // 抽样点数量 
const double PI = 3.1415926535;     // pi值
const int TOTAL_AMPLITUDE = 300;    // 抽样间隔时长

int main()
{
	SetThreadAffinityMask(GetCurrentThread(), 0x00000001);//只让当前线程所在cpu运行程序
	double busyTime[SAMPLING_COUNT];//存储每个抽样间隔内，运行的时长
	double radianIncrement = 2 * PI / SAMPLING_COUNT;//busy_time:idle_time时sin()函数递增的区间长度
	int amplitude = TOTAL_AMPLITUDE / 2;//调整“振幅”，使得屏幕中能够显示完整的sin()曲线波形
	for (int i = 0; i < SAMPLING_COUNT; i++) 
	{
		busyTime[i] = amplitude + sin(radianIncrement * i) * amplitude;//计算每个间隔内运行的时长
	}

	for (int j = 0; ; j = (j + 1) % SAMPLING_COUNT) 
	{
		int startTime = GetTickCount();//求现在运行了多久
		while ((int)(GetTickCount() - startTime) < busyTime[j])//进入busy状态
			;
		Sleep(TOTAL_AMPLITUDE - busyTime[j]);//进入idle状态
	}

	return 0;
}
