
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

template <typename StringT>
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
    StringT _strYear;   // 农历年(字符)
    StringT _strMonth;  // 农历月(字符)
    StringT _strDay;    // 农历天(字符)
    StringT _anm;       // 农历属相
    StringT _socalTerm; // 二十四节气
    StringT _ftvl;      //阴历节日
    StringT _ftvs;      //阳历节日
public:
    int GetLongSecond();

};

using ChinaDate = ChinaDateBase<wstring>;

} // namespace util
} // namespace arklight

#endif
