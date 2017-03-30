
## 安装环境

### ubuntu
```shell
apt-get install gcc nasm gcc-multilib -y
```

### centos

```shell
yum install gcc nasm glibc-devel.i686 glibc-devel ibstdc++-devel.i686 -y
```

```shell
echo $? # 显示最后命令退出状态，0表示没有错误，1表示有错误
```

### first.asm

```asm
global main

main:
    mov eax, 0
    ret
```

编译
```shell
# 32位编译
nasm -f elf first.asm -o first.o
gcc -m32 first.o -o first

# 64位编译
nasm -f elf64 first.asm -o first.o
gcc -m64 first.o -o first
```

### add.asm
```asm
global main

main:
    mov dword [x], 0x1
    mov dword [y], 0x2
    mov eax, [x]
    mov ebx, [y]
    add eax, ebx
    mov [z], eax
    mov eax, [z]
    ret

section .data
x dw 0
y dw 0
z dw 0
```

### 汇编指令
```asm
; mov
mov eax, 1        ; 让eax的值为1
mov ebx, eax      ; ecx = eax

; add
add eax, 2        ; eax = eax + 2

; sub
sub eax, 1        ; eax = eax - 1
sub eax, ecx      ; eax = eax - ecx

; ret
ret               ; 返回，整个程序最后的返回值。
```

> `eax ebx ecx edx`为四个通用寄存器，`esi edi ebp`多见于访问内存情况, `eip` 存储执行位置的信息

```asm
global main

main:
    mov ebx, 1
    mov ecx, 2
    add ebx, ecx

    mov [neicun], ebx
    mov eax, [neicun]

    ret

section .data
neicun dw 0       ;dw ( double word ) 表示四字节，0表示填充0
```

例子：

```asm
global main

main:
    mov eax, [number_1]
    mov ebx, [number_2]
    add eax, ebx

    ret

section .data
number_1 dw 10
number_2 dw 20
```

### 反编译
```shell
apt-get install gdb -y
yum install gdb -y

gdb ./add
(gdb) set disassembly-flavor intel # 设置显示格式
(gdb) disas main
(gdb) break *0x080483f5 # 设置断点
(gdb) info register eax # 查看寄存器的值
(gdb) stepi # 执行下一个指令
(gdb) disas # 查看断点位置
(gdb) continue #运行完程序或下一个断点
```

## struct

### eip
在执行一条指令的时候，eip此时代表是下一条指令的位置

```asm
global main

main:
    mov eax, 1
    mov ebx, 2
    jmp label
    add eax, ebx
label:
    ret
```

```asm
global main

main:
    mov eax, 1
    cmp eax, 100
    jle label            ; 小于等于时跳转
    sub eax, 20
label:
    ret
```

####　if-else demo

```c
int main()
{
    register int grade = 80; //register 变量放入寄存器中
    register int level;

    if (grade >= 85) {
        level = 1;
    } else if ( grade >= 70) {
        level = 2;
    } else {
        level = 3;
    }
    return level;
}

```

### eflags
> 标志寄存器，cmp指令实际上是在对两个操作数进行减法，减法后的一些状态最终就会反映到eflags寄存器中。

### while

```asm
global main

main:
    mov eax, 0
    mov ebx, 1

_start:
    cmp ebx, 10
    jg _end_of_block

    add eax, ebx
    add ebx, 1
    jmp _start

_end_of_block:
    ret
```

## function

```asm
global main

eax_plus_1s:
    add eax, 1
    ret

ebx_plus_1s:
    add ebx, 1
    ret

main:
    mov eax, 0
    mov ebx, 0
    call eax_plus_1s
    call eax_plus_1s
    call ebx_plus_1s
    add eax, ebx
    ret
```

### esp
> ( stack pointer ) 栈顶top是由esp记录的。在x86环境中，栈是朝低地址方向延伸的。


> push eax, pop ebx