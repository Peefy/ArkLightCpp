
#ifndef __DATE_TIME_H
#define __DATE_TIME_H

#include <string>

#if defined _MSC_VER
#include <sysinfoapi.h>
#else
#include <iostream> 
#include <ctime>
#endif 

#include <chrono>
#include <thread>

using namespace std;

namespace arklight
{
namespace time
{

typedef unsigned long long ulong;
typedef long long slong;

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

struct TimeSpan
{
public:
    explicit TimeSpan(slong ticks);
    TimeSpan(int hours, int minutes, int seconds);
    TimeSpan(int days, int hours, int minutes, int seconds);
    TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
    virtual ~TimeSpan() {}
private:
    TimeSpan() {}
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
    slong Ticks() const {
        return _ticks;
    }
    int Days() const {
        return (int)(_ticks / 864000000000L);
    }
    int Hours() const {
        return (int)(_ticks / 36000000000L % 24);
    }
    int Milliseconds() const {
        return (int)(_ticks / 10000 % 1000);
    }
    int Minutes() const {
        return (int)(_ticks / 600000000 % 60);
    }
    int Seconds() const {
        return (int)(_ticks / 10000000 % 60);
    }
    double TotalDays() const {
        return (double)_ticks * 1.1574074074074074E-12;
    }
    double TotalHours() const {
        return (double)_ticks * 2.7777777777777777E-11;
    }
    double TotalMilliseconds() {
		double num = (double)_ticks * 0.0001;
		if (num > 922337203685477.0)
		{
			return 922337203685477.0;
		}
		if (num < -922337203685477.0)
		{
			return -922337203685477.0;
		}
		return num;
    }
    double TotalMinutes() {
        return (double)_ticks * 1.6666666666666667E-09;
    }
    double TotalSeconds() {
        return (double)_ticks * 1E-07;
    }
private:
	slong _ticks;
    static volatile bool _legacyConfigChecked;
	static volatile bool _legacyMode;
    static TimeSpan Interval(double value, int scale);
    slong TimeToTicks(int hour, int minute, int second);
    void judgeTicksIsMin() {
        if (_ticks == MinValueTimeSpanTicks) {
            throw std::exception("overflow duration");
        }
    }
    double TicksToOADate(slong value); 
};

struct TimeZone
{

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
    bool Equals(const DateTime value); 
    DateTime operator +(const TimeSpan& t);
    DateTime operator -(const TimeSpan& t);
    DateTime operator -(const DateTime& d);
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
    inline slong getInternalTicks() const {
        return (slong) (_dateData & 0x3FFFFFFFFFFFFFFF);
    }
    inline ulong getInternalKind() const {
        return (ulong) (_dateData & -4611686018427387904L);
    }
    inline bool IsAmbiguousDaylightSavingTime() const {
		return getInternalKind() == 13835058055282163712uL;
	}
    void judgeMillisecond(int& millisecond) {
        if (millisecond < 0 || millisecond >= 1000)
	    {
		    throw std::exception("millisecond ArgumentOutOfRange_Range");
	    }
    }
    void judgeDateTimeKind(DateTimeKind& kind) {
        if (kind < DateTimeKind::Unspecified || kind > DateTimeKind::Local)
	    {
		    throw std::exception("Argument_InvalidDateTimeKind"); 
	    }
    }
    slong judgeNumTicks(int& year, int& month, int& day, int& hour, int& minute, int& second, int& millisecond) {
        slong num = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
	    num += (slong)millisecond * 10000L;
	    if (num < 0 || num > MaxTicks)
	    {
            throw std::exception("Arg_DateTimeRange");
	    }
        return num;
    }
    void judgeTicks(slong& ticks) {
        if (ticks < 0 || ticks > MaxTicks)
	    {
            throw std::exception("ArgumentOutOfRange_DateTimeBadTicks");
	    }
    }
    void judgeAllParas(int& year, int& month, int& day, int& hour, int& minute, int& second, int& millisecond, DateTimeKind& kind){
        judgeMillisecond(millisecond);
        judgeDateTimeKind(kind);
        judgeNumTicks(year, month, day, hour, minute, second, millisecond);
    }
    slong ToBinaryRaw();
    int GetDatePart(int part);
    void GetDatePart(int* year, int* month, int* day);
    DateTime ToLocalTime(bool throwOnOverflow);
    static double TicksToOADate(slong value);
    static slong DateToTicks(int year, int month, int day);
    static slong TimeToTicks(int hour, int minute, int second);
    static slong DoubleDateToTicks(double value);
};

struct DateTimeEx : public DateTime
{
    
};


}
}

#endif
