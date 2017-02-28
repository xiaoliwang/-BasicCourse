### php目录结构

build
> 编译相关文件
ext
> 官方扩展
main
> PHP 核心文件，实现PHP的基础设施
Zend
> PHP 引擎实现，语法解析，opcode执行及扩展实现机制
<!-- pear -->
sapi
> 服务器抽象层
TSRM
> 线程安全
tests
> PHP测试代码
win32
> windows平台相关实现

### c语言简单介绍
`##`被称为连接符(concatenator).用来将两个语言token组合成单个语言符号。双井号不能作为第一个或最后一个元素存在。 

`#`是一种预处理运算符，它的功能是将后面的宏参数进行"字符串操作"。简单的说就是对它所引用的宏变量通过替换后加上双引号。

`do{}while(0)`来处理宏定义多条语句情况

> gcc -E 可以输出替换宏之后的文本


``` c
PHP_MINIT_FUNCTION(myphpextension)
{
    // 注册常量或者类等初始化操作
    return SUCCESS;
}

PHP_RINIT_FUNCTION(myphpextension)
{
    // 例如记录请求开始时间
    // 随后在请求结束的时候记录结束时间。这样我们就能够记录下处理请求所花费的时间了
    return SUCCESS; 
}

// 使用exit(),die() PHP将调用RSHUTDOWN当请求结束时，MSHUTDOWN当sapi结束时

PHP_RSHUTDOWN_FUNCTION(myphpextension)
{
    // 例如记录请求结束时间，并把相应的信息写入到日至文件中。
    return SUCCESS; 
}

```

### 单进程
