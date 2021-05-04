#include "../include/borrow.h"

//初始化学生借书
PBorrow initBorrow(void)
{
    PBorrow new;
    new = (PBorrow)malloc(sizeof(struct Borrow));
    if (new != NULL)
    {
        new->book.next = NULL;
        new->next = NULL;
        new->book.author = (char *)malloc(sizeof(char) * 30);
        new->book.bookName = (char *)malloc(sizeof(char) * 30);
        if (new->book.author != NULL &&new->book.bookName != NULL)
        {
            return new;
        }
        else if (new->book.author != NULL &&new->book.bookName == NULL)
        {
            free(new->book.author);
            free(new);
        }
        else
        {
            free(new);
        }
    }
    printf("Out of space!\n");
    return NULL;
}

//借阅      option用来确定输入模式,即1.通过书名  2.通过书号
int getBorrow(PBook p, PBorrow pb, char *bookname, int id, int date, int index, int option)
{
    PBookNode book;
    PBorrow stu, temp;
    int i = 0;
    if (option == 1)
    {
        book = getIndexBookName(p, bookname);
    }
    //实现过程过于繁琐,暂时放弃,日后补充
    /*
    else if(option==2){
        book = getIndexAuthor(p, author);
    }
    */
    else if (option == 2)
    {
        book = getIndexIndex(p, index);
    }
    if (book == NULL)
    {
        return 0;
    }
    if (book->exist <= 0)
    {
        printf("此书已被借光\n");
        return 0;
    }
    stu = initBorrow();
    stu->id = id;
    stu->date = date;
    strcpy(stu->book.author, book->author);
    strcpy(stu->book.bookName, book->bookName);
    stu->book.index = book->index;
    stu->book.exist = stu->book.inventory = 1;
    (book->exist)--;
    temp = pb->next;
    pb->next = stu;
    stu->next = temp;
    return 1;
}

//将符合条件的查询结果入栈(针对借书的人)
int pushBorrower(PBorrow p, PBorrowNode node)
{
    PBorrow new, temp;
    new = initBorrow();
    if (new == NULL)
    {
        return 0;
    }
    strcpy(new->book.author, node->book.author);
    strcpy(new->book.bookName, node->book.bookName);
    new->book.exist = node->book.exist;
    new->book.index = node->book.index;
    new->book.inventory = node->book.inventory;
    temp = p->next;
    p->next = new;
    new->next = temp;
    return 1;
}

//存借书的人    出栈
int popBorrower(PBorrow p)
{
    PBorrowNode temp;
    if (p->next == NULL)
    {
        printf("栈中没有元素");
        return 0;
    }
    temp = p->next->next;
    free(p->next);
    p->next = temp;
    return 1;
}

//从借书的列表中删除节点
int delBorrower(PBorrow p, char *bookname, int id)
{
    if (p->next == NULL)
    {
        printf("目前没有人借书\n");
        return 0;
    }
    PBorrowNode temp, pre = p;
    p = p->next;
    int i;
    while (p != NULL)
    {
        if (strcmp(p->book.bookName, bookname) == 0 || p->id == id)
        {
            //已找到符合条件的节点
            temp = p->next;
            free(p);
            pre->next = temp;
            return 1;
        }
        pre = p;
        p = p->next;
    }
}

//归还
int getRestore(PBook p, PBorrow pb, char *bookname, int id, int date)
{
    int flag = 0;
    if (pb->next == NULL)
    {
        printf("输入无效,请重新输入\n");
        return 0;
    }
    PBorrowNode temp;
    PBookNode node, temp2;
    temp = pb->next;
    temp2 = p->next;
    while (temp != NULL)
    {
        if (temp->id == id && strcmp(temp->book.bookName, bookname) == 0)
        {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL && flag == 0)
    {
        printf("您尚未借阅此书籍\n");
        return 0;
    }
    while (temp2 != NULL)
    {
        if (strcmp(temp2->bookName, bookname) == 0)
        {
            break;
        }
        temp2 = temp2->next;
    }
    if (temp->date > date)
    {
        printf("您本次还书时间已超过最大期限,请下次注意\n");
    }
    node = getIndexBookName(p, bookname);
    node->exist++;
    delBorrower(pb, bookname, id);
    return 1;
}

//释放借书的人的指针
void freePBorrow(PBorrow p)
{
    PBorrow temp;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
}
