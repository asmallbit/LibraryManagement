#include "include/borrow.h"
#include "include/library.h"
#include "include/rest.h"
#include <stdio.h>
#include <stdlib.h>

//最后还书期限 UNIX时间戳 2022.5.30
#define MAXDEADLINE 1654012800
//书名所能容纳的最大值
#define MAXWORDS 100
int main()
{
    PBook book, node, bookStack, tempStack;
    PBorrow borrow, borrowNode, borrowStack, borrowStackNode;
    char input[MAXWORDS], bookname[MAXWORDS], author[MAXWORDS];
    int index, number, id, date, option, choice, dateSeconds;
    time_t temp;
    borrowStack = initBorrow();
    borrow = initBorrow();
    book = (PBook)malloc(sizeof(struct Book));
    book->next = NULL;
    bookStack = (PBook)malloc(sizeof(struct Book));
    bookStack->next = NULL;
    printf("*****************图书管理系统*****************\n");
    //safetyScanfString(input);
    while (strcmp(input, "9") != 0)
    {
    label1:
        printf("菜单:\n1.根据书名查询图书信息\n2.根据书号查询图书信息\n3.根据作者查询图书信息\n4.书籍入库\n5.借阅书籍\n6.归还书籍\n");
        printf("7.根据借书证号获取借书信息\n8.打印当前所有藏书\n9.退出\n请输入您需要的选项: ");
    label:
        safetyScanfString(input);
        //根据书名查询图书信息
        if (strcmp(input, "1") == 0)
        {
            printf("请输入您想查询的书籍名称: ");
            //bookname = getString();
            safetyScanfString(bookname);
            node = getIndexBookName(book, bookname);
            if (node != NULL)
            {
                printABook(node);
            }
            else
            {
                printf("没有此藏书\n");
            }
        }
        //根据书号查询图书信息
        else if (strcmp(input, "2") == 0)
        {
            printf("请输入要查询图书的书号: ");
            //scanf("%d", &index);
            safetyScanf(&index);
            node = getIndexIndex(book, index);
            if (node != NULL)
            {
                printABook(node);
            }
            else
            {
                printf("没有此藏书\n");
            }
        }
        //根据作者查询用户信息  由于作者与书可能是一对多的关系,这里引入了栈来存储同一作者名下所有书籍
        else if (strcmp(input, "3") == 0)
        {
            printf("请输入要查询图书的作者: ");
            //author = getString();
            safetyScanfString(author);
            node = getIndexAuthor(book, bookStack, author);
            if (bookStack->next != NULL)
            {
                printBooks(node);
            }
            else
            {
                printf("没有此藏书\n");
            }
            //清空栈
            node = node->next;
            while (node != NULL)
            {
                tempStack = node->next;
                free(node);
                node = tempStack;
            }
            bookStack->next = NULL;
        }
        //书籍入库
        else if (strcmp(input, "4") == 0)
        {
            printf("请输入您要入库的书籍信息:\n书号: ");
            //scanf("%d", &index);
            safetyScanf(&index);
            //buffer = getString();
            printf("书名: ");
            //bookname = getString();
            safetyScanfString(bookname);
            printf("作者: ");
            //author = getString();
            safetyScanfString(author);
            printf("数量(本数): ");
            //scanf("%d", &number);
            safetyScanf(&number);
            if (getStock(book, index, bookname, author, number))
            {
                printf("入库成功!\n");
            }
            else
            {
                printf("入库失败!\n");
            }
        }
        //借阅书籍
        else if (strcmp(input, "5") == 0)
        {
        label2:
            printf("你想要通过哪种方式查找你要借的书: 1.书名\t2.书号(请输入1或2)\n");
            //scanf("%d", &choice);
            safetyScanf(&choice);
            //buffer = getString();
            if (choice == 1)
            {
                //通过书名方式借书
                printf("你选择了通过书名的方式借书\n");
                printf("请输入你的借书证号: ");
                //scanf("%d", &id);
                safetyScanf(&id);
            label3:
                printf("请输入你计划的归还日期(8位数, 如20210101代表202１年1月1日): ");
                //scanf("%d", &date);
                safetyScanf(&date);
                if (!isTrueDate(date))
                {
                    printf("您输入的并不是一个正确的日期,请重新输入\n");
                    goto label3;
                }
                dateSeconds = intToTime(date);
                if (dateSeconds > MAXDEADLINE || dateSeconds < getTime())
                {
                    if (dateSeconds > MAXDEADLINE)
                    {
                        printf("最晚归还时间为: %d,请重新输入\n", timeToInt(MAXDEADLINE));
                    }
                    if (dateSeconds < getTime())
                    {
                        printf("您输入的是过去的时间,请重新输入\n");
                    }
                    goto label3;
                }
                //buffer = getString();
                printf("请输入你要借的书的书名 ");
                //bookname = getString();
                safetyScanfString(bookname);
                if (getBorrow(book, borrow, bookname, id, date, index, choice))
                {
                    printf("借书成功!\n");
                    getBorrowDate();
                }
                /*
                else
                {
                    printf("暂时没有此书籍,借书失败\n");
                }
                 */
            }
            else if (choice == 2)
            {
                //通过书号方式借书
                printf("你选择了通过书号的方式借书\n");
                printf("请输入你的借书证号: ");
                //scanf("%d", &id);
                safetyScanf(&id);
            label4:
                printf("请输入你计划的归还日期(8位数, 如20210101代表2021年1月1日): ");
                //scanf("%d", &date);
                safetyScanf(&date);
                if (!isTrueDate(date))
                {
                    printf("您输入的并不是一个正确的日期,请重新输入\n");
                    goto label4;
                }
                dateSeconds = intToTime(date);
                if (dateSeconds > MAXDEADLINE || dateSeconds < getTime())
                {
                    if (dateSeconds > MAXDEADLINE)
                    {
                        printf("最晚归还时间为: %d,请重新输入\n", timeToInt(MAXDEADLINE));
                    }
                    if (dateSeconds < getTime())
                    {
                        printf("您输入的是过去的时间,请重新输入\n");
                    }
                    goto label4;
                }
                printf("请输入你要借的书的书号");
                //scanf("%d", &index);
                safetyScanf(&index);
                if (getBorrow(book, borrow, bookname, id, date, index, choice))
                {
                    printf("借书成功!\n");
                    getBorrowDate();
                }
                else
                {
                    printf("暂时没有此书籍,借书失败!\n");
                }
            }
            else
            {
                //错误输入处理
                printf("错误输入,请检查你的输入");
                goto label2;
            }
        }
        //归还书籍
        else if (strcmp(input, "6") == 0)
        {
            printf("请输入要归还的书的书名: ");
            //bookname = getString();
            safetyScanfString(bookname);
            printf("请输入你的借书证号(ID): ");
            //scanf("%d", &id);
            safetyScanf(&id);
            //printf("请输入归还日期:\n");
            //scanf("%d", &date);
            //safetyScanf(&date);

            //Need Test!!!!!!
            time(&temp);
            temp = timeToInt((int)temp);
            option = getRestore(book, borrow, bookname, id, date);
            if (option == 1)
            {
                printf("还书成功");
                getBorrowDate();
            }
        }
        //根据借书证号获取借书信息
        else if (strcmp(input, "7") == 0)
        {
            printf("请输入您的借书证号: ");
            //scanf("%d", &id);
            safetyScanf(&id);
            borrowNode = borrow->next;
            while (borrowNode != NULL)
            {
                if (borrowNode->id == id)
                {
                    pushBorrower(borrowStack, borrowNode);
                }
                borrowNode = borrowNode->next;
            }
            borrowStackNode = borrowStack->next;
            if (borrowStackNode == NULL)
            {
                printf("您当前尚未借阅任何书籍");
            }
            else
            {
                printf("您的借书有:\n");
                printf("书号\t书名\t作者\n");
                while (borrowStackNode != NULL)
                {
                    printf("%d\t%s\t%s\n", borrowStackNode->book.index, borrowStackNode->book.bookName, borrowStackNode->book.author);
                    borrowStackNode = borrowStackNode->next;
                }
            }
            if(borrowStack->next!=NULL) {
                //释放掉borrowStackNode
                freePBorrow(borrowStack->next);
                borrowStack->next = NULL;
            }
        }
        //打印当前所有藏书
        else if (strcmp(input, "8") == 0)
        {
            node = book;
            printBooks(node);
        }
        //退出即错误输入的处理
        else
        {
            if (strcmp(input, "9") != 0 && strcmp(input, "\0") != 0)
            {
                printf("您的输入有误,请重新输入\n");
                goto label1;
            }
            if (strcmp(input, "\0") == 0)
            {
                printf("错误输入,请重新输入: ");
                goto label;
            }
            if (strcmp(input, "9") == 0)
            {
                //程序即将退出,释放当前的指针
                freePBook(book);
                freePBorrow(borrow);
                //释放bookname, input author 考虑第一次运行时bookname等指针没有申请空间的情况   待补充
                /**
                **    if(author!=NULL){
                **        free(author);
                **    }
                **    if(bookname!=NULL){
                **        free(bookname);
                **    }
                **/
            }
        }
        printf("\n**************************************\n");
    }
    return 0;
}