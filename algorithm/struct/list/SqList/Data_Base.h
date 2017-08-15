#ifndef _DATA_BASE_SQLIST_
#define _DATA_BASE_SQLIST_

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef int bool;

typedef struct
{
  ElemType data[MAXSIZE];
  int length;
}SqList;

Status InitSqList(SqList *L);
Status GetElem(SqList L, int i, ElemType *e);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelete(SqList *L, int i, ElemType *e);

// 辅助函数
void Print_SqList(SqList *L);
#endif 