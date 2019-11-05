
#include "datetime.h"

#include <sstream>

namespace arklight
{
namespace time
{

#define readonly const
#define private static
#define internal static
#define public

typedef unsigned long long ulong;

static const double MillisecondsPerTick = 0.0001;
static const double SecondsPerTick = 1E-07;
static const double MinutesPerTick = 1.6666666666666667E-09;
static const double HoursPerTick = 2.7777777777777777E-11;
static const double DaysPerTick = 1.1574074074074074E-12;
static const long MaxSeconds = 922337203685L;
static const long MinSeconds = -922337203685L;
static const long MaxMilliSeconds = 922337203685477L;
static const long MinMilliSeconds = -922337203685477L;
static const long TicksPerTenthSecond = 1000000L;
static const long TicksPerMillisecond = 10000L;
static const long TicksPerSecond = 10000000L;
static const long TicksPerMinute = 600000000L;
static const long TicksPerHour = 36000000000L;
static const long TicksPerDay = 864000000000L;
static const int MillisPerSecond = 1000;
static const int MillisPerMinute = 60000;
static const int MillisPerHour = 3600000;
static const int MillisPerDay = 86400000;
static const int DaysPerYear = 365;
static const int DaysPer4Years = 1461;
static const int DaysPer100Years = 36524;
static const int DaysPer400Years = 146097;
static const int DaysTo1601 = 584388;
static const int DaysTo1899 = 693593;
static const int DaysTo1970 = 719162;
static const int DaysTo10000 = 3652059;
static const long MinTicks = 0L;
static const long MaxTicks = 3155378975999999999L;
static const long MaxMillis = 315537897600000L;
static const long FileTimeOffset = 504911232000000000L;
static const long DoubleDateOffset = 599264352000000000L;
static const long OADateMinAsTicks = 31241376000000000L;
static const double OADateMinAsDouble = -657435.0;
static const double OADateMaxAsDouble = 2958466.0;
static const int DatePartYear = 0;
static const int DatePartDayOfYear = 1;
static const int DatePartMonth = 2;
static const int DatePartDay = 3;

private
const ulong TicksMask = 4611686018427387903uL;
private
const ulong FlagsMask = 13835058055282163712uL;
private
const ulong LocalMask = 9223372036854775808uL;
private
const long long TicksCeiling = 4611686018427387904L;
private
const ulong KindUnspecified = 0uL;
private
const ulong KindUtc = 4611686018427387904uL;
private
const ulong KindLocal = 9223372036854775808uL;
private
const ulong KindLocalAmbiguousDst = 13835058055282163712uL;
private
const int KindShift = 62;
private
const string TicksField = "ticks";
private
const string DateDataField = "dateData";

private
readonly int DaysToMonth365[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
private
readonly int DaysToMonth366[13] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
private
readonly string DateTimeFormat[] = {"%a", "%A", "%b", "%B", "%c", "%d", "%H", "%I", "%j", "%m", "%M", "%p", "%S", "%U", "%W", "%w", "%x", "%X", "%y", "%Y", "%Z"};

private const long MinValueTimeSpanTicks = -9223372036854775808L;
private const long MaxValueTimeSpanTicks = 9223372036854775807L;
/// TimeSpan

TimeSpan::TimeSpan(long ticks)
{
    _ticks = ticks;
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
{
    _ticks = TimeToTicks(hours, minutes, seconds);
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds)
{
    TimeSpan(days, hours, minutes, seconds, 0);
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
{
    long num = ((long)days * 3600L * 24 + (long)hours * 3600L + (long)minutes * 60L + seconds) * 1000 + milliseconds;
    if (num > 922337203685477L || num < -922337203685477L)
    {
        throw std::exception("value our of range");
    }
    _ticks = num * 10000;
}

TimeSpan TimeSpan::Zero()
{
    return TimeSpan(0);
}

TimeSpan TimeSpan::MinValue()
{
    return TimeSpan(MaxValueTimeSpanTicks);
}

TimeSpan TimeSpan::MaxValue()
{
    return TimeSpan(MinValueTimeSpanTicks);
}

TimeSpan TimeSpan::FromDays(const double value)
{
    return Interval(value, 86400000);
}

TimeSpan TimeSpan::FromHours(const double value)
{
    return Interval(value, 3600000);
}

TimeSpan TimeSpan::FromMilliseconds(const double value)
{
    return Interval(value, 1);
}

TimeSpan TimeSpan::FromMinutes(const double value)
{
    return Interval(value, 60000);
}

TimeSpan TimeSpan::FromSeconds(const double value)
{
    return Interval(value, 1000);
}

TimeSpan TimeSpan::FromTicks(const long value)
{
    return TimeSpan(value);
}

int TimeSpan::Compare(const TimeSpan &t1, const TimeSpan &t2)
{
    if (t1._ticks > t2._ticks)
    {
        return 1;
    }
    if (t1._ticks < t2._ticks)
    {
        return -1;
    }
    return 0;
}

TimeSpan TimeSpan::Add(const TimeSpan &ts)
{
    long num = _ticks + ts._ticks;
    if (_ticks >> 63 == ts._ticks >> 63 && _ticks >> 63 != num >> 63)
    {
        throw std::exception("value our of range");
    }
    return TimeSpan(num);
}

TimeSpan TimeSpan::Subtract(const TimeSpan &ts)
{
    long num = _ticks - ts._ticks;
	if (_ticks >> 63 != ts._ticks >> 63 && _ticks >> 63 != num >> 63)
	{
		throw std::exception("over flow");
	}
	return TimeSpan(num);
}

bool TimeSpan::Equals(const TimeSpan &ts)
{
    return _ticks == ts._ticks;
}

int TimeSpan::CompareTo(const TimeSpan &value)
{
    long ticks = value._ticks;
	if (_ticks > ticks)
	{
		return 1;
	}
	if (_ticks < ticks)
	{
	    return -1;
	}
	return 0;
}

TimeSpan TimeSpan::Duration()
{
    judgeTicksIsMin();
    return TimeSpan((_ticks >= 0) ? _ticks : (-_ticks));
}

TimeSpan TimeSpan::Negate()
{
    judgeTicksIsMin();
    return TimeSpan(-_ticks);
}

string TimeSpan::ToString() {
    int num = (int)(_ticks / TicksPerDay);
    long num2 = _ticks % TicksPerDay;
	if (_ticks < 0)
	{
		num = -num;
		num2 = -num2;
	}
	int value2 = (int)(num2 / 36000000000L % 24);
	int value3 = (int)(num2 / 600000000 % 60);
	int value4 = (int)(num2 / 10000000 % 60);
	int num3 = (int)(num2 % 10000000);
	long num4 = 0L;
	int i = 0;
    std::stringstream ss;
    ss << Hours() << " " << Minutes() << " " << Seconds();
    return ss.str();
}

string TimeSpan::ToString(string &format)
{
    return ToString();
}

TimeSpan TimeSpan::operator-(const TimeSpan &t)
{
    judgeTicksIsMin();
    return this->Subtract(t);
}

TimeSpan TimeSpan::operator+(const TimeSpan &t)
{
    return this->Add(t);
}

bool TimeSpan::operator==(const TimeSpan &t)
{
    return _ticks == t._ticks;
}

bool TimeSpan::operator!=(const TimeSpan &t)
{
    return _ticks != t._ticks;
}

bool TimeSpan::operator<(const TimeSpan &t)
{
    return _ticks < t._ticks;
}

bool TimeSpan::operator<=(const TimeSpan &t)
{
    return _ticks <= t._ticks;
}

bool TimeSpan::operator>(const TimeSpan &t)
{
    return _ticks > t._ticks;
}

bool TimeSpan::operator>=(const TimeSpan &t)
{
    return _ticks >= t._ticks;
}

TimeSpan TimeSpan::Interval(double value, int scale)
{
    if (isnan(value)) {
        throw std::exception("value is NaN");
    }
	double num = value * (double)scale;
	double num2 = num + ((value >= 0.0) ? 0.5 : (-0.5));
	if (num2 > 922337203685477.0 || num2 < -922337203685477.0)
	{
		throw std::exception("value is NaN");
	}
	return TimeSpan((long)num2 * 10000);
}

long TimeSpan::TimeToTicks(int hour, int minute, int second)
{
    long num = (long)hour * 3600L + (long)minute * 60L + second;
    if (num > 922337203685L || num < -922337203685L)
    {
        throw std::exception("value our of range");
    }
    return num * 10000000;
}

double TimeSpan::TicksToOADate(long value)
{
    if (value == 0L)
    {
        return 0.0;
    }
    if (value < TicksPerDay)
    {
        value += 599264352000000000L;
    }
    if (value < 31241376000000000L)
    {
        throw std::exception("value of out range");
    }
    long num = (value - 599264352000000000L) / 10000;
    if (num < 0)
    {
        long num2 = num % 86400000;
        if (num2 != 0L)
        {
            num -= (86400000 + num2) * 2;
        }
    }
    return (double)num / 86400000.0;
}

/// DateTime

DateTime DateTime::UtcNow()
{
    long long fileTime = 0;
#if defined _MSC_VER
    FILETIME t1;
    GetSystemTimeAsFileTime(&t1);
    fileTime = t1.dwHighDateTime << 32 + t1.dwLowDateTime;
    return DateTime((unsigned long long) (fileTime + 504911232000000000L) | 0x4000000000000000) )
#else
    return DateTime();
#endif
}

DateTime::DateTime(long ticks)
{
    if (ticks < 0 || ticks > 3155378975999999999L)
    {
        throw std::exception("ticks out of range");
    }
    _dateData = (unsigned long long)ticks;
}

DateTime::DateTime(unsigned long long dateData)
{
    _dateData = dateData;
}

DateTime::DateTime(long ticks, DateTimeKind kind)
{
    _dateData = (unsigned long long)(ticks | (static_cast<long>(kind) << 62));
}

DayOfWeek DateTime::GetDayOfWeek()
{
    return static_cast<DayOfWeek>((getInternalTicks() / TicksPerDay + 1) % 7);
}

DateTime DateTime::Now()
{
    auto utcNow = UtcNow();
    bool isAmbiguousLocalDst = false;
}

DateTime DateTime::MinValue()
{
    return DateTime();
}

DateTime DateTime::MaxValue()
{
    return DateTime();
}

DateTime DateTime::Date()
{
}

DateTimeKind DateTime::GetDateTimeKind()
{
    auto internalKind = getInternalKind();
    switch (internalKind)
    {
    case 0uL:
        return DateTimeKind::Unspecified;
    case 4611686018427387904uL:
        return DateTimeKind::Utc;
    default:
        return DateTimeKind::Local;
    }
}

TimeSpan DateTime::GetTimeOfDay()
{
}

} // namespace time
} // namespace arklight
