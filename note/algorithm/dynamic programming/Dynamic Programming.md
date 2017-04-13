# 动态规划

> 动态规划是一类算法问题。它的核心思想是将一个复杂问题化简成一系列简单问题。再根据各简单问题的解，进行比较合并，最终得出原问题的解。
>
> 本文参考了**TopCoder**上的一篇文章[Dynamic Programming – From Novice to Advanced](https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/)
>
> 本文所有的示例均使用 golang 编写，如有疑问，可以参考[官网](https://golang.org/)
>
> 全文分为四个部分，入门，中级，高级以及附录。前面三个部分主要从浅入深介绍动态规划的解题思路。附录则主要介绍文章中的一些基础知识。希望本文能对大家有所帮助。



## 知识梳理

### 入门

首先，我们来看一个简单的问题

> 如果我们有一系列硬币，他们的面值属于集合 $V = \{v_1,v_2,v_3,...\}$ ，这时候我们需要买一个价值为 $S$ 的东西。如何可以让我们付出的硬币数量最少且恰好他们的和是 $S$ ，如若不能，则告知不能。

根据我们日常的生活经验，我们不难得出下面的想法

当 $S \in V$ 时，则只需要一枚硬币即可且硬币的价值为 $S$ 。

当 $S \not\in V$ 时，如果硬币恰好能凑出 $S$ ，则可知 $S$ 是 $v_i  ( \forall v_i \in V and \ v_i < S  )$ 的一个线性组合。由此可知 $S-v_i$ 也由 $v_j  ( \forall v_j \in V and \ v_j \le S - v_i  )$ 组成。而组成 $S$ 的最小个数一定为 $\min(组成S-v_i的硬币个数)$ + 1。反之 $S$ 不可被 $V$ 中的元素组成。

得到代码如下：

```go
func RMinCoins(sum int, face_values []int) int{
	if sum == 0 {
        return 0
    }

    min := 1 << 62 - 1 // max int
    for _, v := range face_values {
        if sum == v {
            return 1
        } else if v < sum {
            t_min := RMinCoins(sum - v, face_values) + 1
            if t_min != 1 && t_min < min {
                min = t_min
            }
        }
    }
    return min
}
```

上面的算法有很多重复计算的地方，故效率比较低。如果我们将计算结果保存下来的话，速度则会快上许多。

```go
var min_coin = make(map[int]int)

func RMinCoinsImp(sum int, face_values []int) int {
	if sum == 0 {
      return sum
	}
	min, ok := min_coin[sum]
	if ok {
		return min
	}

	min = 1 << 62 - 1
	for _, v := range face_values {
		if sum == v {
			return 1
		} else if v < sum {
			t_min := RMinCoinsImp(sum - v, face_values) + 1
			if t_min != 1 && t_min < min {
				min = t_min
			}
		}
	}
	min_coin[sum] = min
	return min
}
```



我们已经了解了动态规划的基本解题思路，现在再来看一道例题加深理解。

> 给定一个序列 $ S = (s_n)_{n \in N}\ (n_1<n_2<n_3<...)$，找出该序列的最长递增子序列 $ S' = (s_{n_j})_{n_j \in N} (n_{j-1} < n_j 且 s_{n_{j-1}} < s_{n_j})$ 的最长长度。

这是计算机中很经典的题目，被称为 [LIS](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)。解题思路与上文几乎如出一辙。具体如下：

假设 $S'$ 为不包含 $S$ 最后一个元素的子序列，$s_k$ 为 $S'$ 的最大递增子序列 $S''$ 的最后一个元素（同时也是最大元素），n 则是 $S''$ 的长度。

当 $S$ 只包含一个元素时，它的最长递增子序列就是它本身，长度为 1。

如果 $S$ 包含 n 个元素（n > 1），若 $s_n > s_k$ ，则 $S$ 的长度为 n + 1，否则长度为 n。

这里需要注意一个问题，如果同时存在多个最大递增子序列。那么我们应该取尾数 $s_k$ 最小的那一个递增子序列。

假如 $S' = ( 3, 4, 1, 2)$ ，则它同时拥有两个长度为2的最大递增子序列， (3, 5) 及 (1, 2)。如果现在 $s_n = 4$ ，如果取序列1，则 $s_k = 5 > s_n$ 则 $S$ 的最长递增序列的长度不会增加，而 (1, 2, 4) 明显是一个更长的递增子序列。

得到代码如下：

```go
var max_seq_tails = []int{}

func RLis(seq []int) int {
    length := len(seq)
    if length == 1 {
        max_seq_tails = append(max_seq_tails, seq[0])
        return 1
    }

    max_len := RLis(seq[:length - 1])
    s_n := seq[length - 1]
    s_k := (max_seq_tails)[max_len - 1]
    
    if s_n > s_k {
        max_seq_tails = append(max_seq_tails, s_n)
        return max_len + 1
        
    }

    for i, v := range max_seq_tails {
        if v >= s_n {
            (max_seq_tails)[i] = s_n
            break;
        }
    }

    return max_len
}
```



在此，大家应该对动态规划有了基本理解。其实解题思路和大家原来学的递推公式几乎如出一辙。先找到最简情况的解，再找到递推关系，最后推出我们想要的结果。上面主要采取的是一种逆向解题的方法，从最复杂的情况一步步演算到最简单的情况，最后再进行整合。因为使用到递归，代码比较简单，大家容易理解。不过既然跟递推公式相似，我们其实也是可以正向进行演算的。后面的章节，我们将为大家展现这种正向解题的技巧。其实大部分动态规划的题目都是使用正向解题来完成的。我们在 code 文件夹里，也放了上面两题的正向解题的代码。有兴趣的朋友可以尝试学习。

### 中等

在**入门**的教程中，我们接触到的题目都只有一个方向。无论是第一题的集合还是第二题的序列，我们每次都是靠增加一个元素来进行递推演算的。但是有时候我们会遇到更为复杂的情况，问题不仅只在一个方向进行变化。下面我们举一个简单的例子，进行说明

> 地上有一个大的方块，被经纬线分割成排列整齐的方格，每个方块里放着数量不等的苹果。现在，你用一个袋子，从左上角的格子开始装苹果，你每次可以移动一格，但是只能向下或者向右走。问你最多可以装走多少个苹果？

我们按照之前的思路，对这道题进行分析。为了方便我们说清问题，规定该方块长为 $i$ ，宽为 $j$ 。$B_{ij}$ 中的元素表示该坐标下苹果的数量。

我们首先构建一个矩阵 $A_{ij}$ ， $\forall a_{nm} \in A_{ij}$ 表示坐标为 $(n,m)$ 我们可以取得的苹果最大数。易知 $a_{11}$ 的最大值就是它本身。而且矩阵中的最大值一定是 $a_{ij}$ （如果不能理解的，请自行面壁）。

经过分析，容易知道 $\max(a_{nm}) = \max(a_{n, m-1},a_{n-1, m}) + b_{nm}$ ，不过需要特别注意便捷的情况。

由此得到代码如下：

```go
func MostApples(apples_matrix [][]int) int{
    height := len(apples_matrix)
    width := len(apples_matrix[0])

    most_apples := make([][]int, height)

    for i, apples := range apples_matrix {
        most_apples[i] = make([]int, len(apples))
        for j, apple := range apples {
            if i == 0 && j == 0 {
                most_apples[i][j] = apple
                continue
            } else if (i == 0) {
                most_apples[i][j] = most_apples[i][j - 1] + apple
                continue
            } else if (j == 0) {
                most_apples[i][j] = most_apples[i - 1][j] + apple
                continue
            }

            if most_apples[i][j - 1] > most_apples[i - 1][j] {
                most_apples[i][j] = most_apples[i][j - 1] + apple
            } else {
                most_apples[i][j] = most_apples[i - 1][j] + apple
            }
        }
    }
    return most_apples[height - 1][width - 1]
}
```

 

## 例题详解

下面的例题主要来自著名算法题库[leetcode](https://leetcode.com/problems/counting-bits/)。点击标题可以打开题目网址，查看题目的具体描述。

### 1. [Counting Bits](https://leetcode.com/problems/counting-bits/)

当 n 为 0 的时候，不包含任何 1 。

当 n 为偶数时，他所包含的 1 的个数一定与 $\frac{1}{2}$n 相等（相当于左移补零）。对于奇数 n ，他所包含的 1 的个数一定与 $\frac{1}{2}$n + 1 相等（相当于左移补一）。得到代码如下

```go
func countBits(num int) []int{
	nums = make([]int, num + 1)
	for i := 0; i <= num; i++ {
		nums[i] = nums[i >> 1] + i % 2
	}
	return nums
}
```



## 附录

### 数学符号介绍

$\forall$ ：表示任意。

$\exists$ ：表示存在。



[^LIS]: Longest increasing subsequence
