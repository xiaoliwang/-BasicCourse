# shell
该文档包含linux上shell的基本操作

---

[TOC]

## 基础命令

```shell
date # 显示系统当前时间
cal # 显示当月日历
```

```shell
df # 查看磁盘驱动器容量，-h可以单位格式化
free # 查看内存空间，-h可以单位格式化
```

```shell
type # 显示命令类型
which # 显示命令位置
```

```shell
help command
whatis command
man command
info command
apropos command
```

```shell
alias name='string'
unalias name
```

```shell
exit # 退出终端(terminal)对话
```



## 文件系统
### ls查看目录内容
```shell
# ls -options arguments
ls ~ /usr # 同时查看~和/usr两个文件夹
```

选项    |长选项            |含义        
--------|-----------------|-----------------------
-a      |--all            |列出所有文件，包括隐藏文件
-d      |--directory      |查看目录的信息
-l      |                 |显示为长格式
-F      |--classify       |末尾添加标识符，@表是link，/表示文件夹
-h      |--human-readable |当使用长格式输出时，使用字节数显示文件大小
-S      |                 |按文件大小降序排序
-t      |                 |按修改时间降序排序
-r      |--reverse        |以相反的顺序显示结果[^defult order]

长格式说明： 

```shell
-rw-r--r-- 1 root root    0 Apr  8 10:22 a
lrwxrwxrwx 1 root root    1 Apr  8 10:22 b -> a
drwxr-xr-x 2 root root 4096 Apr  8 10:22 temp
-rw-r--r-- 1 root root   20 Apr  8 10:21 test.php
```

-rw-r--r--    |1    |root    |root    |4096    |Apr  8 10:22    |temp
--------------|-----|--------|--------|--------|----------------|------
第一位表示类型[^file type]，后面几位表示权限|硬连接数|所有者用户名|所属用户组组名|以字节数表示文件大小|上次修改时间|文件名

### 常用命令
#### cd

```shell
cd # 工作目录切换到主目录(即～)
cd - # 回到先前工作目录
cd ~username # 切换到username的主目录
```

#### 其他
```shell
file filename # 查看文件类型
less filename # 查看文件内容，使用h可以查看说明
zless filename # 可以查看gzip压缩后的文件
mkdir directory ... # 创建文件夹
ln file link # 创建连接，使用-s可以创建软连接
cp # 复制
mv # 移动
rm # 删除
mkdir # 创建文件夹
```

### 通配符
通配符         |说明
--------------|-------------
\*            |匹配任意多个字符
?             |匹配任意一个字符
[characters]  |匹配任意一个属于字符集的字符
[!character]  |匹配任意一个不属于字符集的字符
[[:class:]]   |匹配任意一个属于指定字符集[^character class]中的字符

## 重定向
### 标准输入，标准输出，标准错误及重定向
文件|文件描述符
---|---------
stdin(standard input,标准输入)|0[^stdin]
stdout(standard output,标准输出)|1[^stdout]
stderr(standard error,标准错误)|2[^stderr]

重定向操作符`>`可以把标准输出重定向到另一个文件，重定向操作符`>>`可以追加输出。重定向操作符`<`可以重定向标准输入。`/dev/null`称为位桶(bit bucket)，可用来处理不想要的输出。

```shell
ls -l /bin/usr > ls-output.txt 2>&1 # &1为文件描述符1，即标准输出
ls -l /bin/usr &> ls-output.txt # &>标准输出和标准错误都重定向
```

### 管道
`Command1 | Command2`可以将第一个命令的标准输出传给第二个命令作为标准输入

### 常用命令

```shell
cat
sort
uniq
wc
grep pattern file
head
tail
tee #从stdin读取数据，并同时输出到stdout和文件
```


## 表达式(双引号，单引号，命题替换等未添加)
- `$((expression))`算术扩展[^calculate]。
- 花括号(brace)可以包含一个前导字符(preamble)和一个附言(postscript)。输出信息如下:

```shell
$ echo Number_{1..5}
Number_1 Number_2 Number_3 Number_4 Number_5
$ echo a{A{1,2},B{3,4}}b
aA1b aA2b aB3b aB4b
```

## 键盘技巧
### 光标操作
组合键|作用
-----|-----
`Ctrl + A`|移动光标到行首
`Ctrl + E`|移动光标到行尾
`Ctrl + F`|与右箭头效果一致
`Ctrl + B`|与左箭头效果一致
`Ctrl + L`|与clear效果一致
`Alt + F` |向左移动一个字
`Alt + B` |向右移动一个字

<!-- 注释comments -->
[^defult order]: ls默认是按字母升序排列
[^file type]: -表示文件，d表示目录，l表示连接
[^character class]: alnum 任意字母或数字，alpha任意字母，digit任意数字，lower任意小写字母，upper任意大写字母
[^stdin]: 缺省为键盘
[^stdout]: 缺省为屏幕
[^stderr]: 缺省为屏幕
[^calculate]: 算术扩展只支持整数



