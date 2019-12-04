
#include <iostream>

#include "../../datetime/datetime.h"
#include "../../datetime/chinadate.h"

using namespace arklight::datetime;

int main()
{
    std::cout << "Hello World!\n"; 
	auto now = DateTime::Now();
	cout << now.ToString() << endl;
	ChineseCalendar c = ChineseCalendar(now);
	wcout << c.AnimalString();
	getchar();
	return 0;
}


