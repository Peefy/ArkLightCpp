
#include "datetime.h"

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

private const ulong TicksMask = 4611686018427387903uL;
private const ulong FlagsMask = 13835058055282163712uL;
private const ulong LocalMask = 9223372036854775808uL;
private const long long TicksCeiling = 4611686018427387904L;
private const ulong KindUnspecified = 0uL;
private const ulong KindUtc = 4611686018427387904uL;
private const ulong KindLocal = 9223372036854775808uL;
private const ulong KindLocalAmbiguousDst = 13835058055282163712uL;
private const int KindShift = 62;
private const string TicksField = "ticks";
private const string DateDataField = "dateData";

private readonly int DaysToMonth365[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
private readonly int DaysToMonth366[13] = {0,31,60,91,121,152,182,213,244,274,305,335,366};
private readonly string DateTimeFormat[] = {"%a", "%A", "%b", "%B", "%c", "%d", "%H", "%I", "%j", "%m", "%M", "%p", "%S", "%U", "%W", "%w", "%x", "%X", "%y", "%Y", "%Z"};

/// TimeSpan

TimeSpan::TimeSpan(long ticks) {

}

TimeSpan::TimeSpan(int hours, int minutes, int seconds) {

}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds) {

}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds) {

}

/// DateTime

DateTime DateTime::UtcNow() {
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

DateTime::DateTime(long ticks) {
    if (ticks < 0 || ticks > 3155378975999999999L) {
		throw std::exception("ticks out of range");
	}
    _dateData = (unsigned long long) ticks;
}

DateTime::DateTime(unsigned long long dateData) {
    _dateData = dateData;
}

DateTime::DateTime(long ticks, DateTimeKind kind) {
    _dateData = (unsigned long long)(ticks | (static_cast<long>(kind) << 62));
}

DayOfWeek DateTime::GetDayOfWeek() {
    return static_cast<DayOfWeek>((getInternalTicks() / 864000000000L + 1) % 7);
}

DateTime DateTime::Now(){
    auto utcNow = UtcNow();
    bool isAmbiguousLocalDst = false;
}

DateTime DateTime::MinValue() {
    return DateTime();
}

DateTime DateTime::MaxValue() {
    return DateTime();
}

DateTime DateTime::Date() {

}

DateTimeKind DateTime::GetDateTimeKind() {
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

} // namespace time
} // namespace arklight
