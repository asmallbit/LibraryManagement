#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义图书的结构体
struct Book;
typedef struct Book *PBookNode;
struct Book
{
    char *bookName, *author;
    int index, exist, inventory;
    //exist 现存量      inventory   库存量
    PBookNode next;
};
typedef struct Book *PBook;

//初始化图书馆的书
PBook initBook(int namel, int authorl);
//图书入库
int getStock(PBook p, int index, char *name, char *author, int num);
//根据书名获取图书的信息
PBookNode getIndexBookName(PBook p, char *name);
//将符合条件的查询结果入栈(针对书)
int pushBook(PBook p, PBookNode node);
//根据作者获取图书信息(配合函数pushBook()使用,因为作者和书可能存在一对多的关系)
PBookNode getIndexAuthor(PBook p, PBook stack, char *author);
//根据书号查询图书信息
PBookNode getIndexIndex(PBook p, int index);
//存书的栈  出栈
int popBook(PBook p);
//打印当前的所有书籍
void printBooks(PBook p);
//打印单个图书信息
void printABook(PBookNode p);
//释放关于书指针
void freePBook(PBook p);

#endif