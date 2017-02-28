# SingleNumber
该文档包含3个寻找单一数的例子，难度不断加深。通过该例子可以更好的理解位运算(bit mainpulation)

---

[TOC]

## [Single Number][1]

>Given an array of integers, every element appears twice except for one. Find that single one.
> 
>**Note**:
>
>Your algorithm should have a linear runtime complexity. Could you implement  it without using extra memory? 

这道题目大意是说给一个仅包含整数的数组(array of integers)，除了唯一的一个元素只出现一次外，其它所有元素都会出现两次。找到这个唯一出现一次的数。但是需要注意的是，题目要求我们的时间复杂度为*线性复杂度(a linear runtime complexity)*且*不用多余的内存(without using extra memory)*。

该题的核心是要理解位运算^[^xor]。该运算具有以下三个性质：

1. 交换律：`a ^ b = b ^ a`
2. 相同的两个数进行运算返回0：`a ^ a = 0`
3. 一个数与0进行按位异或，返回该数：`a ^ 0 = a`

举个例子，对于数组[1, 1, 2, 3, 2], 对每一项进行异或操作，其值一定与[1, 1, 2, 2 ,3]相等(交换律)，且最终的结果一定是3。由此，我们可以得到以下代码：

```js
/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    var single = 0;
    var len = nums.length;
    for (var i = 0; i < len; ++i) {
        single ^= nums[i];
    }
    return single;
};
```

## [Single Number II][2]

>Given an array of integers, every element appears three times except for one. Find that single one.
>
>**Note:**
>
>Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

这道题与第一题的要求基本一致，不过将原来出现两次的条件改成了出现三次。这样就不能再简单的利用`a ^ a = 0`的性质，很快的将重复项消除。  
所以我们不能简单的把整数(Integer)再当成一个数字来看，而应该将它看成一个32位的二进制数(32 bits)操作。这样的话，我们只需要将每一位单独进行处理即可。以某一位为例，碰到1时，我们希望计数器加1；而遇到0时，则不变。由于我们希望计数为3时计数器归0。即`0->1->2->3/0`，也可以表示为`00->10->01->11/00`。由此可知，我们需要两个二进制位来存储，我们假设为`one`和`two`，且初始值都为0。

1. 对于`one`来说，我们可以得到`one = one ^ i`。如果`two === 1`，则`one = 0`。所以可以得到`one = (one ^ i) & ~two`
2. 对于`two`来说，我们可以得到`two = two ^ i`。如果`one === 1`，则`two = 0`。所以可以得到`two = (two ^ i) & ~one`。值得注意的是，这里的`one`是计算后的值，这也是为什么`two`需要在后面计算。


```js
/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    var ones = 0, twos = 0;
    var len = nums.length;
    for (var i = 0; i < len; i++){
        ones = (ones ^ nums[i]) & ~twos;
        twos = (twos ^ nums[i]) & ~ones;
    }
    return ones;
};
```

将上面的方法推广到所有元素出现5次，只有唯一的一个元素出现n次(0 < n < 5)。容易得到下面的解:

```js
/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    var ones = 0, twos = 0, threes = 0;
    var len = nums.length;
    for (var i = 0; i < len; i++){
        twos = twos ^ (nums[i] & ones);
        ones = (ones ^ nums[i]) & ~threes;
        threes = threes ^ (nums[i] & ~ones & ~twos);
    }
    // return ones & ~twos & ~threes; // n = 1;
    // return ~ones & twos & ~threes; // n = 2;
    // return ones & twos & ~threes; // n = 3;
    // return ~ones & ~twos & threes; // n = 4;
}
```

## [Single Number III][3]
> Given an array of numbers `nums`, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

此题的难点在于，如何分离两个仅仅出现一次的数。我们可以知道，这两个数一定在某一位上有不一样的值，所以对整个数组进行异或操作，得到的解肯定不为0。我们只要找到其中的某一位为1，就可以知道在这一位上，两数是不等的。这样就可以将两数分离操作，最终得到代码如下：

```js
/**
 * @param {number[]} nums
 * @return {number[]}
 */
var singleNumber = function(nums) {
    var diff = 0;
    for (var num of nums) {
        diff ^= num;
    }
    diff &= -diff; //获取两数不相等的最小位
    var rets = [0, 0];
    for (var num of nums) {
        if (num & diff) {
            rets[1] ^= num;
        } else {
            rets[0] ^= num;
        }
    }
    return rets;
};
```

<!-- links -->
[1]: https://leetcode.com/problems/single-number/
[2]: https://leetcode.com/problems/single-number-ii/
[3]: https://leetcode.com/problems/single-number-iii/

<!-- comments -->
[^xor]: 该符号为按位异或。异或，xor(exclusive or)。当a、b两个值相同时，返回0，不同时返回1。
[^xor cal]: `[1, 1, 2, 3, 2]`可以转换为`[1, 1, 2, 2, 3]`,最终得到那个唯一出现一次的数。
[^bit]: 这里的ones用来存储计数器的1位置的值，twos用来存储计数器2位置的值
