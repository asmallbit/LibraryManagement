#include "..\include\rest.h"

//确认输入是否为真正的日期
int isTrueDate(int num)
{
    int year, month, day;
    year = num / 10000;
    month = num / 100 - year * 100;
    day = num - year * 10000 - month * 100;
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||
         month == 12) &&
        day > 31)
    {
        return 0;
    }
    if (month == 2)
    {
        if (year / 4 != 0 && day > 28)
        {
            return 0;
        }
        if (year / 4 == 0 && day > 29)
        {
            return 0;
        }
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return 0;
    }
    if (day < 1 || month < 1)
    {
        return 0;
    }
    if (month > 12)
    {
        return 0;
    }
    return 1;
}

//获取当前时间
int getTime(void)
{
    time_t now;
    time(&now);
    return now;
}

//打印借书日期
void getBorrowDate(void)
{
    time_t currtm;
    time(&currtm);
    printf("本次操作时间: %s", ctime(&currtm));
}

//整形转时间戳(不精确,只精确到天)
int intToTime(int num)
{
    int now, year, month, day, leapyears, trueYear;
    trueYear = year = num / 10000;
    leapyears = leapYearNum(1970, trueYear);
    year -= 1970;
    month = num / 100 - trueYear * 100;
    day = num - trueYear * 10000 - month * 100;
    //东八区时间 3600*8=28800
    if (!leap(trueYear))
    {
        now = (getDaysInYear(month, day) + (year - leapyears) * 365 + leapyears * 366) * 86400 + 28800;
    }
    else
    {
        if (month > 2)
        {
            now = (getDaysInYear(month, day) + (year - leapyears) * 365 + leapyears * 366 + 1) * 86400 + 28800;
        }
        else
        {
            now = (getDaysInYear(month, day) + (year - leapyears) * 365 + leapyears * 366) * 86400 + 28800;
        }
    }
    return now;
}

//确认一个时间段内有多少个闰年
int leapYearNum(int begin, int end)
{
    int num = 0;
    while (begin < end)
    {
        if (begin % 100 != 0 && begin % 4 == 0)
        {
            num++;
        }
        if (begin % 100 == 0 && begin % 400 == 0)
        {
            num++;
        }
        begin++;
    }
    return num;
}

//确定一年中的第几天
int getDaysInYear(int month, int date)
{
    int day_tab[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, day = 0;
    for (i = 1; i < month; i++)
    {
        day += day_tab[i];
    }
    day += date;
    return day;
}

//确认某一年是否为闰年
int leap(int year) //判断是否为闰年
{
    int leap;
    leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    return leap;
}

//根据一年中的第几天确定是几月几日
int reversegetDayInYear(int days, int year)
{
    int day_tab[12] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int result, month, day, temp = 0;
    month = days / 31 + 1;
    while (temp < month)
    {
        days -= day_tab[temp];
        temp++;
    }
    day = days;
    if (leap(year) && month >= 2)
    {
        day -= 1;
    }
    result = month * 100 + day;
    return result;
}

//时间戳转整形(不准确,只精确到天)
int timeToInt(int date)
{
    int num, year, month, day, result, counter, temp;
    num = date / 86400;
    //考虑闰年
    //(365*4+1)=1461
    counter = num / 1461;
    year = 1970 + counter * 4;
    temp = year;
    num -= 1461 * counter;
    year += num / 365;
    num -= 365 * (year - temp);
    temp = reversegetDayInYear(num, year);
    month = temp / 100;
    day = temp - month * 100;
    result = year * 1000 + month * 100 + day;
    //处理最终结果,若为七位数说明月份前少0,添上即可
    result = getTrueIntDate(result, year, month, day);
    return result;
}

//为日期格式补齐0
int getTrueIntDate(int fake, int year, int month, int day)
{
    if (fake < year * 10000)
    {
        //说明月份小于10(前面没有0)
        fake = year * 10000 + month * 100 + day;
    }
    return fake;
}

//处理用户输入
char *getString(void)
{
    char *str1;
    char *str2;
    int i = 1;
    str1 = (char *)malloc(sizeof(char) * (i + 1));
    while ('\n' != (str1[i - 1] = getchar()))
    {
        i++;
        str2 = (char *)malloc(strlen(str1) + 1);
        str1[i - 1] = '\0';
        strcpy(str2, str1);
        free(str1);
        str1 = (char *)malloc(sizeof(char) * (i + 1));
        if (NULL == str1)
        {
            free(str2);
            printf("No enough memory!");
            return NULL;
        }
        strcpy(str1, str2);
        free(str2);
    }
    str1[i - 1] = '\0';
    return str1;
}

//scanf的安全替代,仅针对整形
void safetyScanf(int *in)
{
    int choice, flag = 0;
    while (flag == 0)
    {
        flag = scanf("%d", in);
        while ((choice = getchar()) != '\n' && choice != EOF)
            ; //清除缓存
        if (flag == 0)
        {
            printf("输入错误,请重新输入: ");
        }
    }
}

void safetyScanfString(char *str)
{
    char *flag = NULL;
    int len;
    while (flag == 0)
    {
        //flag = scanf("%s", str);
        //flag = gets(str);
        flag = fgets(str, MAXWORDS-1, stdin);
        len = strlen(str);
        str[len-1] = '\0';
        //while ((choice = getchar()) != '\n' && choice != EOF)
        //; //清除缓存
        if (flag == 0)
        {
            printf("输入错误,请重新输入: ");
        }
    }
}