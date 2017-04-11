# 动态规划

> 动态规划是一类算法问题。它的核心思想是将一个复杂问题化简成一系列简单问题。利用各简单问题之间的关系，进行比较后，合并子问题的解以得出原问题的解。
>
> 本文参考了**TopCoder**上的一篇文章[Dynamic Programming – From Novice to Advanced](https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/)
>
> 本文所有的示例均使用 golang 编写，如有疑问，可以参考[官网](https://golang.org/)



## 入门

> 在此，我们先来看一个简单的问题。如果我们有一系列硬币，他们的面值属于集合 $V = \{V_1,V_2,V_3,...\}$ ，这时候我们需要买一个价值为 $S$ 的东西。如何可以让我们付出的硬币数量最少且恰好他们的和是 $S$ ，如若不能，则告知不能。
>
> 首先我们可以知道，如果 $S \in V$ ，则只需要一枚硬币就可以返回。如果 $S \not\in V$ ，则 S 只可能由 $v (v \in V and \ v < S )$ 组成。这样我们就可以把问题化成购买价值为 $S - v$ 的东西，如何可以让我们付出的硬币最少。如若有一系列 $v$ 可以达成，则选取使用硬币最少的情况，加一则是达到 $S$ 最小的情况。如若没有任何一个 $v$ 可以达成，则 $S$ 是不能被 $V$ 中的元素构成的。按照这个思路，我们得到以下代码。
>
> 该算法的效率较低，但是代码非常短小，容易理解。在code文件夹里，还有一个改进算法，有兴趣的同学可以研究一下。



示例代码如下：

```go
func RMinCoins(sum int, face_values []int) int{
    if sum == 0 {
        return 0
    }

    min := 1 << 62 - 1
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



