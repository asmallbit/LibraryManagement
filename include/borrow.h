#ifndef BORROW_H
#define BORROW_H
#ifndef LIBRARY_H
#include "library.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef MAXWORDS
#define MAXWORDS 100
#endif

//定义学生存储借书记录的结构体
struct Borrow;
typedef struct Borrow *PBorrowNode;
struct Borrow
{
    int date, id;
    struct Book book;
    PBorrowNode next;
};
typedef struct Borrow *PBorrow;

//初始化学生借书
PBorrow initBorrow(void);
//借阅      option用来确定输入模式,即1.通过书名  2.通过书号
int getBorrow(PBook p, PBorrow pb, char *bookname, int id, int date, int index, int option);
//将符合条件的查询结果入栈(针对借书的人)
int pushBorrower(PBorrow p, PBorrowNode node);
//存借书的人    出栈
int popBorrower(PBorrow p);
//从借书的列表中删除节点
int delBorrower(PBorrow p, char *bookname, int id);
//归还书籍
int getRestore(PBook p, PBorrow pb, char *bookname, int id, int date);
//释放关于借书的人的指针
void freePBorrow(PBorrow p);

#endif