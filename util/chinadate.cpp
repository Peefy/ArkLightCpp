
#include "chinadate.h"

namespace util{
    ChinaDate::ChinaDate()
    {
        this->tick = 0;
        this->time = 555;
    }
    
    ChinaDate::~ChinaDate()
    {
    }

    int ChinaDate::GetLongSecond()
    {
        return this->time;
    }

}
