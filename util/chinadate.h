
#ifndef __CHINA_DATE_H
#define __CHINA_DATE_H

namespace ArkLight {
namespace Util {
    class ChinaDate
    {
    public:
        ChinaDate();
        ChinaDate(ChinaDate &&) = default;
        ChinaDate(const ChinaDate &) = default;
        ChinaDate &operator=(ChinaDate &&) = default;
        ChinaDate &operator=(const ChinaDate &) = default;
        virtual ~ChinaDate();
    
        int GetLongSecond();

    private:
        int time = 0;
        int tick;
    };
    
    }
}

#endif 

