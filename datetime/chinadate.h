
#ifndef __CHINA_DATE_H__
#define __CHINA_DATE_H__

#include <string>
#include <ctime>

#include "datetime.h"

using namespace std;

namespace arklight
{
namespace datetime
{

#define __OUT__
#define __IN__

typedef wstring String;

class ChinaDateBase
{
public:
    ChinaDateBase();
    ChinaDateBase(ChinaDateBase &&) = default;
    ChinaDateBase(const ChinaDateBase &) = default;
    ChinaDateBase &operator=(ChinaDateBase &&) = default;
    ChinaDateBase &operator=(const ChinaDateBase &) = default;
    virtual ~ChinaDateBase();
private:
    int _time = 0;
    int _tick = 0;
private:
    int _intYear;       // 农历年(整型)
    int _intMonth;      // 农历月(整型)
    int _intDay;        // 农历天(整型)
    String _strYear;   // 农历年(字符)
    String _strMonth;  // 农历月(字符)
    String _strDay;    // 农历天(字符)
    String _anm;       // 农历属相
    String _socalTerm; // 二十四节气
    String _ftvl;      //阴历节日
    String _ftvs;      //阳历节日
public:
    int GetLongSecond();
    static int GetDaysByMonth(int y, int m);
    static DateTime GetMondayDateByDate(DateTime& dt);
    static ChinaDateBase GetChinaDate(DateTime& dt);
};

using ChinaDate = ChinaDateBase;


} // namespace util
} // namespace arklight

#endif
