
#ifndef __DATE_TIME_H
#define __DATE_TIME_H

#include <string>

#if defined _MSC_VER
#include <sysinfoapi.h>
#else
#include <iostream> 
#include <ctime>
#endif 

using namespace std;

namespace arklight
{
namespace time
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

struct TimeSpan
{
public:
    explicit TimeSpan(long ticks);
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
    static TimeSpan FromTicks(const long value);
    static TimeSpan Parse(string& s);
    static int Compare(const TimeSpan& t1, const TimeSpan& t2);    
public:
    TimeSpan Add(const TimeSpan& ts);
    TimeSpan Subtract(const TimeSpan& ts);
    bool Equals(const TimeSpan& ts);
    int CompareTo(const TimeSpan& value);
    TimeSpan Duration();
    TimeSpan Negate();
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
    long long Ticks;
    int Days;
    int Hours;
    int Milliseconds;
    int Minutes;
    int Seconds;
    double TotalDays;
    double TotalHours;
    double TotalMilliseconds;
    double TotalMinutes;
    double TotalSeconds;
private:
	long long _ticks;
    static volatile bool _legacyConfigChecked;
	static volatile bool _legacyMode;
    static TimeSpan Interval(double value, int scale);
    static long TimeToTicks(int hour, int minute, int second);
};

struct DateTime
{
public:
    DateTime(long ticks);
    DateTime(unsigned long long dateData); 
    DateTime(long ticks, DateTimeKind kind);
    DateTime(int year, int month, int day);
    DateTime(int year, int month, int day, int hour, int minute, int second);
    DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind);
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind);
    virtual ~DateTime() {}
private:
    DateTime(long ticks, DateTimeKind kind, bool isAmbiguousDst);
    DateTime() {}
public:
    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static DateTime MinValue();
    static DateTime MaxValue();
    static DateTime FromBinary(const long dateData);
    static DateTime FromBinaryRaw(const long dateData);
    static DateTime FromFileTime(const long fileTime);
    static DateTime FromFileTimeUtc(const long fileTime);
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
    DateTime AddTicks(long value);
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
    long ToFileTime();
    long ToFileTimeUtc();
    long ToBinary();
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
    int Day = 0;
    int DayOfYear = 0;
    int Hour = 0;
    int Millisecond = 0;
    int Minute = 0;
    int Month = 0;
    int Second = 0;
    int Year = 0;
    long long Ticks = 0;
private:
    unsigned long _dateData = 0;
    inline long long getInternalTicks() const {
        return (long long) (_dateData & 0x3FFFFFFFFFFFFFFF);
    }
    inline unsigned long long getInternalKind() const {
        return (unsigned long long) (_dateData & -4611686018427387904L);
    }
    long ToBinaryRaw();
    int GetDatePart(int part);
    void GetDatePart(int* year, int* month, int* day);
    inline bool IsAmbiguousDaylightSavingTime() const {
		return getInternalKind() == 13835058055282163712uL;
	}
    DateTime ToLocalTime(bool throwOnOverflow);
    static double TicksToOADate(long value);
    static long DateToTicks(int year, int month, int day);
    static long TimeToTicks(int hour, int minute, int second);
    static long DoubleDateToTicks(double value);
};

struct DateTimeEx : public DateTime
{
    
};


}
}

#endif
