
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
static const slong DoubleDateOffset = 599264352000000000L;
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

private const slong MinValueTimeSpanTicks = -9223372036854775808L;
private const slong MaxValueTimeSpanTicks = 9223372036854775807L;
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
    slong num = ((slong)days * 3600L * 24 + (slong)hours * 3600L + (slong)minutes * 60L + seconds) * 1000 + milliseconds;
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
        throw std::exception("value our of range");
    }
    return TimeSpan(num);
}

TimeSpan TimeSpan::Subtract(const TimeSpan &ts)
{
    slong num = _ticks - ts._ticks;
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

string TimeSpan::ToString() {
    int num = (int)(_ticks / TicksPerDay);
    slong num2 = _ticks % TicksPerDay;
	if (_ticks < 0)
	{
		num = -num;
		num2 = -num2;
	}
	int value2 = (int)(num2 / 36000000000L % 24);
	int value3 = (int)(num2 / 600000000 % 60);
	int value4 = (int)(num2 / 10000000 % 60);
	int num3 = (int)(num2 % 10000000);
	slong num4 = 0L;
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

slong TimeSpan::TimeToTicks(int hour, int minute, int second)
{
    slong num = (slong)hour * 3600L + (slong)minute * 60L + second;
    if (num > 922337203685L || num < -922337203685L)
    {
        throw std::exception("value our of range");
    }
    return num * 10000000;
}

double TimeSpan::TicksToOADate(slong value)
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
    slong num = (value - 599264352000000000L) / 10000;
    if (num < 0)
    {
        slong num2 = num % 86400000;
        if (num2 != 0L)
        {
            num -= (86400000 + num2) * 2;
        }
    }
    return (double)num / 86400000.0;
}

/// DateTime

DateTime::DateTime(slong ticks) {
        if (ticks < 0 || ticks > MaxTicks)
    {
        throw std::exception("ticks out of range");
    }
    _dateData = (ulong)ticks;
}

DateTime::DateTime(ulong dateData) {
    _dateData = dateData;
}

DateTime::DateTime(slong ticks, DateTimeKind kind) {
    _dateData = (ulong)(ticks | (static_cast<slong>(kind) << 62));
}

DateTime::DateTime(int year, int month, int day) {

}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {

}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind) {

}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {

}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind) {

}

DateTime::DateTime(slong ticks, DateTimeKind kind, bool isAmbiguousDst) {

}

DateTime DateTime::Now()
{
    auto utcNow = UtcNow();
    bool isAmbiguousLocalDst = false;
}

DateTime DateTime::UtcNow()
{
    slong fileTime = 0;
#if defined _MSC_VER
    FILETIME t1;
    GetSystemTimeAsFileTime(&t1);
    fileTime = t1.dwHighDateTime << 32 + t1.dwLowDateTime;
    return DateTime((ulong) (fileTime + 504911232000000000L) | 0x4000000000000000); 
#else
    return DateTime();
#endif
}

DateTime DateTime::Today() {

}

DateTime DateTime::MinValue() {
    return DateTime(0L, DateTimeKind::Unspecified);
}

DateTime DateTime::MaxValue() {
    return DateTime(MaxTicks, DateTimeKind::Unspecified);
}

DateTime DateTime::FromBinary(const slong dateData) {

}

DateTime DateTime::FromBinaryRaw(const slong dateData) {

}

DateTime FromFileTime(const slong fileTime) {

}

DateTime DateTime::FromFileTimeUtc(const slong fileTime) {

}

DateTime DateTime::FromOADate(const double d) {

}

DateTime DateTime::Parse(const string& s) {

}

DateTime DateTime::SpecifyKind(const DateTime& value, const DateTimeKind& kind) {

}

int DateTime::Compare(const DateTime& t1, const  DateTime& t2) {

}

int DateTime::DaysInMonth(const int year, const int month) {

}

bool DateTime::IsLeapYear(const int year) {

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
    case 4611686018427387904uL:
        return DateTimeKind::Utc;
    default:
        return DateTimeKind::Local;
    }
}

TimeSpan DateTime::GetTimeOfDay() {

}

DateTime DateTime::Date() {

}

DateTime DateTime::Add(const TimeSpan& value) {

}

DateTime DateTime::Add(double value, int scale) {

}

DateTime DateTime::AddDays(double value) {

}

DateTime DateTime::AddHours(double value) {

}

DateTime DateTime::AddMilliseconds(double value) {

}

DateTime DateTime::AddMinutes(double value) {

}

DateTime DateTime::AddMonths(int months) {

}

DateTime DateTime::AddSeconds(double value) {

}

DateTime DateTime::AddTicks(slong value) {

}

DateTime DateTime::AddYears(int value) {

}

TimeSpan DateTime::Subtract(const DateTime& value) {

}

DateTime DateTime::Subtract(const TimeSpan& value) {

}

DateTime DateTime::ToLocalTime() {

}

DateTime DateTime::ToUniversalTime() {

}

string DateTime::ToString() {

}

string DateTime::ToLongDateString() {

}

string DateTime::ToLongTimeString() {

}

string DateTime::ToShortDateString() {

}

string DateTime::ToShortTimeString() {

}

double DateTime::ToOADate() {

}

slong DateTime::ToFileTime() {

}

slong DateTime::ToFileTimeUtc() {

}

slong DateTime::ToBinary() {

}

int DateTime::CompareTo(const DateTime& value) {

}

bool DateTime::Equals(const DateTime value) {

}

DateTime DateTime::operator +(const TimeSpan& t) {

}

DateTime DateTime::operator -(const TimeSpan& t) {

}

DateTime DateTime::operator -(const DateTime& d) {

}

bool DateTime::operator ==(const DateTime& d) {

}

bool DateTime::operator !=(const DateTime& d) {

}

bool DateTime::operator <(const DateTime& d) {

}

bool DateTime::operator <=(const DateTime& d) {

}

bool DateTime::operator >(const DateTime& d) {

}

bool DateTime::operator >=(const DateTime& d) {

}

slong DateTime::ToBinaryRaw() {

}

int DateTime::GetDatePart(int part) {

}

void DateTime::GetDatePart(int* year, int* month, int* day) {

}

DateTime DateTime::ToLocalTime(bool throwOnOverflow) {

}

double DateTime::TicksToOADate(slong value) {

}

slong DateTime::DateToTicks(int year, int month, int day) {

}

slong DateTime::TimeToTicks(int hour, int minute, int second) {

}

slong DateTime::DoubleDateToTicks(double value) {

}

} // namespace time
} // namespace arklight
