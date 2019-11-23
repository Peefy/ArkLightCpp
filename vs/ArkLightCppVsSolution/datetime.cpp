
#include "datetime.h"

#include <sstream>

namespace arklight
{
namespace time
{

#define readonly const
#define final const
#define private static
#define internal static
#define public

#ifndef boolean
#define boolean bool
#endif

#define True true
#define Flase false

static const double MillisecondsPerTick = 0.0001;
static const double SecondsPerTick = 1E-07;
static const double MinutesPerTick = 1.6666666666666667E-09;
static const double HoursPerTick = 2.7777777777777777E-11;
static const double DaysPerTick = 1.1574074074074074E-12;
static const slong MaxSeconds = 922337203685L;
static const slong MinSeconds = -922337203685L;
static const slong MaxMilliSeconds = 922337203685477L;
static const slong MinMilliSeconds = -922337203685477L;
static const slong TicksPerTenthSecond = 1000000L;
static const slong TicksPerMillisecond = 10000L;
static const slong TicksPerSecond = 10000000L;
static const slong TicksPerMinute = 600000000L;
static const slong TicksPerHour = 36000000000L;
static const slong TicksPerDay = 864000000000L;
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
static const slong MinTicks = 0L;
static const slong MaxTicks = 3155378975999999999L;
static const slong MaxMillis = 315537897600000L;
static const slong FileTimeOffset = 504911232000000000L;
static const slong OADateMinAsTicks = 31241376000000000L;
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
const slong TicksCeiling = 4611686018427387904L;
private
const ulong KindUnspecified = 0uL;
private
const ulong KindUtc = 4611686018427387904uL;
private
const ulong KindLocal = 9223372036854775808uL;
private
const ulong KindLocalAmbiguousDst = 13835058055282163712uL;
private
const slong MinValueTimeSpanTicks = -9223372036854775807L;
private
const slong MaxValueTimeSpanTicks = 9223372036854775807L;
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

char AllStandardFormats[] = {'d', 'D', 'f', 'F', 'g', 'G', 'm', 'M', 'o', 'O', 'r', 'R', 's', 't', 'T', 'u', 'U', 'y', 'Y'};

/// TimeSpan

TimeSpan::TimeSpan(slong ticks)
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
    slong num = ((slong)days * 3600L * 24 + (slong)hours * 3600L + (slong)minutes * 60L + seconds) * MillisPerSecond + milliseconds;
    if (num > MaxMilliSeconds || num < MinMilliSeconds)
    {
        // throw std::exception();
        throw;
    }
    _ticks = num * TicksPerMillisecond;
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
    return Interval(value, MillisPerDay);
}

TimeSpan TimeSpan::FromHours(const double value)
{
    return Interval(value, MillisPerHour);
}

TimeSpan TimeSpan::FromMilliseconds(const double value)
{
    return Interval(value, 1);
}

TimeSpan TimeSpan::FromMinutes(const double value)
{
    return Interval(value, MillisPerMinute);
}

TimeSpan TimeSpan::FromSeconds(const double value)
{
    return Interval(value, MillisPerSecond);
}

TimeSpan TimeSpan::FromTicks(const slong value)
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
    slong num = _ticks + ts._ticks;
    if (_ticks >> 63 == ts._ticks >> 63 && _ticks >> 63 != num >> 63)
    {
        throw std::exception();
    }
    return TimeSpan(num);
}

TimeSpan TimeSpan::Subtract(const TimeSpan &ts)
{
    slong num = _ticks - ts._ticks;
    if (_ticks >> 63 != ts._ticks >> 63 && _ticks >> 63 != num >> 63)
    {
        throw std::exception();
    }
    return TimeSpan(num);
}

bool TimeSpan::Equals(const TimeSpan &ts)
{
    return _ticks == ts._ticks;
}

