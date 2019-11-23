
#include <iostream>

#include "../../time/datetime.h"

using namespace arklight::datetime;

int main()
{
    std::cout << "Hello World!\n"; 
	auto time = DateTime::Now();
	cout << time.ToString() << endl;
	getchar();
	return 0;
}


