#ifndef REST_H
#define REST_H
#include <stdlib.h>
#include <time.h>

//日期处理
int isDate(int x);
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

#endif