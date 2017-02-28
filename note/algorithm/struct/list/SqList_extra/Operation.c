#include "Data_Base.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INT_SIZE 5
#define LIST_INCREMENT 20

// 辅助函数
void PrintList(SqList* sqlist)
{
	ElemType *e = (ElemType *) malloc(sizeof(ElemType));
	for (int i = 0; i < sqlist->length; ++i) {
		GetElem(*sqlist, i, e);
		printf("%d ", *e);
	}
	puts("");
}

Status InitSqList(SqList *L)
{
	if (!L) {
		return ERROR;
	}
	L->elem = malloc(LIST_INT_SIZE * sizeof(ElemType));
	if (!L->elem) {
		exit(OVERFLOW);
	}
	L->length = 0;
	L->list_size = LIST_INT_SIZE;
	return OK;
}

Status DestroyList(SqList *L)
{
	free(L->elem);
	L->elem = NULL;
	L->length = 0;
	L->list_size = 0;
	return OK;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
	ElemType *newbase, *q, *p;
	if (i < 0 || i >= L->length + 1) {
		return ERROR;
	}
	if (L->length >= L->list_size) {
		newbase = realloc(L->elem, (L->list_size + LIST_INCREMENT) * sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L->elem = newbase;
		L->list_size += LIST_INCREMENT;
	}
	q = L->elem + i;
	for (p = L->elem + L->length - 1;p >= q; --p) {
		*(p + 1) = *p;
	}
	*q = e;
	++L->length;
	return OK;
}

Status ListPush(SqList *L, ElemType e)
{
	int length = L->length;
	ListInsert(L, length, e);
	return OK;
}

Status GetElem(SqList L, int i, ElemType *e)
{
	if (!L.length || i < 0 || i >= L.length) {
		return ERROR;
	}
	*e = *(L.elem + i);
	return OK;
	
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
	ElemType *p, *q;
	if (i < 0 || i > L->length - 1) {
		return ERROR;
	}
	p = L->elem + i;
	*e = *p;
	q = L->elem + L->length - 1;
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	--L->length;
	return OK;
}

Status SwapElem(SqList *L, int i, int j)
{
	if (i < 0 || i > L->length ||
		j < 0 || j > L->length) {
		return ERROR;
	}
	ElemType temp = *(L->elem + i);
	*(L->elem + i) = *(L->elem + j);
	*(L->elem + j) = temp;
	return OK;
}

Status ClearList(SqList* L)
{
	L->length = 0;
	return OK;
}

SqList ListSlice(SqList L, int start, int end)
{
	SqList *sqlist = (SqList*) malloc(sizeof(SqList));
	ElemType *e = (ElemType *) malloc(sizeof(ElemType));
	InitSqList(sqlist);
	for (int i = start; i < end; ++i) {
		GetElem(L, i, e);
		ListPush(sqlist, *e);
	}
	return *sqlist;
}

int ListLength(SqList L)
{
	return L.length;
}

bool ListEmpty(SqList L)
{
	if (L.length == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}