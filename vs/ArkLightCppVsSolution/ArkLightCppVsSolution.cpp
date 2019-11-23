
#include <iostream>

#include "../../time/datetime.h"

using namespace arklight::time;

int main()
{
    std::cout << "Hello World!\n"; 
	cout << DateTime::UtcNow().Ticks() << endl;
	getchar();
	return -1;
}


