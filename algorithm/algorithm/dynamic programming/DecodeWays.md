# Docode Ways
该文档包含1个动态规划的例子

[TOC]

## [Best Time to Buy and Sell Stock][1]

> A message containing letters from `A-Z` is being encoded to numbers using the following mapping:
> 
> 
> 'A' -> 1  
> 'B' -> 2  
> ...  
> 'Z' -> 26
> 
> Given an encoded message containing digits, determine the total number of ways to decode it.
> 

举一个例子，当`s="123"`时，其实我们可以看成是`s="1"`和`s="12"`分别拼上`"23"`和`"3"`。这样就保证了`numD("123") = numD("12") + numD("1")`。但这里有一个前提条件，就是`"23"`和`"3"`都是合法的情况。如果数是`s="127"`,那么因为`"27"`不合法，所以`numD("127") = num("12")`。这里有一个值得注意的数`0`,他是不能单独存在的,只有`"20"`和`"10"`是合法的。只要保证`"20"`和`"10"`时，`numD("{n}") === numD("{n - 2}")`其它则为0即可。

```js
/**
 * @param {string} s
 * @return {number}
 */
var numDecodings = function(s) {
    if (!s.length) return 0;
    var pre_char = '0';
    var pre_num = 1;
    var num = 1;
    for (var char of s) {
        // 如果数不为10或者20，则num和pre_num都会变成0
        if (char === '0') num = 0;
        if (pre_char === '1' || pre_char === '2' &&  char <= '6') {
            // 这里实现的是num成为前两个的和，再将之前num的值赋给pre_num
            num = pre_num + num;
            pre_num = num - pre_num;
        } else {
            pre_num = num;
        }
        pre_char = char;
    }
    return num;
};
```

<!-- links -->
[1]: https://leetcode.com/problems/decode-ways/