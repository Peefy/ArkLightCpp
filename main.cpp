
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <memory>

#include "time/datetime.h"
#include "platform/platform.hpp"

using namespace std;
using namespace arklight::time;

int main()
{  
    auto i = 0;
    auto j = L"123";
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    float f0 = 1.0;
    std::cout << '\n' << f0 << '\n';
    cout << "hello world" << endl;
    DateTime t = DateTime::UtcNow();
    cout << t.Ticks() << endl;
    return 0;
}

