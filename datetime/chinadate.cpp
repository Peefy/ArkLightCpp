
#include "chinadate.h"

namespace arklight
{
namespace datetime
{

static const long long lunarInfo[] = {0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554,
                                      0x056a0, 0x09ad0, 0x055d2, 0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0,
                                      0x14977, 0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970, 0x06566,
                                      0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950, 0x0d4a0, 0x1d8a6, 0x0b550,
                                      0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557, 0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5d0,
                                      0x14573, 0x052d0, 0x0a9a8, 0x0e950, 0x06aa0, 0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263,
                                      0x0d950, 0x05b57, 0x056a0, 0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b5a0,
                                      0x195a6, 0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570, 0x04af5,
                                      0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x055c0, 0x0ab60, 0x096d5, 0x092e0, 0x0c960, 0x0d954, 0x0d4a0,
                                      0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5, 0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9,
                                      0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930, 0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0,
                                      0x0d260, 0x0ea65, 0x0d530, 0x05aa0, 0x076a3, 0x096d0, 0x04bd7, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520,
                                      0x0dd45, 0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0};

static const int year20[] = {1, 4, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1};
static const int year19[] = {0, 3, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0};
static const int year2000[] = {0, 3, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1};
static const String nStr[] = {"", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十", "十一", "十二"};
static const String Gan[] = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
static const String Zhi[] = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};
static const String Animals[] = {"鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"};
static const String solarTerm[] = {"小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪", "冬至"};
static const int sTermInfo[] = {0, 21208, 42467, 63836, 85337, 107014, 128867, 150921, 173149, 195551, 218072, 240693, 263343, 285989, 308563, 331033, 353350, 375494, 397447, 419210, 440795, 462224, 483532, 504758};

static const String lFtv[] = {"0101 农历春节", "0202 龙抬头节", "0115 元宵节", "0505 端午节", "0707 七夕情人节", "0815 中秋节", "0909 重阳节", "1208 腊八节", "1114 李君先生生日", "1224 小年", "0100 除夕"};
static const String sFtv[] = {"0101 新年元旦",
                           "0202 世界湿地日",
                           "0207 国际声援南非日",
                           "0210 国际气象节",
                           "0214 情人节",
                           "0301 国际海豹日",
                           "0303 全国爱耳日",
                           "0308 国际妇女节",
                           "0312 植树节 孙中山逝世纪念日",
                           "0314 国际警察日",
                           "0315 国际消费者权益日",
                           "0317 中国国医节 国际航海日",
                           "0321 世界森林日 消除种族歧视国际日",
                           "0321 世界儿歌日",
                           "0322 世界水日",
                           "0323 世界气象日",
                           "0324 世界防治结核病日",
                           "0325 全国中小学生安全教育日",
                           "0330 巴勒斯坦国土日",
                           "0401 愚人节 全国爱国卫生运动月(四月) 税收宣传月(四月)",
                           "0407 世界卫生日",
                           "0422 世界地球日",
                           "0423 世界图书和版权日",
                           "0424 亚非新闻工作者日",
                           "0501 国际劳动节",
                           "0504 中国五四青年节",
                           "0505 碘缺乏病防治日",
                           "0508 世界红十字日",
                           "0512 国际护士节",
                           "0515 国际家庭日",
                           "0517 世界电信日",
                           "0518 国际博物馆日",
                           "0520 全国学生营养日",
                           "0523 国际牛奶日",
                           "0531 世界无烟日",
                           "0601 国际儿童节",
                           "0605 世界环境日",
                           "0606 全国爱眼日",
                           "0617 防治荒漠化和干旱日",
                           "0623 国际奥林匹克日",
                           "0625 全国土地日",
                           "0626 国际反毒品日",
                           "0701 中国共产党建党日 世界建筑日",
                           "0702 国际体育记者日",
                           "0707 中国人民抗日战争纪念日",
                           "0711 世界人口日",
                           "0730 非洲妇女日",
                           "0801 中国建军节",
                           "0808 中国男子节(爸爸节)",
                           "0815 日本正式宣布无条件投降日",
                           "0908 国际扫盲日 国际新闻工作者日",
                           "0910 教师节",
                           "0914 世界清洁地球日",
                           "0916 国际臭氧层保护日",
                           "0918 九·一八事变纪念日",
                           "0920 全国爱牙日",
                           "0927 世界旅游日",
                           "1001 国庆节 世界音乐日 国际老人节",
                           "1001 国际音乐日",
                           "1002 国际和平与民主自由斗争日",
                           "1004 世界动物日",
                           "1008 全国高血压日",
                           "1008 世界视觉日",
                           "1009 世界邮政日 万国邮联日",
                           "1010 辛亥革命纪念日 世界精神卫生日",
                           "1013 世界保健日 国际教师节",
                           "1014 世界标准日",
                           "1015 国际盲人节(白手杖节)",
                           "1016 世界粮食日",
                           "1017 世界消除贫困日",
                           "1022 世界传统医药日",
                           "1024 联合国日 世界发展信息日",
                           "1031 世界勤俭日",
                           "1107 十月社会主义革命纪念日",
                           "1108 中国记者日",
                           "1109 全国消防安全宣传教育日",
                           "1110 世界青年节",
                           "1111 国际科学与和平周(本日所属的一周)",
                           "1112 孙中山诞辰纪念日",
                           "1114 世界糖尿病日",
                           "1117 国际大学生节 世界学生节",
                           "1121 世界问候日 世界电视日",
                           "1129 国际声援巴勒斯坦人民国际日",
                           "1201 世界艾滋病日",
                           "1203 世界残疾人日",
                           "1205 国际经济和社会发展志愿人员日",
                           "1208 国际儿童电视日",
                           "1209 世界足球日",
                           "1210 世界人权日",
                           "1212 西安事变纪念日",
                           "1213 南京大屠杀(1937年)纪念日！紧记血泪史！",
                           "1221 国际篮球日",
                           "1224 平安夜",
                           "1225 圣诞节",
                           "1226 毛主席诞辰",
                           "1229 国际生物多样性日"};

static int LeapDays(int y);
static inline int LeapMonth(int y);
static int MonthDays(const int y, const int m);
static inline String AnimalsYear(const int y);
static inline String Cyclicalm(const int num);
static inline String Cyclical(const int y);

// 传回农历y年的总天数
static int LYearDays(int y)
{
    int i, sum = 348;
    for (i = 0x8000; i > 0x8; i >>= 1)
    {
        if ((lunarInfo[y - 1900] & i) != 0)
            sum += 1;
    }
    return (sum + LeapDays(y));
}

// 传回农历y年闰月的天数
static int LeapDays(int y)
{
    if (LeapMonth(y) != 0)
    {
        if ((lunarInfo[y - 1900] & 0x10000) != 0)
            return 30;
        else
            return 29;
    }
    else
        return 0;
}

// 传回农历y年闰哪个月 1-12 , 没闰传回 0
static inline int LeapMonth(int y)
{
    return (int)(lunarInfo[y - 1900] & 0xf);
}

// 传回农历y年m月的总天数
static int MonthDays(const int y, const int m)
{
    if ((lunarInfo[y - 1900] & (0x10000 >> m)) == 0)
        return 29;
    else
        return 30;
}

// 传回农历y年的生肖
static inline String AnimalsYear(const int y)
{
    return Animals[(y - 4) % 12];
}

// 传入月日的offset 传回干支,0=甲子
static inline String Cyclicalm(const int num)
{
    return (Gan[num % 10] + Zhi[num % 12]);
}

// 传入offset 传回干支, 0=甲子
static inline String Cyclical(const int y)
{
    int num = y - 1900 + 36;
    return (Cyclicalm(num));
}

// 传出农历.year0 .month1 .day2 .yearCyl3 .monCyl4 .dayCyl5 .isLeap6
void Lunar(const int y, const int m, __OUT__ long long nongDate[7])
{
    int i = 0, temp = 0, leap = 0;
    DateTime baseDate = DateTime(1900 + 1900, 2, 31);
    DateTime objDate = DateTime(y + 1900, m + 1, 1);
    TimeSpan ts = (objDate - baseDate);
    long long offset = (long long)ts.TotalDays();
    if (y < 2000)
        offset += year19[m - 1];
    if (y > 2000)
        offset += year20[m - 1];
    if (y == 2000)
        offset += year2000[m - 1];
    nongDate[5] = offset + 40;
    nongDate[4] = 14;

    for (i = 1900; i < 2050 && offset > 0; i++)
    {
        temp = LYearDays(i);
        offset -= temp;
        nongDate[4] += 12;
    }
    if (offset < 0)
    {
        offset += temp;
        i--;
        nongDate[4] -= 12;
    }
    nongDate[0] = i;
    nongDate[3] = i - 1864;
    leap = LeapMonth(i); // 闰哪个月
    nongDate[6] = 0;

    for (i = 1; i < 13 && offset > 0; i++)
    {
        // 闰月
        if (leap > 0 && i == (leap + 1) && nongDate[6] == 0)
        {
            --i;
            nongDate[6] = 1;
            temp = LeapDays((int)nongDate[0]);
        }
        else
        {
            temp = MonthDays((int)nongDate[0], i);
        }

        // 解除闰月
        if (nongDate[6] == 1 && i == (leap + 1))
            nongDate[6] = 0;
        offset -= temp;
        if (nongDate[6] == 0)
            nongDate[4]++;
    }

    if (offset == 0 && leap > 0 && i == leap + 1)
    {
        if (nongDate[6] == 1)
        {
            nongDate[6] = 0;
        }
        else
        {
            nongDate[6] = 1;
            --i;
            --nongDate[4];
        }
    }
    if (offset < 0)
    {
        offset += temp;
        --i;
        --nongDate[4];
    }
    nongDate[1] = i;
    nongDate[2] = offset + 1;
}

// 传出y年m月d日对应的农历.year0 .month1 .day2 .yearCyl3 .monCyl4 .dayCyl5 .isLeap6
static void CalElement(int y, int m, int d, __OUT__ long long nongDate[7])
{
    int i = 0, temp = 0, leap = 0;

    DateTime baseDate = DateTime(1900, 1, 31);
    DateTime objDate = DateTime(y, m, d);
    TimeSpan ts = objDate - baseDate;

    long long offset = (long long)ts.TotalDays();

    nongDate[5] = offset + 40;
    nongDate[4] = 14;

    for (i = 1900; i < 2050 && offset > 0; i++)
    {
        temp = LYearDays(i);
        offset -= temp;
        nongDate[4] += 12;
    }
    if (offset < 0)
    {
        offset += temp;
        i--;
        nongDate[4] -= 12;
    }
    nongDate[0] = i;
    nongDate[3] = i - 1864;
    leap = LeapMonth(i); // 闰哪个月
    nongDate[6] = 0;

    for (i = 1; i < 13 && offset > 0; i++)
    {
        // 闰月
        if (leap > 0 && i == (leap + 1) && nongDate[6] == 0)
        {
            --i;
            nongDate[6] = 1;
            temp = LeapDays((int)nongDate[0]);
        }
        else
        {
            temp = MonthDays((int)nongDate[0], i);
        }

        // 解除闰月
        if (nongDate[6] == 1 && i == (leap + 1))
            nongDate[6] = 0;
        offset -= temp;
        if (nongDate[6] == 0)
            nongDate[4]++;
    }

    if (offset == 0 && leap > 0 && i == leap + 1)
    {
        if (nongDate[6] == 1)
        {
            nongDate[6] = 0;
        }
        else
        {
            nongDate[6] = 1;
            --i;
            --nongDate[4];
        }
    }
    if (offset < 0)
    {
        offset += temp;
        --i;
        --nongDate[4];
    }
    nongDate[1] = i;
    nongDate[2] = offset + 1;
}

static String GetChinaDate(int day)
{
    String a = "";
    if (day == 10)
        return "初十";
    if (day == 20)
        return "二十";
    if (day == 30)
        return "三十";
    int two = (int)((day) / 10);
    if (two == 0)
        a = "初";
    if (two == 1)
        a = "十";
    if (two == 2)
        a = "廿";
    if (two == 3)
        a = "三";
    int one = (int)(day % 10);
    switch (one)
    {
    case 1:
        a += "一";
        break;
    case 2:
        a += "二";
        break;
    case 3:
        a += "三";
        break;
    case 4:
        a += "四";
        break;
    case 5:
        a += "五";
        break;
    case 6:
        a += "六";
        break;
    case 7:
        a += "七";
        break;
    case 8:
        a += "八";
        break;
    case 9:
        a += "九";
        break;
    }
    return a;
}

static DateTime STerm(int y, int n)
{
    double ms = 31556925974.7 * (y - 1900);
    double ms1 = sTermInfo[n];
    DateTime offDate = DateTime(1900, 1, 6, 2, 5, 0);
    offDate = offDate.AddMilliseconds(ms);
    offDate = offDate.AddMinutes(ms1);
    return offDate;
}

ChinaDateBase::ChinaDateBase() : _tick(0),
                                 _time(0),
                                 _intYear(0),     // 农历年(整型)
                                 _intMonth(0),    // 农历月(整型)
                                 _intDay(0),      // 农历天(整型)
                                 _strYear(""),   // 农历年(字符)
                                 _strMonth(""),  // 农历月(字符)
                                 _strDay(""),    // 农历天(字符)
                                 _anm(""),       // 字符属相
                                 _socalTerm(""), // 二十四节气
                                 _ftvl(""),      //阴历节日
                                 _ftvs("")       //阳历节日
{
}

ChinaDateBase::~ChinaDateBase()
{
}

int ChinaDateBase::GetLongSecond()
{
    return _time;
}

int ChinaDateBase::GetDaysByMonth(int y, int m)
{
    int days[] = {31, DateTime::IsLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[m - 1];
}

DateTime ChinaDateBase::GetMondayDateByDate(DateTime &dt)
{
    double d = 0;
    switch ((int)dt.GetDayOfWeek())
    {
    //case 1: d = 0; break;
    case 2:
        d = -1;
        break;
    case 3:
        d = -2;
        break;
    case 4:
        d = -3;
        break;
    case 5:
        d = -4;
        break;
    case 6:
        d = -5;
        break;
    case 0:
        d = -6;
        break;
    }
    return dt.AddDays(d);
}

ChinaDateBase ChinaDateBase::GetChinaDate(DateTime &dt)
{
    ChinaDateBase cd;
    int year = dt.Year();
    int month = dt.Month();
    int date = dt.Day();
    long long l[7] = {0, 0, 0, 0, 0, 0, 0};
    CalElement(year, month, date, l);
    cd._intYear = (int)l[0];
    cd._intMonth = (int)l[1];
    cd._intDay = (int)l[2];
    cd._strYear = Cyclical(year);
    cd._anm = AnimalsYear(year);
    cd._strMonth = nStr[(int)l[1]];
    // cd._strDay = GetChinaDate((int)(l[2]));

    for (int i = 0; i < 24; i++)
    {
        auto s1 = STerm(dt.Year(), i);
        if (s1.EqualsMonthAndDay(dt) == true)
        {
            cd._socalTerm = solarTerm[i];
            break;
        }
    }

    for (auto &&s : sFtv)
    {
        auto s1 = atoi(s.substr(0, 2).c_str());
        auto s2 = atoi(s.substr(2, 2).c_str());
        if (s1 == dt.Month() && s2 == dt.Day())
        {
            cd._ftvs = s.substr(5);
            break;
        }
    }

    for (auto &&s : lFtv)
    {
        auto s1 = atoi(s.substr(0, 2).c_str());
        auto s2 = atoi(s.substr(2, 2).c_str());
        if (s1 == dt.Month() && s2 == dt.Day())
        {
            cd._ftvl = s.substr(5);
            break;
        }
    }
    dt = dt.AddDays(1);
    year = dt.Year();
    month = dt.Month();
    date = dt.Day();
    CalElement(year, month, date, l);
    if (l[1] == dt.Month() && l[2] == dt.Day())
    {
        cd._ftvl = "除夕";
    }
    return cd;
}

static const int MinYear = 1900;
static const int MaxYear = 2050;
static const int GanZhiStartYear = 1864; //干支计算起始年
static const int AnimalStartYear = 1900; //1900年为鼠年
static const String HZNum = "零一二三四五六七八九";
static auto MinDay = make_shared<DateTime>(1900, 1, 30);
static auto MaxDay = make_shared<DateTime>(2049, 12, 31);
static auto GanZhiStartDay = make_shared<DateTime>(1899, 12, 22);              //起始日
static auto ChineseConstellationReferDay = make_shared<DateTime>(2007, 9, 13); //28星宿参考值,本日为角

// 农历数据，第17位：表示闰月天数，0表示29天   1表示30天; 第16位-第5位（共12位）表示12个月，其中第16位表示第一月，如果该月为30天则为1，29天为0; 第4位-第1位（共4位）表示闰月是哪个月，如果当年没有闰月，则置0
static const long int LunarDateArray[]{
    0x04BD8, 0x04AE0, 0x0A570, 0x054D5, 0x0D260, 0x0D950, 0x16554, 0x056A0, 0x09AD0, 0x055D2,
    0x04AE0, 0x0A5B6, 0x0A4D0, 0x0D250, 0x1D255, 0x0B540, 0x0D6A0, 0x0ADA2, 0x095B0, 0x14977,
    0x04970, 0x0A4B0, 0x0B4B5, 0x06A50, 0x06D40, 0x1AB54, 0x02B60, 0x09570, 0x052F2, 0x04970,
    0x06566, 0x0D4A0, 0x0EA50, 0x06E95, 0x05AD0, 0x02B60, 0x186E3, 0x092E0, 0x1C8D7, 0x0C950,
    0x0D4A0, 0x1D8A6, 0x0B550, 0x056A0, 0x1A5B4, 0x025D0, 0x092D0, 0x0D2B2, 0x0A950, 0x0B557,
    0x06CA0, 0x0B550, 0x15355, 0x04DA0, 0x0A5B0, 0x14573, 0x052B0, 0x0A9A8, 0x0E950, 0x06AA0,
    0x0AEA6, 0x0AB50, 0x04B60, 0x0AAE4, 0x0A570, 0x05260, 0x0F263, 0x0D950, 0x05B57, 0x056A0,
    0x096D0, 0x04DD5, 0x04AD0, 0x0A4D0, 0x0D4D4, 0x0D250, 0x0D558, 0x0B540, 0x0B6A0, 0x195A6,
    0x095B0, 0x049B0, 0x0A974, 0x0A4B0, 0x0B27A, 0x06A50, 0x06D40, 0x0AF46, 0x0AB60, 0x09570,
    0x04AF5, 0x04970, 0x064B0, 0x074A3, 0x0EA50, 0x06B58, 0x055C0, 0x0AB60, 0x096D5, 0x092E0,
    0x0C960, 0x0D954, 0x0D4A0, 0x0DA50, 0x07552, 0x056A0, 0x0ABB7, 0x025D0, 0x092D0, 0x0CAB5,
    0x0A950, 0x0B4A0, 0x0BAA4, 0x0AD50, 0x055D9, 0x04BA0, 0x0A5B0, 0x15176, 0x052B0, 0x0A930,
    0x07954, 0x06AA0, 0x0AD50, 0x05B52, 0x04B60, 0x0A6E6, 0x0A4E0, 0x0D260, 0x0EA65, 0x0D530,
    0x05AA0, 0x076A3, 0x096D0, 0x04BD7, 0x04AD0, 0x0A4D0, 0x1D0B6, 0x0D250, 0x0D520, 0x0DD45,
    0x0B5A0, 0x056D0, 0x055B2, 0x049B0, 0x0A577, 0x0A4B0, 0x0AA50, 0x1B255, 0x06D20, 0x0ADA0,
    0x14B63};

// 星座名称
static const String _constellationName[] =
    {
        "白羊座", "金牛座", "双子座",
        "巨蟹座", "狮子座", "处女座",
        "天秤座", "天蝎座", "射手座",
        "摩羯座", "水瓶座", "双鱼座"};

// 二十四节气
static const String _lunarHolidayName[] =
    {
        "小寒", "大寒", "立春", "雨水",
        "惊蛰", "春分", "清明", "谷雨",
        "立夏", "小满", "芒种", "夏至",
        "小暑", "大暑", "立秋", "处暑",
        "白露", "秋分", "寒露", "霜降",
        "立冬", "小雪", "大雪", "冬至"};

// 二十八星宿
static const String _chineseConstellationName[] =
    {
        //四        五      六         日        一      二      三
        "角木蛟", "亢金龙", "女土蝠", "房日兔", "心月狐", "尾火虎", "箕水豹",
        "斗木獬", "牛金牛", "氐土貉", "虚日鼠", "危月燕", "室火猪", "壁水獝",
        "奎木狼", "娄金狗", "胃土彘", "昴日鸡", "毕月乌", "觜火猴", "参水猿",
        "井木犴", "鬼金羊", "柳土獐", "星日马", "张月鹿", "翼火蛇", "轸水蚓"};

static const String SolarTerm[] = {"小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪", "冬至"};

static const String ganStr = "甲乙丙丁戊己庚辛壬癸";
static const String zhiStr = "子丑寅卯辰巳午未申酉戌亥";
static const String animalStr = "鼠牛虎兔龙蛇马羊猴鸡狗猪";
static const String nStr1 = "日一二三四五六七八九";
static const String nStr2 = "初十廿卅";
static const String _monthString[] =
{
    "出错", "正月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "十一月", "腊月"
};

static const ChineseCalendar::SolarHolidayStruct sHolidayInfo[] = {
    ChineseCalendar::SolarHolidayStruct(1, 1, 1, "元旦"),
    ChineseCalendar::SolarHolidayStruct(2, 2, 0, "世界湿地日"),
    ChineseCalendar::SolarHolidayStruct(2, 10, 0, "国际气象节"),
    ChineseCalendar::SolarHolidayStruct(2, 14, 0, "情人节"),
    ChineseCalendar::SolarHolidayStruct(3, 1, 0, "国际海豹日"),
    ChineseCalendar::SolarHolidayStruct(3, 5, 0, "学雷锋纪念日"),
    ChineseCalendar::SolarHolidayStruct(3, 8, 0, "妇女节"),
    ChineseCalendar::SolarHolidayStruct(3, 12, 0, "植树节 孙中山逝世纪念日"),
    ChineseCalendar::SolarHolidayStruct(3, 14, 0, "国际警察日"),
    ChineseCalendar::SolarHolidayStruct(3, 15, 0, "消费者权益日"),
    ChineseCalendar::SolarHolidayStruct(3, 17, 0, "中国国医节 国际航海日"),
    ChineseCalendar::SolarHolidayStruct(3, 21, 0, "世界森林日 消除种族歧视国际日 世界儿歌日"),
    ChineseCalendar::SolarHolidayStruct(3, 22, 0, "世界水日"),
    ChineseCalendar::SolarHolidayStruct(3, 24, 0, "世界防治结核病日"),
    ChineseCalendar::SolarHolidayStruct(4, 1, 0, "愚人节"),
    ChineseCalendar::SolarHolidayStruct(4, 7, 0, "世界卫生日"),
    ChineseCalendar::SolarHolidayStruct(4, 22, 0, "世界地球日"),
    ChineseCalendar::SolarHolidayStruct(5, 1, 1, "劳动节"),
    ChineseCalendar::SolarHolidayStruct(5, 2, 1, "劳动节假日"),
    ChineseCalendar::SolarHolidayStruct(5, 3, 1, "劳动节假日"),
    ChineseCalendar::SolarHolidayStruct(5, 4, 0, "青年节"),
    ChineseCalendar::SolarHolidayStruct(5, 8, 0, "世界红十字日"),
    ChineseCalendar::SolarHolidayStruct(5, 12, 0, "国际护士节"),
    ChineseCalendar::SolarHolidayStruct(5, 31, 0, "世界无烟日"),
    ChineseCalendar::SolarHolidayStruct(6, 1, 0, "国际儿童节"),
    ChineseCalendar::SolarHolidayStruct(6, 5, 0, "世界环境保护日"),
    ChineseCalendar::SolarHolidayStruct(6, 26, 0, "国际禁毒日"),
    ChineseCalendar::SolarHolidayStruct(7, 1, 0, "建党节 香港回归纪念 世界建筑日"),
    ChineseCalendar::SolarHolidayStruct(7, 11, 0, "世界人口日"),
    ChineseCalendar::SolarHolidayStruct(8, 1, 0, "建军节"),
    ChineseCalendar::SolarHolidayStruct(8, 8, 0, "中国男子节 父亲节"),
    ChineseCalendar::SolarHolidayStruct(8, 15, 0, "抗日战争胜利纪念"),
    ChineseCalendar::SolarHolidayStruct(9, 9, 0, "毛主席逝世纪念"),
    ChineseCalendar::SolarHolidayStruct(9, 10, 0, "教师节"),
    ChineseCalendar::SolarHolidayStruct(9, 18, 0, "九·一八事变纪念日"),
    ChineseCalendar::SolarHolidayStruct(9, 20, 0, "国际爱牙日"),
    ChineseCalendar::SolarHolidayStruct(9, 27, 0, "世界旅游日"),
    ChineseCalendar::SolarHolidayStruct(9, 28, 0, "孔子诞辰"),
    ChineseCalendar::SolarHolidayStruct(10, 1, 1, "国庆节 国际音乐日"),
    ChineseCalendar::SolarHolidayStruct(10, 2, 1, "国庆节假日"),
    ChineseCalendar::SolarHolidayStruct(10, 3, 1, "国庆节假日"),
    ChineseCalendar::SolarHolidayStruct(10, 6, 0, "老人节"),
    ChineseCalendar::SolarHolidayStruct(10, 24, 0, "联合国日"),
    ChineseCalendar::SolarHolidayStruct(11, 10, 0, "世界青年节"),
    ChineseCalendar::SolarHolidayStruct(11, 12, 0, "孙中山诞辰纪念"),
    ChineseCalendar::SolarHolidayStruct(12, 1, 0, "世界艾滋病日"),
    ChineseCalendar::SolarHolidayStruct(12, 3, 0, "世界残疾人日"),
    ChineseCalendar::SolarHolidayStruct(12, 20, 0, "澳门回归纪念"),
    ChineseCalendar::SolarHolidayStruct(12, 24, 0, "平安夜"),
    ChineseCalendar::SolarHolidayStruct(12, 25, 0, "圣诞节"),
    ChineseCalendar::SolarHolidayStruct(12, 26, 0, "毛主席诞辰纪念")};

static const ChineseCalendar::LunarHolidayStruct lHolidayInfo[] = {
    ChineseCalendar::LunarHolidayStruct(1, 1, 1, "春节"),
    ChineseCalendar::LunarHolidayStruct(1, 15, 0, "元宵节"),
    ChineseCalendar::LunarHolidayStruct(5, 5, 0, "端午节"),
    ChineseCalendar::LunarHolidayStruct(7, 7, 0, "七夕情人节"),
    ChineseCalendar::LunarHolidayStruct(7, 15, 0, "中元节 盂兰盆节"),
    ChineseCalendar::LunarHolidayStruct(8, 15, 0, "中秋节"),
    ChineseCalendar::LunarHolidayStruct(9, 9, 0, "重阳节"),
    ChineseCalendar::LunarHolidayStruct(12, 8, 0, "腊八节"),
    ChineseCalendar::LunarHolidayStruct(12, 23, 0, "北方小年(扫房)"),
    ChineseCalendar::LunarHolidayStruct(12, 24, 0, "南方小年(掸尘)"),

};

static const ChineseCalendar::WeekHolidayStruct wHolidayInfo[] = {
    ChineseCalendar::WeekHolidayStruct(5, 2, 1, "母亲节"),
    ChineseCalendar::WeekHolidayStruct(5, 3, 1, "全国助残日"),
    ChineseCalendar::WeekHolidayStruct(6, 3, 1, "父亲节"),
    ChineseCalendar::WeekHolidayStruct(9, 3, 3, "国际和平日"),
    ChineseCalendar::WeekHolidayStruct(9, 4, 1, "国际聋人节"),
    ChineseCalendar::WeekHolidayStruct(10, 1, 2, "国际住房日"),
    ChineseCalendar::WeekHolidayStruct(10, 1, 4, "国际减轻自然灾害日"),
    ChineseCalendar::WeekHolidayStruct(11, 4, 5, "感恩节")};

ChineseCalendar::ChineseCalendar(DateTime& dt)
{
    int i;
    int leap;
    int temp;
    int offset;

    CheckDateLimit(dt);

    _date = dt.Date();
    _datetime = dt;

    //农历日期计算部分
    leap = 0;
    temp = 0;

    //计算两天的基本差距
    TimeSpan ts = _date - (*MinDay);
    offset = ts.Days();

    for (i = MinYear; i <= MaxYear; i++)
    {
        //求当年农历年天数
        temp = GetChineseYearDays(i);
        if (offset - temp < 1)
            break;
        else
        {
            offset = offset - temp;
        }
    }
    _cYear = i;

    //计算该年闰哪个月
    leap = GetChineseLeapMonth(_cYear);

    //设定当年是否有闰月
    if (leap > 0)
    {
        _cIsLeapYear = true;
    }
    else
    {
        _cIsLeapYear = false;
    }

    _cIsLeapMonth = false;
    for (i = 1; i <= 12; i++)
    {
        //闰月
        if ((leap > 0) && (i == leap + 1) && (_cIsLeapMonth == false))
        {
            _cIsLeapMonth = true;
            i = i - 1;
            temp = GetChineseLeapMonthDays(_cYear); //计算闰月天数
        }
        else
        {
            _cIsLeapMonth = false;
            temp = GetChineseMonthDays(_cYear, i); //计算非闰月天数
        }

        offset = offset - temp;
        if (offset <= 0)
            break;
    }

    offset = offset + temp;
    _cMonth = i;
    _cDay = offset;
}

ChineseCalendar::ChineseCalendar(int cy, int cm, int cd, bool leapMonthFlag)
{
    int i, leap, Temp, offset;

    CheckChineseDateLimit(cy, cm, cd, leapMonthFlag);

    _cYear = cy;
    _cMonth = cm;
    _cDay = cd;

    offset = 0;

    for (i = MinYear; i < cy; i++)
    {
        //求当年农历年天数
        Temp = GetChineseYearDays(i);
        offset = offset + Temp;
    }

    //计算该年应该闰哪个月
    leap = GetChineseLeapMonth(cy);
    if (leap != 0)
    {
        _cIsLeapYear = true;
    }
    else
    {
        _cIsLeapYear = false;
    }

    if (cm != leap)
    {
        //当前日期并非闰月
        _cIsLeapMonth = false;
    }
    else
    {
        //使用用户输入的是否闰月月份
        _cIsLeapMonth = leapMonthFlag;
    }

    //当年没有闰月||计算月份小于闰月
    if ((_cIsLeapYear == false) || (cm < leap))
    {
        for (i = 1; i < cm; i++)
        {
            Temp = GetChineseMonthDays(cy, i); //计算非闰月天数
            offset = offset + Temp;
        }

        //检查日期是否大于最大天
        if (cd > GetChineseMonthDays(cy, cm))
        {
            // 不合法的农历日期
            throw;
        }
        //加上当月的天数
        offset = offset + cd;
    }

    //是闰年，且计算月份大于或等于闰月
    else
    {
        for (i = 1; i < cm; i++)
        {
            //计算非闰月天数
            Temp = GetChineseMonthDays(cy, i);
            offset = offset + Temp;
        }

        //计算月大于闰月
        if (cm > leap)
        {
            Temp = GetChineseLeapMonthDays(cy); //计算闰月天数
            offset = offset + Temp;             //加上闰月天数

            if (cd > GetChineseMonthDays(cy, cm))
            {
                // 不合法的农历日期
                throw;
            }
            offset = offset + cd;
        }

        //计算月等于闰月
        else
        {
            //如果需要计算的是闰月，则应首先加上与闰月对应的普通月的天数
            if (_cIsLeapMonth == true) //计算月为闰月
            {
                Temp = GetChineseMonthDays(cy, cm); //计算非闰月天数
                offset = offset + Temp;
            }

            if (cd > GetChineseLeapMonthDays(cy))
            {
                // 不合法的农历日期
                throw;
            }
            offset = offset + cd;
        }
    }
    _date = MinDay->AddDays(offset);
}

int ChineseCalendar::GetChineseMonthDays(int year, int month) {
    if (BitTest32((LunarDateArray[year - MinYear] & 0x0000FFFF), (16 - month)))
            {
                return 30;
            }
            else
            {
                return 29;
            }
}

inline int ChineseCalendar::GetChineseLeapMonth(int year)
{
    return LunarDateArray[year - MinYear] & 0xF;
}

int ChineseCalendar::GetChineseLeapMonthDays(int year)
{
    if (GetChineseLeapMonth(year) != 0)
    {
        if ((LunarDateArray[year - MinYear] & 0x10000) != 0)
        {
            return 30;
        }
        else
        {
            return 29;
        }
    }
    else
    {
        return 0;
    }
}

int ChineseCalendar::GetChineseYearDays(int year)
{
    int i, f, sumDay, info;
    sumDay = 348; //29天*12个月
    i = 0x8000;
    info = LunarDateArray[year - MinYear] & 0x0FFFF;
    //计算12个月中有多少天为30天
    for (int m = 0; m < 12; m++)
    {
        f = info & i;
        if (f != 0)
        {
            sumDay++;
        }
        i = i >> 1;
    }
    return sumDay + GetChineseLeapMonthDays(year);
}

String ChineseCalendar::GetChineseHour(DateTime& dt)
{
    int _hour, _minute, offset, i;
    int indexGan;
    String tmpGan;

    //计算时辰的地支
    _hour = dt.Hour();     //获得当前时间小时
    _minute = dt.Minute(); //获得当前时间分钟

    if (_minute != 0)
        _hour += 1;
    offset = _hour / 2;
    if (offset >= 12)
        offset = 0;
    //zhiHour = String(1, zhiStr[offset]);

    //计算天干
    TimeSpan ts = _date - (*GanZhiStartDay);
    i = ts.Days() % 60;

    // ganStr[i % 10] 为日的天干,(n*2-1) %10得出地支对应,n从1开始
    indexGan = ((i % 10 + 1) * 2 - 1) % 10 - 1;

    tmpGan = ganStr.substr(indexGan) + ganStr.substr(0, indexGan + 2); //凑齐12位
    // ganHour = ganStr[((i % 10 + 1) * 2 - 1) % 10 - 1].ToString();

    return String(1, tmpGan[offset]) + String(1, zhiStr[offset]);
}

void ChineseCalendar::CheckDateLimit(DateTime& dt)
{
    if ((dt < (*MinDay)) || (dt > (*MaxDay)))
    {
        throw;
    }
}

void ChineseCalendar::CheckChineseDateLimit(int year, int month, int day, bool leapMonth)
{
    if ((year < MinYear) || (year > MaxYear))
    {
        // 非法农历日期
        throw;
    }
    if ((month < 1) || (month > 12))
    {
        // 非法农历日期
        throw;
    }
    if ((day < 1) || (day > 30)) //中国的月最多30天
    {
        // 非法农历日期
        throw;
    }
    int leap = GetChineseLeapMonth(year); // 计算该年应该闰哪个月
    if ((leapMonth == true) && (month != leap))
    {
        // 非法农历日期
        throw;
    }
}

String ChineseCalendar::ConvertNumToChineseNum(char n)
{
    if ((n < '0') || (n > '9'))
        return "";
    return String(1, HZNum[n - '0']);
}

bool ChineseCalendar::BitTest32(int num, int bitpostion)
{
    if ((bitpostion > 31) || (bitpostion < 0))
        throw;
    int bit = 1 << bitpostion;
    return !((num & bit) == 0);
}

int ChineseCalendar::ConvertDayOfWeek(DayOfWeek dayOfWeek)
{
    return static_cast<int>(dayOfWeek);
}

bool ChineseCalendar::CompareWeekDayHoliday(DateTime& date, int month, int week, int day)
{
    bool ret = false;
    if (date.Month() == month)
    {
        if (ConvertDayOfWeek(date.GetDayOfWeek()) == day) //星期几相同
        {
            DateTime firstDay = DateTime(date.Year(), date.Month(), 1); //生成当月第一天
            auto dayOfWeek = firstDay.GetDayOfWeek();
            int i = ConvertDayOfWeek(dayOfWeek);
            int firWeekDays = 7 - ConvertDayOfWeek(dayOfWeek) + 1; //计算第一周剩余天数

            if (i > day)
            {
                if ((week - 1) * 7 + day + firWeekDays == date.Day())
                {
                    ret = true;
                }
            }
            else
            {
                if (day + firWeekDays + (week - 2) * 7 == date.Day())
                {
                    ret = true;
                }
            }
        }
    }
    return ret;
}

String ChineseCalendar::NewCalendarHoliday()
{
    String tempStr = "";
    if (_cIsLeapMonth == false) //闰月不计算节日
    {
        for (const auto& lh : lHolidayInfo)
        {
            if ((lh.Month == _cMonth) && (lh.Day == _cDay))
            {

                tempStr = lh.HolidayName;
                break;
            }
        }

        //对除夕进行特别处理
        if (_cMonth == 12)
        {
            int i = GetChineseMonthDays(_cYear, 12); //计算当年农历12月的总天数
            if (_cDay == i)                          //如果为最后一天
            {
                tempStr = "除夕";
            }
        }
    }
    return tempStr;
}

String ChineseCalendar::WeekDayHoliday()
{
    String tempStr = "";
    for (const auto &wh : wHolidayInfo)
    {
        if (CompareWeekDayHoliday(_date, wh.Month, wh.WeekAtMonth, wh.WeekDay))
        {
            tempStr = wh.HolidayName;
            break;
        }
    }
    return tempStr;
}

String ChineseCalendar::DateHoliday()
{
    String tempStr = "";
    for (const auto &sh : sHolidayInfo)
    {
        if ((sh.Month == _date.Month()) && (sh.Day == _date.Day()))
        {
            tempStr = sh.HolidayName;
            break;
        }
    }
    return tempStr;
}

DateTime ChineseCalendar::Date()
{
    return _date;
}

DayOfWeek ChineseCalendar::WeekDay()
{
    return _date.GetDayOfWeek();
}

String ChineseCalendar::WeekDayStr()
{
    switch (_date.GetDayOfWeek())
    {
    case DayOfWeek::Sunday:
        return "星期日";
    case DayOfWeek::Monday:
        return "星期一";
    case DayOfWeek::Tuesday:
        return "星期二";
    case DayOfWeek::Wednesday:
        return "星期三";
    case DayOfWeek::Thursday:
        return "星期四";
    case DayOfWeek::Friday:
        return "星期五";
    default:
        return "星期六";
    }
}

String ChineseCalendar::DateString()
{
    return "公元" + _date.ToString();
}

bool ChineseCalendar::IsLeapYear()
{
    return DateTime::IsLeapYear(_date.Year());
}

String ChineseCalendar::ChineseConstellation()
{
    int offset = 0;
    int modStarDay = 0;

    TimeSpan ts = _date - (*ChineseConstellationReferDay);
    offset = ts.Days();
    modStarDay = offset % 28;
    return (modStarDay >= 0 ? _chineseConstellationName[modStarDay] : _chineseConstellationName[27 + modStarDay]);
}

String ChineseCalendar::ChineseHour()
{
    return GetChineseHour(_datetime);
}

bool ChineseCalendar::IsChineseLeapMonth()
{
    return _cIsLeapMonth;
}

bool ChineseCalendar::IsChineseLeapYear()
{
    return _cIsLeapYear;
}

int ChineseCalendar::ChineseDay()
{
    return _cDay;
}

String ChineseCalendar::ChineseDayString()
{
    switch (_cDay)
    {
    case 0:
        return "";
    case 10:
        return "初十";
    case 20:
        return "二十";
    case 30:
        return "三十";
    default:
        return String(1, nStr2[(int)(_cDay / 10)]) + String(1, nStr1[_cDay % 10]);
    }
}

int ChineseCalendar::ChineseMonth()
{
    return _cMonth;
}

String ChineseCalendar::ChineseMonthString()
{
    return _monthString[_cMonth];
}

int ChineseCalendar::ChineseYear()
{
    return _cYear;
}

String ChineseCalendar::ChineseYearString()
{
    String tempStr = "";
    String num = to_string(_cYear);
    for (int i = 0; i < 4; i++)
    {
        tempStr += ConvertNumToChineseNum(num[i]);
    }
    return tempStr + "年";
}

String ChineseCalendar::ChineseDateString()
{
    if (_cIsLeapMonth == true)
    {
        return "农历" + ChineseYearString() + "闰" + ChineseMonthString() + ChineseDayString();
    }
    else
    {
        return "农历" + ChineseYearString() + ChineseMonthString() + ChineseDayString();
    }
}

/// <summary>
/// 定气法计算二十四节气,二十四节气是按地球公转来计算的，并非是阴历计算的
/// </summary>
/// <remarks>
/// 节气的定法有两种。古代历法采用的称为"恒气"，即按时间把一年等分为24份，
/// 每一节气平均得15天有余，所以又称"平气"。现代农历采用的称为"定气"，即
/// 按地球在轨道上的位置为标准，一周360°，两节气之间相隔15°。由于冬至时地
/// 球位于近日点附近，运动速度较快，因而太阳在黄道上移动15°的时间不到15天。
/// 夏至前后的情况正好相反，太阳在黄道上移动较慢，一个节气达16天之多。采用
/// 定气时可以保证春、秋两分必然在昼夜平分的那两天。
/// </remarks>
String ChineseCalendar::ChineseTwentyFourDay()
{
    DateTime baseDateAndTime = DateTime(1900, 1, 6, 2, 5, 0); //#1/6/1900 2:05:00 AM#
    double num;
    String tempStr = "";

    int y = _date.Year();

    for (int i = 1; i <= 24; i++)
    {
        num = 525948.76 * (y - 1900) + sTermInfo[i - 1];

        auto newDate = baseDateAndTime.AddMinutes(num); //按分钟计算
        if (newDate.DayOfYear() == _date.DayOfYear())
        {
            tempStr = SolarTerm[i - 1];
            break;
        }
    }
    return tempStr;
}

//当前日期前一个最近节气
String ChineseCalendar::ChineseTwentyFourPrevDay()
{
    DateTime baseDateAndTime = DateTime(1900, 1, 6, 2, 5, 0); //#1/6/1900 2:05:00 AM#
    double num;
    String tempStr = "";

    int y = _date.Year();

    for (int i = 24; i >= 1; i--)
    {
        num = 525948.76 * (y - 1900) + sTermInfo[i - 1];

        auto newDate = baseDateAndTime.AddMinutes(num); //按分钟计算

        if (newDate.DayOfYear() < _date.DayOfYear())
        {
            tempStr = SolarTerm[i - 1] + "\"" + newDate.ToString() + "\"";
            break;
        }
    }

    return tempStr;
}

//当前日期后一个最近节气
String ChineseCalendar::ChineseTwentyFourNextDay()
{
    DateTime baseDateAndTime = DateTime(1900, 1, 6, 2, 5, 0); //#1/6/1900 2:05:00 AM#
    double num;
    String tempStr = "";

    int y = _date.Year();

    for (int i = 1; i <= 24; i++)
    {
        num = 525948.76 * (y - 1900) + sTermInfo[i - 1];

        auto newDate = baseDateAndTime.AddMinutes(num); //按分钟计算

        if (newDate.DayOfYear() > _date.DayOfYear())
        {
            tempStr = SolarTerm[i - 1] + "\"" + newDate.ToString() + "\"";
            break;
        }
    }
    return tempStr;
}

String ChineseCalendar::Constellation()
{
    int index = 0;
    int y, m, d;
    y = _date.Year();
    m = _date.Month();
    d = _date.Day();
    y = m * 100 + d;

    if (((y >= 321) && (y <= 419)))
    {
        index = 0;
    }
    else if ((y >= 420) && (y <= 520))
    {
        index = 1;
    }
    else if ((y >= 521) && (y <= 620))
    {
        index = 2;
    }
    else if ((y >= 621) && (y <= 722))
    {
        index = 3;
    }
    else if ((y >= 723) && (y <= 822))
    {
        index = 4;
    }
    else if ((y >= 823) && (y <= 922))
    {
        index = 5;
    }
    else if ((y >= 923) && (y <= 1022))
    {
        index = 6;
    }
    else if ((y >= 1023) && (y <= 1121))
    {
        index = 7;
    }
    else if ((y >= 1122) && (y <= 1221))
    {
        index = 8;
    }
    else if ((y >= 1222) || (y <= 119))
    {
        index = 9;
    }
    else if ((y >= 120) && (y <= 218))
    {
        index = 10;
    }
    else if ((y >= 219) && (y <= 320))
    {
        index = 11;
    }
    else
    {
        index = 0;
    }

    return _constellationName[index];
}

/// 计算属相的索引，注意虽然属相是以农历年来区别的，但是目前在实际使用中是按公历来计算的
/// 鼠年为1,其它类推
int ChineseCalendar::Animal()
{
    int offset = _date.Year() - AnimalStartYear;
    return (offset % 12) + 1;
}

String ChineseCalendar::AnimalString()
{
    int offset = _date.Year() - AnimalStartYear; //阳历计算
    //int offset = _cYear - AnimalStartYear;　农历计算
    return String(1, animalStr[offset % 12]);
}

// 取农历年的干支表示法如 乙丑年
String ChineseCalendar::GanZhiYearString()
{
    int i = (_cYear - GanZhiStartYear) % 60; //计算干支
    String tempStr = String(1, ganStr[i % 10]) + String(1, zhiStr[i % 12]) + "年";
    return tempStr;
}

// 取干支的月表示字符串，注意农历的闰月不记干支
String ChineseCalendar::GanZhiMonthString()
{
    //每个月的地支总是固定的,而且总是从寅月开始
    int zhiIndex;
    if (_cMonth > 10)
    {
        zhiIndex = _cMonth - 10;
    }
    else
    {
        zhiIndex = _cMonth + 2;
    }
    String zhi = String(1, zhiStr[zhiIndex - 1]);

    //根据当年的干支年的干来计算月干的第一个
    int ganIndex = 1;

    int i = (_cYear - GanZhiStartYear) % 60; //计算干支
    switch (i % 10)
    {
    case 0: //甲
        ganIndex = 3;
        break;
    case 1: //乙
        ganIndex = 5;
        break;
    case 2: //丙
        ganIndex = 7;
        break;
    case 3: //丁
        ganIndex = 9;
        break;
    case 4: //戊
        ganIndex = 1;
        break;
    case 5: //己
        ganIndex = 3;
        break;
    case 6: //庚
        ganIndex = 5;
        break;
    case 7: //辛
        ganIndex = 7;
        break;
    case 8: //壬
        ganIndex = 9;
        break;
    case 9: //癸
        ganIndex = 1;
        break;

    }
    String gan = String(1, ganStr[(ganIndex + _cMonth - 2) % 10]);

    return gan + zhi + "月";
}

String ChineseCalendar::GanZhiDayString()
{
    int i, offset;
    TimeSpan ts = _date - (*GanZhiStartDay);
    offset = ts.Days();
    i = offset % 60;
    return String(1, ganStr[i % 10]) + String(1, zhiStr[i % 12]) + "日";
}

String ChineseCalendar::GanZhiDateString()
{
    return GanZhiYearString() + GanZhiMonthString() + GanZhiDayString();
}

} // namespace datetime
} // namespace arklight
