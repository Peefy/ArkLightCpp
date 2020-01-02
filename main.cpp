
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <memory>

#include "datetime/datetime.h"
#include "datetime/chinadate.h"
#include "platform/platform.hpp"

using namespace std;
using namespace arklight::datetime;

#define enum_to_string(x) #x

int main()
{  
    std::cout << "Hello World!\n"; 
    auto now = DateTime::Now();
    // 现在时间
    std::cout << now.ToString() << endl;
    // 与标准时区的时差
    std::cout << (now - DateTime::UtcNow()).Hours() << endl;
    ChineseCalendar c = ChineseCalendar(now);
    cout << c.AnimalString();
    return 0;
}

