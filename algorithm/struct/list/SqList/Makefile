SqList = Operation.o test.o
edit: $(SqList)
	gcc -o test $(SqList)
Operation.o: Data_base.h
test.o: Data_base.h
.PHONY: clean
clean:
	-rm test *.o