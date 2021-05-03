#include "include/library.h"
#include <stdio.h>

//初始化图书馆的书
PBook initBook(int namel, int authorl)
{
    PBook new;
    new = (PBook)malloc(sizeof(struct Book));
    if (new != NULL)
    {
        new->bookName = (char *)malloc(sizeof(char) * (namel + 1));
        if (new->bookName == NULL)
        {
            printf("Out of space!\n");
            free(new);
            return NULL;
        }
        new->author = (char *)malloc(sizeof(char) * (authorl));
        if (new->author == NULL)
        {
            printf("Out of space!\n");
            free(new->bookName);
            free(new);
            return 0;
        }
        new->next = NULL;
        new->exist = new->inventory = 0;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//图书入库
int getStock(PBook p, int index, char *name, char *author, int num)
{
    PBook new, temp;
    temp = getIndexIndex(p, index);
    if (temp == NULL)
    {
        new = initBook(strlen(name), strlen(author));
        if (new == NULL)
        {
            return 0;
        }
        strcpy(new->author, author);
        strcpy(new->bookName, name);
        new->exist = new->inventory = num;
        new->index = index;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new;
        return 1;
    }
    else
    {
        temp->exist += num;
        temp->inventory += num;
        return 1;
    }
}

//根据书名获取图书的信息
PBookNode getIndexBookName(PBook p, char *name)
{
    if (p->next == NULL)
    {
        //printf("图书馆暂时没有任何书籍\n");
        return NULL;
    }
    p = p->next;
    while (p != NULL)
    {
        if (strcmp(p->bookName, name) == 0)
        {
            break;
        }
        p = p->next;
    }
    if (p == NULL)
    {
        printf("图书馆库存中没有此书籍\n");
        return NULL;
    }
    return p;
}

//根据作者获取图书信息(配合函数pushBook()使用,因为作者和书可能存在一对多的关系)
PBookNode getIndexAuthor(PBook p, PBook stack, char *author)
{
    if (p->next == NULL)
    {
        //printf("图书馆暂时没有任何书籍\n");
        return NULL;
    }
    p = p->next;
    while (p != NULL)
    {
        if (strcmp(p->author, author) == 0)
        {
            pushBook(stack, p);
        }
        p = p->next;
    }
    if (stack->next == NULL)
    {
        //printf("图书馆库存中没有此作者的书籍\n");
        return NULL;
    }
    return stack;
}

//根据书号查询图书信息
PBookNode getIndexIndex(PBook p, int index)
{
    if (p->next == NULL)
    {
        //printf("图书馆暂时没有任何书籍\n");
        return NULL;
    }
    while (p != NULL)
    {
        if (p->index == index)
        {
            break;
        }
        p = p->next;
    }
    if (p == NULL)
    {
        //printf("图书馆库存中没有此书籍\n");
        return NULL;
    }
    return p;
}

//将符合条件的查询结果入栈(针对书)
int pushBook(PBook p, PBookNode node)
{
    PBook new, temp;
    new = initBook(strlen(node->bookName), strlen(node->author));
    if (new == NULL)
    {
        return 0;
    }
    strcpy(new->author, node->author);
    strcpy(new->bookName, node->bookName);
    new->exist = node->exist;
    new->index = node->index;
    new->inventory = node->inventory;
    temp = p->next;
    p->next = new;
    new->next = temp;
    return 1;
}

//存书的栈  出栈
int popBook(PBook p)
{
    PBookNode temp;
    if (p->next == NULL)
    {
        printf("栈中没有元素\n");
        return 0;
    }
    temp = p->next->next;
    free(p->next);
    p->next = temp;
    return 1;
}

//打印当前的所有书籍
void printBooks(PBook p)
{
    if (p->next == NULL)
    {
        //printf("当前没有藏书\n");
        return;
    }
    p = p->next;
    printf("书号\t书名\t作者\t现存量\t库存量\n");
    while (p != NULL)
    {
        printf("%d\t%s\t%s\t%d\t%d\n", p->index, p->bookName, p->author, p->exist, p->inventory);
        p = p->next;
    }
}

//打印单个图书信息
void printABook(PBookNode p)
{
    printf("书号\t书名\t作者\t现存量\t库存量\n");
    printf("%d\t%s\t%s\t%d\t%d\n", p->index, p->bookName, p->author, p->exist, p->inventory);
}

//后续处理 释放指针
void freePBook(PBook p)
{
    PBook temp;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
}