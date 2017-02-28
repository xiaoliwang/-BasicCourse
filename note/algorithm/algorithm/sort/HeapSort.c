#include "../../struct/list/SqList_extra/Data_Base.h"
#include <stdio.h>
#include <stdlib.h>

// 堆排序
SqList AssisHeapSort(SqList sqlist)
{
	if (sqlist.length == 1) {
		return sqlist;
	}

	int start = 0;
	int end = sqlist.length;
	int half = start + (end - start) / 2;
	SqList L1 = ListSlice(sqlist, start, half);
	SqList L2 = ListSlice(sqlist, half, end);

	L1 = AssisHeapSort(L1);
	L2 = AssisHeapSort(L2);
	
	SqList newsqlist;
	InitSqList(&newsqlist);
	ElemType *le1 = (ElemType *) malloc(sizeof(ElemType));
	ElemType *le2 = (ElemType *) malloc(sizeof(ElemType));

	int i, j;
	for (i = 0, j = 0; i < L1.length && j < L2.length;) {
		GetElem(L1, i, le1);
		GetElem(L2, j, le2);
		if (*le1 < *le2) {
			ListPush(&newsqlist, *le1);
			++i;
		} else {
			ListPush(&newsqlist, *le2);
			++j;
		}
	}

	if (i < L1.length) {
		for (int k = i; k < half; ++k) {
			GetElem(L1, k, le1);
			ListPush(&newsqlist, *le1);
		}
	} else {
		for (int k = j; k < end; ++k) {
			GetElem(L1, k, le1);
			ListPush(&newsqlist, *le1);
		}
	}

	return newsqlist;
}

int main(int argc, const char *argv[])
{
	SqList sqlist;
	InitSqList(&sqlist);
	for (int i = 0; i < 10; ++i) {
		ListInsert(&sqlist, i, 15 - i);
	}
	puts("Original Array:");
	PrintList(&sqlist);
	puts("sort Array:");
	SqList L = AssisHeapSort(sqlist);
	PrintList(&L);

	for (int i = 0; i < 10; ++i) {
		ListInsert(&sqlist, i, 15 - i);
	}
	puts("Another Original Array:");
	PrintList(&sqlist);
	puts("sort again Array:");
	L = AssisHeapSort(sqlist);
	PrintList(&L);
	return OK;
}