
#ifndef __DATE_TIME_H
#define __DATE_TIME_H

#include <iostream> 
#include <string>

#if defined _MSC_VER
#include <Windows.h>
#include <time.h>
#else
#include <time.h>
#endif 

using namespace std;

typedef unsigned long long ulong;
typedef long long slong;

namespace arklight
{
namespace datetime
{

enum class DayOfWeek {
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

enum class DateTimeKind {
	Unspecified,
	Utc,
	Local
};

struct Time
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second; 
    int Millisecond;
};

struct TimeSpan
{
public:
    explicit TimeSpan(slong ticks);
    TimeSpan(int hours, int minutes, int seconds);
    TimeSpan(int days, int hours, int minutes, int seconds);
    TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
    virtual ~TimeSpan() {}
public:
    static TimeSpan Zero();
    static TimeSpan MinValue();
    static TimeSpan MaxValue();
    static TimeSpan FromDays(const double value);
    static TimeSpan FromHours(const double value);
    static TimeSpan FromMilliseconds(const double value);
    static TimeSpan FromMinutes(const double value);
    static TimeSpan FromSeconds(const double value);
    static TimeSpan FromTicks(const slong value);
    static int Compare(const TimeSpan& t1, const TimeSpan& t2);  
    static slong TimeToTicks(int hour, int minute, int second);  
public:
    TimeSpan Add(const TimeSpan& ts);
    TimeSpan Subtract(const TimeSpan& ts);
    bool Equals(const TimeSpan& ts);
    int CompareTo(const TimeSpan& value);
    TimeSpan Duration();
    TimeSpan Negate();
    string ToString();
    string ToString(string& format);
    TimeSpan operator -(const TimeSpan& t);
    TimeSpan operator +(const TimeSpan& t);
    bool operator ==(const TimeSpan& t);
    bool operator !=(const TimeSpan& t);
    bool operator <(const TimeSpan& t);
    bool operator <=(const TimeSpan& t);
    bool operator >(const TimeSpan& t);
    bool operator >=(const TimeSpan& t);
public:
    slong Ticks() const;
    int Days() const;
    int Hours() const;
    int Milliseconds() const;
    int Minutes() const;
    int Seconds() const;
    double TotalDays() const;
    double TotalHours() const;
    double TotalMilliseconds() const;
    double TotalMinutes() const;
    double TotalSeconds() const;
private:
	slong _ticks;
    static volatile bool _legacyConfigChecked;
	static volatile bool _legacyMode;
    static TimeSpan Interval(double value, int scale); 
    void judgeTicksIsMin();
    double TicksToOADate(slong value); 
};

struct TimeZone
{

};

class TimeZoneInfo
{
    enum TimeZoneInfoResult
    {
        Success,
		TimeZoneNotFoundException,
		InvalidTimeZoneException,
		SecurityException
    };
};

class DateTimeFormat
{
private:
	string RoundtripFormat = "yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK";
	string RoundtripDateTimeUnfixed = "yyyy'-'MM'-'ddTHH':'mm':'ss zzz";
};

struct DateTime
{
public:
    DateTime(slong ticks);
    DateTime(ulong dateData); 
    DateTime(slong ticks, DateTimeKind kind);
    DateTime(int year, int month, int day);
    DateTime(int year, int month, int day, int hour, int minute, int second);
    DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind);
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind);
    virtual ~DateTime() {}
private:
    DateTime(slong ticks, DateTimeKind kind, bool isAmbiguousDst);
    DateTime() {}
public:
    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static DateTime MinValue();
    static DateTime MaxValue();
    static DateTime FromBinary(const slong dateData);
    static DateTime FromBinaryRaw(const slong dateData);
    static DateTime FromFileTime(const slong fileTime);
    static DateTime FromFileTimeUtc(const slong fileTime);
    static DateTime FromOADate(const double d);
    static DateTime Parse(const string& s);
    static DateTime SpecifyKind(const DateTime& value, const DateTimeKind& kind);
    static int Compare(const DateTime& t1, const  DateTime& t2);
    static int DaysInMonth(const int year, const int month);
    static bool IsLeapYear(const int year);
public:
    Time GetTime();
    DayOfWeek GetDayOfWeek();
    DateTimeKind GetDateTimeKind();
    TimeSpan GetTimeOfDay();
    DateTime Date();
    DateTime Add(const TimeSpan& value);
    DateTime Add(double value, int scale);
    DateTime AddDays(double value);
    DateTime AddHours(double value);
    DateTime AddMilliseconds(double value);
    DateTime AddMinutes(double value);
    DateTime AddMonths(int months);
    DateTime AddSeconds(double value);
    DateTime AddTicks(slong value);
    DateTime AddYears(int value);  
    TimeSpan Subtract(const DateTime& value);
    DateTime Subtract(const TimeSpan& value);
    DateTime ToLocalTime();
    DateTime ToUniversalTime();
    string ToString();
    string ToLongDateString();
    string ToLongTimeString();
    string ToShortDateString();
    string ToShortTimeString();
    double ToOADate();
    slong ToFileTime();
    slong ToFileTimeUtc();
    slong ToBinary();
    int CompareTo(const DateTime& value);
    bool Equals(const DateTime& value); 
    DateTime operator +(const TimeSpan& t);
    DateTime operator -(const TimeSpan& t);
    TimeSpan operator -(const DateTime& d);
    bool operator ==(const DateTime& d);
    bool operator !=(const DateTime& d);
    bool operator <(const DateTime& d);
    bool operator <=(const DateTime& d);
    bool operator >(const DateTime& d);
    bool operator >=(const DateTime& d);
public:
    int Day();
    int DayOfYear();
    int Hour();
    int Millisecond();
    int Minute();
    int Month();
    int Second();
    int Year();
    slong Ticks();
private:
    ulong _dateData = 0;
    inline slong getInternalTicks() const;
    inline ulong getInternalKind() const;
    inline bool IsAmbiguousDaylightSavingTime() const;
    void judgeMillisecond(int& millisecond);
    void judgeDateTimeKind(DateTimeKind& kind);
    slong judgeNumTicks(int& year, int& month, int& day, int& hour, int& minute, int& second, int& millisecond);
    void judgeTicks(slong& ticks);
    void judgeAllParas(int& year, int& month, int& day, int& hour, int& minute, int& second, int& millisecond, DateTimeKind& kind);
    slong ToBinaryRaw();
    int GetDatePart(int part);
    void GetDatePart(int* year, int* month, int* day);
    DateTime ToLocalTime(bool throwOnOverflow);
    static double TicksToOADate(slong value);
    static slong DateToTicks(int year, int month, int day);
    static slong TimeToTicks(int hour, int minute, int second);
    static slong DoubleDateToTicks(double value);
};

template<typename _strT>
struct DateTimeEx : public DateTime
{
public:
    using str_type = _strT;

    str_type ToExString() {
        auto str = ToString();
        return NULL;
    }

};

using DateTimeExWString = DateTimeEx<std::wstring>;

}
}

#endif
