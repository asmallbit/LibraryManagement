#ifndef REST_H
#define REST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//日期处理,确认输入是否为真正的日期
int isTrueDate(int x);
//确认一个时间段内有多少个闰年
int leapYearNum(int begin, int end);
//确认某年是否为闰年
int leap(int year);
//确定一年中的第几天
int getDaysInYear(int month, int date);
//根据一年中的第几天确定是几月几日
int reversegetDayInYear(int days, int year);
//为日期格式补齐0
int getTrueIntDate(int fake, int year, int month, int day);
//获取当前时间戳
int getTime(void);
//打印借书日期
void getBorrowDate(void);
//整形转时间戳(不准确,只精确到了天)
int intToTime(int num);
//时间戳转整形(不准确,精确到天)
int timeToInt(int date);
//输入处理
char *getString(void);
//scanf的安全替代,仅针对整形
void safetyScanf(int* in);
//针对字符串的输入
void safetyScanfString(char* str);

#endif