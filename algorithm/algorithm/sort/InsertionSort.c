#include "../../struct/list/SqList_extra/Data_Base.h"
#include <stdio.h>
#include <stdlib.h>

// 当使用链表时，可以考虑使用这种
Status InsertionSort1(SqList* sqlist)
{
	ElemType *pe = (ElemType *) malloc(sizeof(ElemType));
	ElemType *ce = (ElemType *) malloc(sizeof(ElemType));
	for (int i = 1; i < sqlist->length; ++i) {
		ListDelete(sqlist, i, ce);
		for (int j = i - 1; j >= 0; --j) {
			GetElem(*sqlist, j, pe);
			if (*pe < *ce){
				ListInsert(sqlist, j + 1, *ce);
				break;
			} else if (j == 0) {
				ListInsert(sqlist, j, *ce);
			}
		}
	}
	return OK;
}

// 当使用顺序表时，可以考虑使用这种
Status InsertionSort2(SqList* sqlist)
{
	ElemType *pe = (ElemType *) malloc(sizeof(ElemType));
	ElemType *ce = (ElemType *) malloc(sizeof(ElemType));
	for (int i = 1; i < sqlist->length; ++i) {
		GetElem(*sqlist, i, ce);
		for (int j = i - 1; j >= 0; --j) {
			GetElem(*sqlist, j, pe);
			if (*pe > *ce){
				SwapElem(sqlist, j, j + 1);
			} else {
				break;
			}
		}
	}
	return OK;
}

int main(int argc, const char *argv[])
{
	SqList *sqlist = (SqList*) malloc(sizeof(SqList));
	InitSqList(sqlist);
	for (int i = 0; i < 10; ++i) {
		ListInsert(sqlist, i, 15 - i);
	}
	puts("Original Array:");
	PrintList(sqlist);
	puts("sort Array:");
	InsertionSort1(sqlist);
	PrintList(sqlist);

	for (int i = 0; i < 10; ++i) {
		ListInsert(sqlist, i, 15 - i);
	}
	puts("Another Original Array:");
	PrintList(sqlist);
	puts("sort again Array:");
	InsertionSort2(sqlist);
	PrintList(sqlist);
	return OK;
}
