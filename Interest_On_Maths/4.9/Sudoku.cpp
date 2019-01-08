#include"grids.h"
using namespace std;


int main()
{
	Grids tests;
	tests.output();
	tests.row_swap(0, 1);
	cout << endl;
	tests.output();
	return 0;
}
