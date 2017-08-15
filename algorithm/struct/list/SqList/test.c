#include "Data_Base.h"
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  SqList *sqlist = (SqList*) malloc(sizeof(SqList));
  InitSqList(sqlist);
  printf("the original length is %d\n", sqlist->length);

  ElemType *pe = (ElemType *) malloc(sizeof(ElemType));
  GetElem(*sqlist, 2, pe);
  printf("get 2th element is %d\n", *pe);
  
  ElemType e = 12;
  ListInsert(sqlist, 16 ,e);
  GetElem(*sqlist, 2, pe);
  printf("the length after insert one element is %d\n", sqlist->length);
  Print_SqList(sqlist);
  printf("the 2th element now is %d\n", *pe);
  
  ListDelete(sqlist, 2, &e);
  printf("delete 2th element is %d\n", e);
  Print_SqList(sqlist);
  GetElem(*sqlist, 2, pe);
  printf("get 2th element now is %d\n", *pe);
  printf("the length after delete on element is %d\n", sqlist->length);
  
  free(pe);
  free(sqlist);
  return TRUE;
}
