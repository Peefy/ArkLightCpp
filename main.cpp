
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <memory>

#include "datetime/datetime.h"
#include "platform/platform.hpp"

using namespace std;
using namespace arklight::datetime;

#define enum_to_string(x) #x

int main()
{  
    std::cout << "Hello World!\n"; 
    std::cout << DateTime::Now().ToString() << endl;
    return 0;
}

