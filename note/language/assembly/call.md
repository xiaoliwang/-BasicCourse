# 函数调用约定

## stdcall

> 因为pascal使用该规范，故又称为*pascal调用规范*

- 参数从右向左压堆栈
- 函数自身修改堆栈
- 函数的装饰名为函数名自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸

```assembly

```

## cdecl

## fastcall

## thiscall

## naked call