
#ifndef __CHINA_DATE_H__
#define __CHINA_DATE_H__

#include <string>
#include <ctime>
#include <memory>

#include "datetime.h"

using namespace std;

namespace arklight
{
namespace datetime
{

#define __OUT__
#define __IN__

// #define IS_USE_STRING_VIEW 1

#ifdef IS_USE_STRING_VIEW
#include <string_view>
typedef wstring_view String;
#else
typedef string String;
#endif

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

class ChineseCalendar
{
public:
    // 阳历节日
    struct SolarHolidayStruct {
        int Month;   
        int Day;
        int Recess;  // 假期长度
        String HolidayName;
        SolarHolidayStruct(int month, int day, int recess, String name) :
            Month(month), Day(day), Recess(recess), HolidayName(name)  {

        }
    };
    // 农历节日
    struct LunarHolidayStruct {
        int Month;
        int Day;
        int Recess;
        String HolidayName;

        LunarHolidayStruct(int month, int day, int recess, String name) {
            Month = month;
            Day = day;
            Recess = recess;
            HolidayName = name;
        }
    };

    struct WeekHolidayStruct {
        int Month;
        int WeekAtMonth;
        int WeekDay;
        String HolidayName;
        WeekHolidayStruct(int month, int weekAtMonth, int weekDay, String name) :
            Month(month), WeekAtMonth(weekAtMonth), WeekDay(weekDay), HolidayName(name)  {

        }
    };
private:
    DateTime _date;
    DateTime _datetime;
    int _cYear;
    int _cMonth;
    int _cDay;
    bool _cIsLeapMonth; //当月是否闰月
    bool _cIsLeapYear;  //当年是否有闰月
public:
    ChineseCalendar() = default;
    ChineseCalendar(DateTime& dt);
    ChineseCalendar(int cy, int cm, int cd, bool leapMonthFlag);
    virtual ~ChineseCalendar() = default;
private:
    int GetChineseMonthDays(int year, int month);
    inline int GetChineseLeapMonth(int year);
    int GetChineseLeapMonthDays(int year);
    int GetChineseYearDays(int year);
    String GetChineseHour(DateTime& dt);
    void CheckDateLimit(DateTime& dt);
    void CheckChineseDateLimit(int year, int month, int day, bool leapMonth);
    String ConvertNumToChineseNum(char n);
    bool BitTest32(int num, int bitpostion);
    int ConvertDayOfWeek(DayOfWeek dayOfWeek);
    bool CompareWeekDayHoliday(DateTime& date, int month, int week, int day);
public:
    String NewCalendarHoliday();
    String WeekDayHoliday();
    String DateHoliday();
    DateTime Date();
    DayOfWeek WeekDay();
    String WeekDayStr();
    String DateString();
    bool IsLeapYear();
    String ChineseConstellation();
    String ChineseHour();
    bool IsChineseLeapMonth();
    bool IsChineseLeapYear();
    int ChineseDay();
    int ChineseMonth();
    int ChineseYear();
    String ChineseDayString();
    String ChineseMonthString();
    String ChineseYearString();
    String ChineseDateString();
    String ChineseTwentyFourDay();
    String ChineseTwentyFourPrevDay();
    String ChineseTwentyFourNextDay();
    String Constellation();
    int Animal();
    String AnimalString();
    String GanZhiYearString();
    String GanZhiMonthString();
    String GanZhiDayString();
    String GanZhiDateString();
};


} // namespace util
} // namespace arklight

#endif
