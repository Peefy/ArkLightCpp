
#include "chinadate.h"

namespace arklight
{
namespace time
{

typedef wstring String;

static const long lunarInfo[] = {0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554,
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
static const String nStr1[] = {L"", L"正", L"二", L"三", L"四", L"五", L"六", L"七", L"八", L"九", L"十", L"十一", L"十二"};
static const String Gan[]{L"甲", L"乙", L"丙", L"丁", L"戊", L"己", L"庚", L"辛", L"壬", L"癸"};
static const String Zhi[]{L"子", L"丑", L"寅", L"卯", L"辰", L"巳", L"午", L"未", L"申", L"酉", L"戌", L"亥"};
static const String Animals[]{L"鼠", L"牛", L"虎", L"兔", L"龙", L"蛇", L"马", L"羊", L"猴", L"鸡", L"狗", L"猪"};
static const String solarTerm[]{L"小寒", L"大寒", L"立春", L"雨水", L"惊蛰", L"春分", L"清明", L"谷雨", L"立夏", L"小满", L"芒种", L"夏至", L"小暑", L"大暑", L"立秋", L"处暑", L"白露", L"秋分", L"寒露", L"霜降", L"立冬", L"小雪", L"大雪", L"冬至"};
static const int sTermInfo[]{0, 21208, 42467, 63836, 85337, 107014, 128867, 150921, 173149, 195551, 218072, 240693, 263343, 285989, 308563, 331033, 353350, 375494, 397447, 419210, 440795, 462224, 483532, 504758};
static const String lFtv[]{L"0101农历春节", L"0202 龙抬头节", L"0115 元宵节", L"0505 端午节", L"0707 七夕情人节", L"0815 中秋节", L"0909 重阳节", L"1208 腊八节", L"1114 李君先生生日", L"1224 小年", L"0100除夕"};
static const String sFtv[]{L"0101 新年元旦",
                           L"0202 世界湿地日",
                           L"0207 国际声援南非日",
                           L"0210 国际气象节",
                           L"0214 情人节",
                           L"0301 国际海豹日",
                           L"0303 全国爱耳日",
                           L"0308 国际妇女节",
                           L"0312 植树节 孙中山逝世纪念日",
                           L"0314 国际警察日",
                           L"0315 国际消费者权益日",
                           L"0317 中国国医节 国际航海日",
                           L"0321 世界森林日 消除种族歧视国际日",
                           L"0321 世界儿歌日",
                           L"0322 世界水日",
                           L"0323 世界气象日",
                           L"0324 世界防治结核病日",
                           L"0325 全国中小学生安全教育日",
                           L"0330 巴勒斯坦国土日",
                           L"0401 愚人节 全国爱国卫生运动月(四月) 税收宣传月(四月)",
                           L"0407 世界卫生日",
                           L"0422 世界地球日",
                           L"0423 世界图书和版权日",
                           L"0424 亚非新闻工作者日",
                           L"0501 国际劳动节",
                           L"0504 中国五四青年节",
                           L"0505 碘缺乏病防治日",
                           L"0508 世界红十字日",
                           L"0512 国际护士节",
                           L"0515 国际家庭日",
                           L"0517 世界电信日",
                           L"0518 国际博物馆日",
                           L"0520 全国学生营养日",
                           L"0523 国际牛奶日",
                           L"0531 世界无烟日",
                           L"0601 国际儿童节",
                           L"0605 世界环境日",
                           L"0606 全国爱眼日",
                           L"0617 防治荒漠化和干旱日",
                           L"0623 国际奥林匹克日",
                           L"0625 全国土地日",
                           L"0626 国际反毒品日",
                           L"0701 中国共产党建党日 世界建筑日",
                           L"0702 国际体育记者日",
                           L"0707 中国人民抗日战争纪念日",
                           L"0711 世界人口日",
                           L"0730 非洲妇女日",
                           L"0801 中国建军节",
                           L"0808 中国男子节(爸爸节)",
                           L"0815 日本正式宣布无条件投降日",
                           L"0908 国际扫盲日 国际新闻工作者日",
                           L"0910 教师节",
                           L"0914 世界清洁地球日",
                           L"0916 国际臭氧层保护日",
                           L"0918 九·一八事变纪念日",
                           L"0920 全国爱牙日",
                           L"0927 世界旅游日",
                           L"1001 国庆节 世界音乐日 国际老人节",
                           L"1001 国际音乐日",
                           L"1002 国际和平与民主自由斗争日",
                           L"1004 世界动物日",
                           L"1008 全国高血压日",
                           L"1008 世界视觉日",
                           L"1009 世界邮政日 万国邮联日",
                           L"1010 辛亥革命纪念日 世界精神卫生日",
                           L"1013 世界保健日 国际教师节",
                           L"1014 世界标准日",
                           L"1015 国际盲人节(白手杖节)",
                           L"1016 世界粮食日",
                           L"1017 世界消除贫困日",
                           L"1022 世界传统医药日",
                           L"1024 联合国日 世界发展信息日",
                           L"1031 世界勤俭日",
                           L"1107 十月社会主义革命纪念日",
                           L"1108 中国记者日",
                           L"1109 全国消防安全宣传教育日",
                           L"1110 世界青年节",
                           L"1111 国际科学与和平周(本日所属的一周)",
                           L"1112 孙中山诞辰纪念日",
                           L"1114 世界糖尿病日",
                           L"1117 国际大学生节 世界学生节",
                           L"1121 世界问候日 世界电视日",
                           L"1129 国际声援巴勒斯坦人民国际日",
                           L"1201 世界艾滋病日",
                           L"1203 世界残疾人日",
                           L"1205 国际经济和社会发展志愿人员日",
                           L"1208 国际儿童电视日",
                           L"1209 世界足球日",
                           L"1210 世界人权日",
                           L"1212 西安事变纪念日",
                           L"1213 南京大屠杀(1937年)纪念日！紧记血泪史！",
                           L"1221 国际篮球日",
                           L"1224 平安夜",
                           L"1225 圣诞节",
                           L"1226 毛主席诞辰",
                           L"1229 国际生物多样性日"};

static int getLYearDays(int y);
static int leapDays(int y);
static inline int leapMonth(int y);

// 传回农历y年的总天数
static int lYearDays(int y)
{
    int i, sum = 348;
    for (i = 0x8000; i > 0x8; i >>= 1)
    {
        if ((lunarInfo[y - 1900] & i) != 0)
            sum += 1;
    }
    return (sum + leapDays(y));
}

// 传回农历y年闰月的天数
static int leapDays(int y)
{
    if (leapMonth(y) != 0)
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
static inline int leapMonth(int y)
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
static String AnimalsYear(const int y)
{
    return Animals[(y - 4) % 12];
}

// 传入月日的offset 传回干支,0=甲子
static String Cyclicalm(const int num)
{
    return (Gan[num % 10] + Zhi[num % 12]);
}

// 传入offset 传回干支, 0=甲子
static String Cyclical(const int y)
{
    int num = y - 1900 + 36;
    return (Cyclicalm(num));
}

// 传出农历.year0 .month1 .day2 .yearCyl3 .monCyl4 .dayCyl5 .isLeap6
void Lunar(const int y, const int m, long nongDate[7])
{
    int i = 0, temp = 0, leap = 0;
    DateTime baseDate = new DateTime(1900 + 1900, 2, 31);
    DateTime objDate = new DateTime(y + 1900, m + 1, 1);
    TimeSpan ts = objDate - baseDate;
    long offset = (long)ts.TotalDays;
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
    return nongDate;
}

template <typename StringT>
ChinaDateBase<StringT>::ChinaDateBase() : _tick(0),
                                          _time(0),
                                          _intYear(0),    // 农历年(整型)
                                          _intMonth(0),   // 农历月(整型)
                                          _intDay(0),     // 农历天(整型)
                                          _strYear(""),   // 农历年(字符)
                                          _strMonth(""),  // 农历月(字符)
                                          _strDay(""),    // 农历天(字符)
                                          _anm(""),       // 字符属相
                                          _socalTerm(""), // 二十四节气
                                          _ftvl(""),      //阴历节日
                                          _ftvs("")       //阳历节日
{
}

template <typename StringT>
ChinaDateBase<StringT>::~ChinaDateBase()
{
}

template <typename StringT>
int ChinaDateBase<StringT>::GetLongSecond()
{
    return _time;
}

} // namespace util
} // namespace arklight
