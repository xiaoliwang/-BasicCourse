# Bit Operation
该文档包含一系列二进制操作,前两题为二进制位的计数，第三题为二进制的反转操作。

[TOC]

## [Number of 1 Bits][1]
> Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).  
> For example, the 32-bit integer ’11' has binary representation `00000000000000000000000000001011`, so the function should return 3.

这是一道非常简单的题目，下面我用两种方法来解答。一种是从最左边开始计数，碰到1就技术加1，碰到0则不做任何操作。代码如下：

```js
/**
 * @param {number} n - a positive integer
 * @return {number}
 */
var hammingWeight = function(n) {
    var numbers = 0;
    while(n) {
        numbers += (n & 1);
        n >>>= 1;
    }
    return numbers;
};
```

另一种是每次减少一个1，其代码关键在于`n &= n - 1`,这样每次接可以消除最右边的那一位1，更快的得到1的个数。代码如下:

```js
/**
 * @param {number} n - a positive integer
 * @return {number}
 */
var hammingWeight = function(n) {
    var numbers = 0;
    while(n) {
        n &= n - 1;
       ++numbers;
    }
    return numbers;
};
```

## [Countings Bits][2]
> Given a non negative integer number `num`. For every numbers **i** in the range **0 ≤ i ≤ num** calculate the number of 1's in their binary representation and return them as an array.  
> **Example:**  
>  or `num = 5 you` should return `[0,1,1,2,1,2]`.

这道题的难点在于，要求空间和时间复杂度都为`O(n)`。也就是`n`的bits数量只跟比`n`小的数量相关。这道题其实思路很简单，`n`与`2n`所具有的1的数量相同，以`4 bits`的数为例，`2`可以表示成`0010`,而他的倍数`4`相当于右移一位，即`0100`。他们所具有的1的数量是相同的。这样我们就解决了所有2倍数的情况。但是还有一类数不能被2整除，例如`3`。他们其实就是将`1`右移后再加上1。所以结果如下：

```js
/**
 * @param {number} num
 * @return {number[]}
 */
var countBits = function(num) {
    var numbers = new Array(num + 1).fill(0);
    for (var i = 0; i <= num; ++i) {
        numbers[i] = numbers[i >> 1] + i % 2;
    }
    return numbers;
};
```


## [Reverse Bits][3]
> Reverse bits of a given 32 bits unsigned integer.

这道题对于js实现有个难点，就是如何把`integer`转换成`unsigned integer`。这里有个非常实用的方法，就是使用无符号右移`>>>`。回到这道题本身，一个比较好想到的方法就是直接便利每一位，然后从另一个方向进行生成。代码如下：

```js
/**
 * @param {number} n - a positive integer
 * @return {number} - a positive integer
 */
var reverseBits = function(n) {
    var reverse_number = 0;
    for (var i = 0; i < 32; ++i) {
        if (n & (1 << i)) {
            reverse_number |= (1 << 31 - i);
        }
    }
    return reverse_number >>> 0;
};
```

另外一种想法则是分段进行翻转。思路如下`abcdefgh -> efghabcd -> ghefcdab -> hgfedcba`。代码如下：
```js
var reverseBits = function(n) {
    var overflow = n & 1;
    n = (n >>> 16) | (n << 16);
    n = ((n & 0xff00ff00) >>> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >>> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >>> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >>> 1) | ((n & 0x55555555) << 1);
    return n >>> 0;
};
```

<!--links-->
[1]: https://leetcode.com/problems/number-of-1-bits/
[2]: https://leetcode.com/problems/counting-bits/
[3]: https://leetcode.com/problems/reverse-bits/