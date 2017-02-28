ISort = InsertionSort.o Operation.o
HSort = HeapSort.o Operation.o
temp1: $(ISort)
	gcc -o InsertionSort $(ISort)
temp2: $(HSort)
	gcc -o HeapSort $(HSort)
InsertionSort.o: ../../struct/list/SqList_extra/Data_Base.h # 使用自动推到功能
HeapSort.o: ../../struct/list/SqList_extra/Data_Base.h
Operation.o: ../../struct/list/SqList_extra/Operation.c ../../struct/list/SqList_extra/Data_Base.h
	gcc -c ../../struct/list/SqList_extra/Operation.c
.PHONY: clean all
clean:
	-rm InsertionSort HeapSort *.o # -表示报错也继续执行
all: temp1 temp2