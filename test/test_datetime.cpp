
#include "datetime.h"

#include <iostream>

using namespace std;

using namespace arklight::time;

static void TestDataTime() {
    auto nowTime = DateTime::Now();
    cout << nowTime.Second();
}
