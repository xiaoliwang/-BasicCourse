# 动态规划

> 动态规划是一类算法问题。它的核心思想是将一个复杂问题化简成一系列简单问题。利用各简单问题之间的关系，进行比较后，合并子问题的解以得出原问题的解。
>
> 本文参考了**TopCoder**上的一篇文章[Dynamic Programming – From Novice to Advanced](https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/)
>
> 本文所有的示例均使用 golang 编写，如有疑问，可以参考[官网](https://golang.org/)



## 入门

> 在此，我们先来看一个简单的问题。如果我们有一系列硬币，他们的面值属于集合 $V = \{V_1,V_2,V_3,...\}$ ，这时候我们需要买一个价值为 $S$ 的东西。如何可以让我们付出的硬币数量最少且恰好他们的和是 $S$ ，如若不能，则告知不能。

易知，当 $S \in V$ 时，则只需要一枚硬币即可。当 $S \not\in V$ 时，如果 $S$ 能恰好由硬币组成，则一定是由 $v  ( \forall v \in V and \ v < S  )$ 组成，且  $\exists v\  s.t. \  S-v$ 也由 $v  ( \forall v \in V and \ v < S  )$ 组成。而组成 $S$ 的最小个数则为 $min(组成S-v的个数)$ + 1。反之，则 $S$ 不可被 $V$ 中的元素组成。代码如下：

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

> 我们已经了解了动态规划的基本解题思路，现在来看一道经典的 [LIS](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)[^LIS] 例题。给定一个序列 $ S = \{s_1, s_2, s_3, ...\}$，找出该序列的最长递增子序列。



[^LIS]: Longest increasing subsequence

