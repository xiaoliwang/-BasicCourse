#ifndef _DATA_BASE_SQLISE_
#define _DATA_BASE_SQLISE_

#define OVERFLOW -1

#define TRUE 1
#define FALSE 0
#define ERROR 1
#define OK 0

typedef int ElemType;
typedef int Status;
typedef int bool;

typedef struct
{
	ElemType *elem; //存储空间的其实位置
	int list_size; // 当前分配的存储容量
	int length; // 当前链表的长度
}SqList;

Status InitSqList(SqList *L); // 初始化线性表
Status DestroyList(SqList *L); // 销毁表

Status ListInsert(SqList *L, int i, ElemType e); // 在位置i插入元素
Status ListPush(SqList *L, ElemType e);
Status GetElem(SqList L, int i, ElemType *e); // 获取位置i的元素
Status ListDelete(SqList *L, int i, ElemType *e); // 删除位置i的元素
Status SwapElem(SqList *L, int i, int j); // 
Status ClearList(); // 清空顺序表
SqList ListSlice(SqList L, int start, int end); // 截取数组的一部分

bool ListEmpty(SqList L); // 顺序表是否为空
int ListLength(SqList L); // 获取顺序表长度

// 辅助函数
void PrintList(SqList* sqlist); //打印线性表
#endif