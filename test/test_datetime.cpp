
#include "../datetime/datetime.h"

#include <iostream>

using namespace std;

using namespace arklight::datetime;

static void TestDateTime() {
    auto nowTime = DateTime::Now();
    cout << nowTime.ToString() << endl;
    nowTime = nowTime.AddDays(120);
    cout << nowTime.ToString() << endl;
    nowTime = nowTime.AddHours(120);
    cout << nowTime.ToString() << endl;
    nowTime = nowTime.AddMinutes(120);
    cout << nowTime.ToString() << endl;
    nowTime = nowTime.AddYears(3);   
    cout << nowTime.ToString() << endl;
    cout << nowTime.Ticks() << endl;
}

static void TestTimeSpan() {
    auto nowTimeSpan = DateTime::Now() - DateTime::UtcNow();
    cout << nowTimeSpan.ToString() << endl;
    cout << nowTimeSpan.Hours() << endl;
    cout << nowTimeSpan.Days() << endl;
    cout << nowTimeSpan.Seconds() << endl;
    cout << nowTimeSpan.Minutes() << endl;
}
