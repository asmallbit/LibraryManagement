#include "include\rest.h"

//确认输入是否为日期
int isTrueDate(int num)
{
    int year, month, day;
    year = num / 10000;
    month = num / 100 - year * 100;
    day = num % 1000000;
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
    int now, year, month, day;
    year = num / 10000;
    month = num / 100 - year * 100;
    day = num % 1000000;
    now = (day + month * 100 + year * 10000) * 86400;
    return now;
}

//时间戳转整形(不准确,只精确到天)
int timeToInt(int date)
{
    int num, year, month, day, result;
    num = date / 86400;
    year = num / 10000;
    month = num / 100 - year * 100;
    day = num % 1000000;
    result = year * 1000 + month * 100 + day;
    return result;
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