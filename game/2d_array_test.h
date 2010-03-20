#include "2d_array.h"

int Test()
{
	ns_2d::Array<int> my_array1, my_array2(5, 5), my_array3(5, 5, 10);
	my_array1.Swap(my_array2);
	const ns_2d::Array<int> my_array = my_array1;
	int x = my_array(0, 0);
	x = my_array1(0, 0);
	x = my_array[ns_2d::Coords(0,0)];
	x = my_array1[ns_2d::Coords(0,0)];
	return 0;
}