#pragma GCC diagnostic error "-std=c++11" 

#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <memory>

#include "util/chinadate.h"
#include "platform/platform.hpp"

using namespace std;
using namespace arklight::util;

int main()
{  
    auto i = 0;
    auto j = L"123";
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    for(auto num : nums)
    {
        cout << num << " ";
    }
    std::cout << [](float f) -> int { return std::abs(f); } (-3.5);
    auto lambda = [] (float val) -> int { return val * 100; };
    float f0 = 1.0;
    std::cout << [=](float f) mutable { return f0 += std::abs(f); } (-3.5);
    std::cout << '\n' << f0 << '\n';
    cout << endl;
    cout << "hello world" << endl;
    cout << "hello world" << endl;
    ChinaDate* chinadate = new ChinaDate;
    cout << chinadate->GetLongSecond() << endl;
    getchar();
    return 0;
}