int TimeSpan::CompareTo(const TimeSpan &value)
{
    slong ticks = value._ticks;
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

string TimeSpan::ToString()
{
    int num = (int)(_ticks / TicksPerDay);
    slong num2 = _ticks % TicksPerDay;
    if (_ticks < 0)
    {
        num = -num;
        num2 = -num2;
    }
    int value2 = (int)(num2 / TicksPerHour % 24);
    int value3 = (int)(num2 / TicksPerMinute % 60);
    int value4 = (int)(num2 / TicksPerSecond % 60);
    int num3 = (int)(num2 % TicksPerSecond);
    slong num4 = 0L;
    int i = 0;
    std::stringstream ss;
    ss << Hours() << " " << Minutes() << " " << Seconds();
    return ss.str();
}

void TimeSpan::judgeTicksIsMin()
{
    if (_ticks == MinValueTimeSpanTicks)
    {
        throw std::exception();
    }
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

slong TimeSpan::Ticks() const
{
    return _ticks;
}

int TimeSpan::Days() const
{
    return (int)(_ticks / TicksPerDay);
}

int TimeSpan::Hours() const
{
    return (int)(_ticks / TicksPerHour % 24);
}

int TimeSpan::Milliseconds() const
{
    return (int)(_ticks / TicksPerMillisecond % 1000);
}

int TimeSpan::Minutes() const
{
    return (int)(_ticks / TicksPerMinute % 60);
}

int TimeSpan::Seconds() const
{
    return (int)(_ticks / TicksPerSecond % 60);
}

double TimeSpan::TotalDays() const
{
    return (double)_ticks * DaysPerTick;
}

double TimeSpan::TotalHours() const
{
    return (double)_ticks * HoursPerTick;
}

double TimeSpan::TotalMilliseconds() const
{
    double num = (double)_ticks * 0.0001;
    if (num > (double)MaxMilliSeconds)
    {
        return (double)MaxMilliSeconds;
    }
    if (num < (double)MinMilliSeconds)
    {
        return (double)MinMilliSeconds;
    }
    return num;
}

double TimeSpan::TotalMinutes() const
{
    return (double)_ticks * MinutesPerTick;
}

double TimeSpan::TotalSeconds() const
{
    return (double)_ticks * SecondsPerTick;
}

TimeSpan TimeSpan::Interval(double value, int scale)
{
    if ((slong)value == 0xFFFFFFFFFFFFFFFF)
    {
        // throw std::exception("value is NaN");
        throw;
    }
    double num = value * (double)scale;
    double num2 = num + ((value >= 0.0) ? 0.5 : (-0.5));
    if (num2 > (double)MaxMilliSeconds || num2 < (double)MinMilliSeconds)
    {
        // throw std::exception("value is NaN");
        throw;
    }
    return TimeSpan((slong)num2 * 10000);
}

slong TimeSpan::TimeToTicks(int hour, int minute, int second)
{
    slong num = (slong)hour * 3600L + (slong)minute * 60L + second;
    if (num > MaxSeconds || num < MinSeconds)
    {
        // throw std::exception("value our of range");
        throw;
    }
    return num * TicksPerSecond;
}

double TimeSpan::TicksToOADate(slong value)
{
    if (value == 0L)
    {
        return 0.0;
    }
    if (value < TicksPerDay)
    {
        value += MaxSeconds;
    }
    if (value < OADateMinAsTicks)
    {
        // throw std::exception("value of out range");
        throw;
    }
    slong num = (value - MaxSeconds) / 10000;
    if (num < 0)
    {
        slong num2 = num % MillisPerDay;
        if (num2 != 0L)
        {
            num -= (MillisPerDay + num2) * 2;
        }
    }
    return (double)num / (double)MillisPerDay;
}

/// DateTime

DateTime::DateTime(slong ticks)
{
    judgeTicks(ticks);
    _dateData = (ulong)ticks;
}

DateTime::DateTime(ulong dateData)
{
    _dateData = dateData;
}

DateTime::DateTime(slong ticks, DateTimeKind kind)
{
    judgeTicks(ticks);
    _dateData = (ulong)(ticks | (static_cast<slong>(kind) << 62));
}

DateTime::DateTime(int year, int month, int day)
{
    _dateData = (ulong)DateToTicks(year, month, day);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
    _dateData = (ulong)(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second));
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind)
{
    judgeDateTimeKind(kind);
    slong num = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    _dateData = (ulong)(num | ((slong)kind << 62));
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
    judgeMillisecond(millisecond);
    _dateData = (ulong)judgeNumTicks(year, month, day, hour, minute, second, millisecond);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind)
{
    judgeAllParas(year, month, day, hour, minute, second, millisecond, kind);
    _dateData = (ulong)(judgeNumTicks(year, month, day, hour, minute, second, millisecond) | ((slong)kind << 62));
}

DateTime::DateTime(slong ticks, DateTimeKind kind, bool isAmbiguousDst)
{
    judgeTicks(ticks);
    _dateData = (ulong)(ticks | (isAmbiguousDst ? (-TicksCeiling) : (MinValueTimeSpanTicks)));
}

DateTime DateTime::Now()
{
    auto utcNow = UtcNow();
    bool isAmbiguousLocalDst = false;
    slong num = utcNow.Ticks();
    if (num > MaxTicks)
    {
        return DateTime(MaxTicks, DateTimeKind::Local);
    }
    if (num < 0)
    {
        return DateTime(0L, DateTimeKind::Local);
    }
    return DateTime(num, DateTimeKind::Local, isAmbiguousLocalDst);
}

DateTime DateTime::UtcNow()
{
#if defined _MSC_VER
    slong fileTime = 0;
    FILETIME t1;
    GetSystemTimeAsFileTime(&t1);
    fileTime = t1.dwHighDateTime << 32 + t1.dwLowDateTime;
    return DateTime((ulong)(fileTime + FileTimeOffset) | 0x4000000000000000);
#else
    return DateTime();
#endif
}

DateTime DateTime::Today()
{
    return Now().Date();
}

DateTime DateTime::MinValue()
{
    return DateTime(0L, DateTimeKind::Unspecified);
}

DateTime DateTime::MaxValue()
{
    return DateTime(MaxTicks, DateTimeKind::Unspecified);
}

DateTime DateTime::FromBinary(const slong dateData)
{
    if ((dateData & MinValueTimeSpanTicks) != 0L)
    {
        slong num = dateData & 0x3FFFFFFFFFFFFFFF;
        if (num > 4611685154427387904L)
        {
            num -= 4611686018427387904L;
        }
        bool isAmbiguousLocalDst = false;
        slong ticks = 0;
        if (num < 0)
        {
            //ticks = TimeZoneInfo.GetLocalUtcOffset(MinValue, TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        }
        else if (num > MaxTicks)
        {
            // ticks = TimeZoneInfo.GetLocalUtcOffset(MaxValue, TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        }
        else
        {
            DateTime time = DateTime(num, DateTimeKind::Utc);
            bool isDaylightSavings = false;
            // ticks = TimeZoneInfo.GetUtcOffsetFromUtc(time, TimeZoneInfo.Local, out isDaylightSavings, out isAmbiguousLocalDst).Ticks;
        }
        num += ticks;
        if (num < 0)
        {
            num += TicksPerDay;
        }
        if (num < 0 || num > MaxTicks)
        {
            // throw std::exception("Argument_DateTimeBadBinaryData");
            throw;
        }
        return DateTime(num, DateTimeKind::Local, isAmbiguousLocalDst);
    }
    return FromBinaryRaw(dateData);
}

DateTime DateTime::FromBinaryRaw(const slong dateData)
{
    return DateTime((ulong)dateData);
}

DateTime DateTime::FromFileTime(const slong fileTime)
{
    return FromFileTimeUtc(fileTime).ToLocalTime();
}

DateTime DateTime::FromFileTimeUtc(const slong fileTime)
{
    if (fileTime < 0 || fileTime > 2650467743999999999L)
    {
        // throw std::exception("invalid fileTime");
        throw;
    }
    slong ticks = fileTime + FileTimeOffset;
    return DateTime(ticks, DateTimeKind::Utc);
}

DateTime DateTime::FromOADate(const double d)
{
    return DateTime(DoubleDateToTicks(d), DateTimeKind::Unspecified);
}

// Unrealized
DateTime DateTime::Parse(const string &s)
{
    return DateTime::Now();
}

DateTime DateTime::SpecifyKind(const DateTime &value, const DateTimeKind &kind)
{
    return DateTime(value.getInternalTicks(), kind);
}

int DateTime::Compare(const DateTime &t1, const DateTime &t2)
{
    slong internalTicks = t1.getInternalTicks();
    slong internalTicks2 = t2.getInternalTicks();
    if (internalTicks2 > internalTicks)
    {
        return 1;
    }
    if (internalTicks2 < internalTicks)
    {
        return -1;
    }
    return 0;
}

int DateTime::DaysInMonth(const int year, const int month)
{
    if (month < 1 || month > 12)
    {
        // throw std::exception("invalid month");
        throw;
    }
    auto isleapyear = IsLeapYear(year);
    if (isleapyear == true)
    {
        return DaysToMonth366[month] - DaysToMonth366[month];
    }
    else
    {
        return DaysToMonth365[month] - DaysToMonth365[month];
    }
}

bool DateTime::IsLeapYear(const int year)
{
    if (year < 1 || year > 9999)
    {
        // throw std::exception("invalid year");
        throw;
    }
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            return year % 400 == 0;
        }
        return true;
    }
    return false;
}

DayOfWeek DateTime::GetDayOfWeek()
{
    return static_cast<DayOfWeek>((getInternalTicks() / TicksPerDay + 1) % 7);
}

DateTimeKind DateTime::GetDateTimeKind()
{
    auto internalKind = getInternalKind();
    switch (internalKind)
    {
    case 0uL:
        return DateTimeKind::Unspecified;
    case KindUtc:
        return DateTimeKind::Utc;
    default:
        return DateTimeKind::Local;
    }
}

TimeSpan DateTime::GetTimeOfDay()
{
    return TimeSpan(0);
}

DateTime DateTime::Date()
{
    slong internalTicks = getInternalTicks();
    return DateTime((ulong)((internalTicks - internalTicks % TicksPerDay) | (long)getInternalKind()));
}

DateTime DateTime::Add(const TimeSpan &value)
{
    return AddTicks(value.Ticks());
}

DateTime DateTime::Add(double value, int scale)
{
    slong num = (slong)(value * (double)scale + ((value >= 0.0) ? 0.5 : (-0.5)));
    if (num <= -MaxMillis || num >= MaxMillis)
    {
        // throw std::exception("invalid value");
        throw;
    }
    return AddTicks(num * 10000);
}

DateTime DateTime::AddDays(double value)
{
    return Add(value, MillisPerDay);
}

DateTime DateTime::AddHours(double value)
{
    return Add(value, MillisPerHour);
}

DateTime DateTime::AddMilliseconds(double value)
{
    return Add(value, 1);
}

DateTime DateTime::AddMinutes(double value)
{
    return Add(value, MillisPerMinute);
}

DateTime DateTime::AddMonths(int months)
{
    int year = 0, month = 0, day = 0;
    if (months < -120000 || months > 120000)
    {
        // throw std::exception("invalid months");
        throw;
    }
    GetDatePart(&year, &month, &day);
    int num = month - 1 + months;
    if (num >= 0)
    {
        month = num % 12 + 1;
        year += num / 12;
    }
    else
    {
        month = 12 + (num + 1) % 12;
        year += (num - 11) / 12;
    }
    if (year < 1 || year > 9999)
    {
        // throw std::exception("invalid year");
        throw;
    }
    int num2 = DaysInMonth(year, month);
    if (day > num2)
    {
        day = num2;
    }
    return DateTime((ulong)((DateToTicks(year, month, day) + getInternalTicks() % TicksPerDay) | (long)getInternalKind()));
}

DateTime DateTime::AddSeconds(double value)
{
    return Add(value, MillisPerSecond);
}

DateTime DateTime::AddTicks(slong value)
{
    slong internalTicks = getInternalTicks();
    if (value > MaxTicks - internalTicks || value < -internalTicks)
    {
        // throw std::exception("invalid value");
        throw;
    }
    return DateTime((ulong)((internalTicks + value) | (slong)getInternalKind()));
}

DateTime DateTime::AddYears(int value)
{
    if (value < -10000 || value > 10000)
    {
        // throw std::exception("invalid yaer");
        throw;
    }
    return AddMonths(value * 12);
}

TimeSpan DateTime::Subtract(const DateTime &value)
{
    return TimeSpan(getInternalTicks() - value.getInternalTicks());
}

DateTime DateTime::Subtract(const TimeSpan &value)
{
    slong internalTicks = getInternalTicks();
    slong ticks = value.Ticks();
    if (internalTicks - 0 < ticks || internalTicks - MaxTicks > ticks)
    {
        // throw std::exception("invalid value");
        throw;
    }
    return DateTime((ulong)((internalTicks - ticks) | (slong)getInternalTicks()));
}

DateTime DateTime::ToLocalTime()
{
    return ToLocalTime(false);
}

DateTime DateTime::ToLocalTime(bool throwOnOverflow)
{
    if (GetDateTimeKind() == DateTimeKind::Local)
    {
        return *this;
    }
    bool isDaylightSavings = false;
    bool isAmbiguousLocalDst = false;
    slong ticks = 0; // TimeZoneInfo::GetUtcOffsetFromUtc(this, TimeZoneInfo::Local, &isDaylightSavings, &isAmbiguousLocalDst).Ticks();
    slong num = getInternalTicks() + ticks;
    if (num > MaxTicks)
    {
        if (throwOnOverflow)
        {
            // throw std::exception("out of range");
            throw;
        }
        return DateTime(MaxTicks, DateTimeKind::Local);
    }
    if (num < 0)
    {
        if (throwOnOverflow)
        {
            // throw std::exception("out of range");
            throw;
        }
        return DateTime(0L, DateTimeKind::Local);
    }
    return DateTime(num, DateTimeKind::Local, isAmbiguousLocalDst);
}

DateTime DateTime::ToUniversalTime()
{
    return *this;
    // return TimeZoneInfo::ConvertTimeToUtc(*this, TimeZoneInfoOptions::NoThrowOnInvalidTime);
}

string DateTime::ToString()
{
    std::stringstream ss;
    ss << Year() << Month() << Day() << Hour() << Minute() << Millisecond();
    return ss.str();
    // return DateTimeFormat::Format(this, nullptr, DateTimeFormatInfo::CurrentInfo);
}

string DateTime::ToLongDateString()
{
    return ToString();
    // return DateTimeFormat::Format(this, "D", DateTimeFormatInfo::CurrentInfo);
}

string DateTime::ToLongTimeString()
{
    return ToString();
    // return DateTimeFormat::Format(this, "T", DateTimeFormatInfo::CurrentInfo);
}

string DateTime::ToShortDateString()
{
    return ToString();
    // return DateTimeFormat::Format(this, "d", DateTimeFormatInfo::CurrentInfo);
}

string DateTime::ToShortTimeString()
{
    return ToString();
    // return DateTimeFormat::Format(this, "t", DateTimeFormatInfo::CurrentInfo);
}

double DateTime::ToOADate()
{
    return TicksToOADate(getInternalTicks());
}

slong DateTime::ToFileTime()
{
    return ToUniversalTime().ToFileTimeUtc();
}

slong DateTime::ToFileTimeUtc()
{
    slong num = (((slong)getInternalKind() & -9223372036854775807L) != 0L) ? ToUniversalTime().getInternalTicks() : getInternalTicks();
    num -= 504911232000000000L;
    if (num < 0)
    {
        throw;
    }
    return num;
}

slong DateTime::ToBinary()
{
    return (slong)_dateData;
}

int DateTime::CompareTo(const DateTime &value)
{
    slong internalTicks = value.getInternalTicks();
    slong internalTicks2 = getInternalTicks();
    if (internalTicks2 > internalTicks)
    {
        return 1;
    }
    if (internalTicks2 < internalTicks)
    {
        return -1;
    }
    return 0;
}

bool DateTime::Equals(const DateTime &value)
{
    return getInternalTicks() == value.getInternalTicks();
}

DateTime DateTime::operator+(const TimeSpan &t)
{
    slong internalTicks = getInternalTicks();
    slong ticks = t.Ticks();
    if (ticks > MaxTicks - internalTicks || ticks < -internalTicks)
    {
        throw;
        // new ArgumentOutOfRangeException("t", Environment.GetResourceString("ArgumentOutOfRange_DateArithmetic"));
    }
    return DateTime((ulong)((internalTicks + ticks) | (slong)getInternalKind()));
}

DateTime DateTime::operator-(const TimeSpan &t)
{
    long internalTicks = getInternalTicks();
    long ticks = t.Ticks();
    if (internalTicks - 0 < ticks || internalTicks - MaxTicks > ticks)
    {
        throw; 
        // new ArgumentOutOfRangeException("t", Environment.GetResourceString("ArgumentOutOfRange_DateArithmetic"));
    }
    return DateTime((ulong)((internalTicks - ticks) | (slong)getInternalKind()));
}

TimeSpan DateTime::operator-(const DateTime &d)
{
    return TimeSpan(getInternalTicks() - d.getInternalTicks());
}

bool DateTime::operator==(const DateTime &d)
{
    return getInternalTicks() == d.getInternalTicks();
}

bool DateTime::operator!=(const DateTime &d)
{
    return getInternalTicks() != d.getInternalTicks();
}

bool DateTime::operator<(const DateTime &d)
{
    return getInternalTicks() < d.getInternalTicks();
}

bool DateTime::operator<=(const DateTime &d)
{
    return getInternalTicks() <= d.getInternalTicks();
}

bool DateTime::operator>(const DateTime &d)
{
    return getInternalTicks() > d.getInternalTicks();
}

bool DateTime::operator>=(const DateTime &d)
{
    return getInternalTicks() >= d.getInternalTicks();
}

int DateTime::Day()
{
    return GetDatePart(3);
}

int DateTime::DayOfYear()
{
    return GetDatePart(1);
}

int DateTime::Hour()
{
    return (int)(getInternalTicks() / TicksPerHour % 24);
}

int DateTime::Millisecond()
{
    return (int)(getInternalTicks() / TicksPerMillisecond % 1000);
}

int DateTime::Minute()
{
    return (int)(getInternalTicks() / TicksPerMinute % 60);
}

int DateTime::Month()
{
    return GetDatePart(2);
}

int DateTime::Second()
{
    return (int)(getInternalTicks() / TicksPerSecond % 60);
}

int DateTime::Year()
{
    return GetDatePart(0);
}

slong DateTime::Ticks()
{
    return getInternalTicks();
}

slong DateTime::ToBinaryRaw()
{
    return (slong)_dateData;
}

int DateTime::GetDatePart(int part)
{
    long internalTicks = getInternalTicks();
    int num = (int)(internalTicks / TicksPerDay);
    int num2 = num / 146097;
    num -= num2 * 146097;
    int num3 = num / 36524;
    if (num3 == 4)
    {
        num3 = 3;
    }
    num -= num3 * 36524;
    int num4 = num / 1461;
    num -= num4 * 1461;
    int num5 = num / 365;
    if (num5 == 4)
    {
        num5 = 3;
    }
    if (part == 0)
    {
        return num2 * 400 + num3 * 100 + num4 * 4 + num5 + 1;
    }
    num -= num5 * 365;
    if (part == 1)
    {
        return num + 1;
    }
    auto array = (num5 == 3 && (num4 != 24 || num3 == 3)) ? DaysToMonth366 : DaysToMonth365;
    int i;
    for (i = num >> 6; num >= array[i]; i++)
    {
    }
    if (part == 2)
    {
        return i;
    }
    return num - array[i - 1] + 1;
}

void DateTime::GetDatePart(int *year, int *month, int *day)
{
    long internalTicks = getInternalTicks();
    int num = (int)(internalTicks / TicksPerDay);
    int num2 = num / 146097;
    num -= num2 * 146097;
    int num3 = num / 36524;
    if (num3 == 4)
    {
        num3 = 3;
    }
    num -= num3 * 36524;
    int num4 = num / 1461;
    num -= num4 * 1461;
    int num5 = num / 365;
    if (num5 == 4)
    {
        num5 = 3;
    }
    *year = num2 * 400 + num3 * 100 + num4 * 4 + num5 + 1;
    num -= num5 * 365;
    auto array = (num5 == 3 && (num4 != 24 || num3 == 3)) ? DaysToMonth366 : DaysToMonth365;
    int i;
    for (i = (num >> 5) + 1; num >= array[i]; i++)
    {
    }
    *month = i;
    *day = num - array[i - 1] + 1;
}

double DateTime::TicksToOADate(slong value)
{
    if (value == 0L)
    {
        return 0.0;
    }
    if (value < TicksPerDay)
    {
        value += 599264352000000000L;
    }
    if (value < OADateMinAsTicks)
    {
        throw; 
        // new OverflowException(Environment.GetResourceString("Arg_OleAutDateInvalid"));
    }
    long num = (value - 599264352000000000L) / 10000;
    if (num < 0)
    {
        long num2 = num % MillisPerDay;
        if (num2 != 0L)
        {
            num -= (MillisPerDay + num2) * 2;
        }
    }
    return (double)num / (double)MillisPerDay;
}

slong DateTime::DateToTicks(int year, int month, int day)
{
    if (year >= 1 && year <= 9999 && month >= 1 && month <= 12)
    {
        auto array = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
        if (day >= 1 && day <= array[month] - array[month - 1])
        {
            int num = year - 1;
            int num2 = num * 365 + num / 4 - num / 100 + num / 400 + array[month - 1] + day - 1;
            return num2 * TicksPerDay;
        }
    }
    throw; 
    // new ArgumentOutOfRangeException(null, Environment.GetResourceString("ArgumentOutOfRange_BadYearMonthDay"));
}

slong DateTime::TimeToTicks(int hour, int minute, int second)
{
    if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60)
	{
		return TimeSpan::TimeToTicks(hour, minute, second);
	}
	throw; 
    // new ArgumentOutOfRangeException(null, Environment.GetResourceString("ArgumentOutOfRange_BadHourMinuteSecond"));
}

