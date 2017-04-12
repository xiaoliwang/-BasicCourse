# 动态规划

> 动态规划是一类算法问题。它的核心思想是将一个复杂问题化简成一系列简单问题。利用各简单问题之间的关系，进行比较后，合并子问题的解以得出原问题的解。
>
> 本文参考了**TopCoder**上的一篇文章[Dynamic Programming – From Novice to Advanced](https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/)
>
> 本文所有的示例均使用 golang 编写，如有疑问，可以参考[官网](https://golang.org/)



## 入门

> 在此，我们先来看一个简单的问题。如果我们有一系列硬币，他们的面值属于集合 $V = \{v_1,v_2,v_3,...\}$ ，这时候我们需要买一个价值为 $S$ 的东西。如何可以让我们付出的硬币数量最少且恰好他们的和是 $S$ ，如若不能，则告知不能。

当 $S \in V$ 时，则只需要一枚硬币即可。

当 $S \not\in V$ 时，如果 $S$ 能恰好由硬币组成，则一定是由多枚 $v_i  ( \forall v_i \in V and \ v_i < S  )$ 组成。且 $S-v_i$ 也由 $v_j  ( \forall v_j \in V and \ v_j \le S - v_i  )$ 组成。而组成 $S$ 的最小个数则为 $\min(组成S-v_i的硬币个数)$ + 1。

反之，则 $S$ 不可被 $V$ 中的元素组成。

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

上面的算法有很多重复计算的地方，故效率比较低。

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

如果我们将计算结果保存下来的话，速度则会快上许多。



## 基础

> 我们已经了解了动态规划的基本解题思路，现在再来看一道例题。给定一个序列 $ S = (s_n)_{n \in N}\ (n_1<n_2<n_3<...)$，找出该序列的最长递增子序列 $ S' = (s_{n_j})_{n_j \in N} (n_{j-1} < n_j 且 s_{n_{j-1}} < s_{n_j})$ 的最长长度。这是计算机中很经典的题目，被称为 [LIS](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)[^LIS] 。

假设 $S'$ 为不包含 $S$ 最后一个元素的子序列，$s_k$ 为 $S'$ 的最大递增子序列 $S''$ 的最后一个元素——也就是最大元素，k 则是 $S''$ 的长度。

当 $S$ 只包含一个元素时，它的最长递增子序列就是它本身，长度为 1。

如果 $S$ 包含 n 个元素（n > 1），若 $s_n > s_k$ ，则 $S$ 的长度为 k + 1，否则长度为 k。

这里需要注意一个问题，如果同时有多个序列可以达到长度K，那么 $s_k$ 应该取其中最小的一个。假如 $S' = ( 3, 4, 1, 2)$ ，则它同时拥有两个长度为2的最大递增子序列， (3, 5) 及 (1, 2)。如果现在 $s_n = 4$ ，如果取序列1，则 $s_k = 5 > s_n$ 则 $S$ 的最长递增序列的长度不会增加，而 (1, 2, 4) 明显是一个更长的递增子序列。

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



[^LIS]: Longest increasing subsequence
