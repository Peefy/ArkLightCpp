
#include <stdint.h>
#include <iostream>
#include <vector>
#include <memory>

#include "util/chinadate.h"

using namespace std;

int main()
{  
    auto i = 0;
    auto nums = {1, 2, 3, 4, 5};
    for(auto num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "hello world" << endl;
    unique_ptr<util::ChinaDate> chinadate(new util::ChinaDate);
    cout << chinadate->GetLongSecond() << endl;
    getchar();
    return 0;
}

