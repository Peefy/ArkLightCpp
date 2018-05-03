
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <memory>

#include "util/chinadate.h"

using namespace std;

void abssort(float *x, unsigned N)
{
  std::sort(x,
            x + N,
            [](float a, float b) { return std::abs(a) < std::abs(b); });
}

int main()
{  
    auto i = 0;
    auto nums = {1, 2, 3, 4, 5};
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
    unique_ptr<util::ChinaDate> chinadate(new util::ChinaDate);
    cout << chinadate->GetLongSecond() << endl;
    getchar();
    return 0;
}