slong DateTime::DoubleDateToTicks(double value)
{
    if (!(value < 2958466.0) || !(value > -657435.0))
    {
        throw; 
        // new ArgumentException(Environment.GetResourceString("Arg_OleAutDateInvalid"));
    }
    long num = (long)(value * (double)MillisPerDay + ((value >= 0.0) ? 0.5 : (-0.5)));
    if (num < 0)
    {
        num -= num % MillisPerDay * 2;
    }
    num += 59926435200000L;
    if (num < 0 || num >= 315537897600000L)
    {
        throw; 
        // new ArgumentException(Environment.GetResourceString("Arg_OleAutDateScale"));
    }
    return num * 10000;
}

inline slong DateTime::getInternalTicks() const
{
    return (slong)(_dateData & 0x3FFFFFFFFFFFFFFF);
}

inline ulong DateTime::getInternalKind() const
{
    return (ulong)(_dateData & -4611686018427387904L);
}

inline bool DateTime::IsAmbiguousDaylightSavingTime() const
{
    return getInternalKind() == KindLocalAmbiguousDst;
}

void DateTime::judgeMillisecond(int &millisecond)
{
    if (millisecond < 0 || millisecond >= 1000)
    {
        // throw std::exception("millisecond ArgumentOutOfRange_Range");
        throw;
    }
}
void DateTime::judgeDateTimeKind(DateTimeKind &kind)
{
    if (kind < DateTimeKind::Unspecified || kind > DateTimeKind::Local)
    {
        // throw std::exception("Argument_InvalidDateTimeKind");
        throw;
    }
}
slong DateTime::judgeNumTicks(int &year, int &month, int &day, int &hour, int &minute, int &second, int &millisecond)
{
    slong num = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    num += (slong)millisecond * 10000L;
    if (num < 0 || num > MaxTicks)
    {
        // throw std::exception("Arg_DateTimeRange");
        throw;
    }
    return num;
}
void DateTime::judgeTicks(slong &ticks)
{
    if (ticks < 0 || ticks > MaxTicks)
    {
        // throw std::exception("ArgumentOutOfRange_DateTimeBadTicks");
        throw;
    }
}
void DateTime::judgeAllParas(int &year, int &month, int &day, int &hour, int &minute, int &second, int &millisecond, DateTimeKind &kind)
{
    judgeMillisecond(millisecond);
    judgeDateTimeKind(kind);
    judgeNumTicks(year, month, day, hour, minute, second, millisecond);
}

} // namespace time
} // namespace arklight
