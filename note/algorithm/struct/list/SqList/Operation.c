#include "Data_Base.h"

Status InitSqList(SqList *L)
{
  if (!L)
    return ERROR;
  int i = 0;
  while (i < MAXSIZE - 4) {
    L->data[i++] = i;
  }
  L->length = i;
  return OK;
}

Status GetElem(SqList L, int i, ElemType *e)
{
  if (L.length == 0 || i < 0 || i >= L.length)
    return ERROR;
  if (!e)
    return ERROR;
  *e = L.data[i];
  return OK;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
  int k;
  if (L->length == MAXSIZE)
	  return ERROR;
  if (i < 0 || i > L->length)
	  return ERROR;
  for (k = L->length - 1; k >= i; k--) {
	  L->data[k + 1] = L->data[k];
  }
  L->data[i] = e;
  L->length++;
  return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
  int k;
  if (L->length == 0)
    return ERROR;
  if (i < 0 || i > L->length - 1)
    return ERROR;
  *e = L->data[i];
  if (i < L->length){
    for (k = i; k < L->length - 1; k++)
      L->data[k] = L->data[k + 1];
  }
  L->length--;
  return OK;
}

// 辅助函数
void Print_SqList(SqList* list)
{
  for(int i = 0; i < list->length; ++i){
    printf("%d ", list->data[i]);
  }
  printf("\n");
}

