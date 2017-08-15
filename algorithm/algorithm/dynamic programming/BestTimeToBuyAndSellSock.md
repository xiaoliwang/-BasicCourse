# Best Time to Buy and Sell Stock
该文档包含5个买卖股票的例子，难度不断加深。通过该例子可以更好的理解动态规划(dynamic programming)[^dynamic programming]的使用。

[TOC]

## [Best Time to Buy and Sell Stock][1]

> Say you have an array for which the ith element is the price of a given stock on day i.  
> If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

题目大意是说有一个数组标出了股票每天的价格，你只被同意买和卖一次。求最大利润。这是一道典型的动态规划，一维动态规划。对于这道题来说，有两个条件对我们来说非常重要，一个是当前的最大利润，一个是到现在为止的最低买入价(因为这个可以决定之后的最大利润)。得到结果如下：

```js
/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    var maxProfit = 0;
    var minPrice = Infinity;
    for (var price of prices) {
        minPrice = Math.min(minPrice, price);
        maxProfit = Math.max(maxProfit, price - minPrice);
    }
    return maxProfit;
};
```

## [Best Time to Buy and Sell Stock II][2]
> Say you have an array for which the ith element is the price of a given stock on day i.  
> Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

跟第一题的区别在于可以尽量多的进行交易，但是只能在卖出后再买入。这道题其实很容易。因为可以买卖无限多次，那么我们只要确保现在是赚钱的情况，我们就一直持有，一旦发现第二天会跌，我们就卖出，第二天再买入。这样就可以轻易的得到下面的答案：

```js
/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    var total = 0;
    var len = prices.length;
    for (var i = 0; i < len; ++i) {
        if (prices[i + 1] > prices[i]) {
            total += prices[i + 1] - prices[i];
        }
    }
    return total;
};
```

## [Best Time to Buy and Sell Stock III][3]
> Say you have an array for which the ith element is the price of a given stock on day i.  
> Design an algorithm to find the maximum profit. You may complete at most two transactions.

这道题的买卖次数被限制在两次

```js
/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    var m
};
```

<!-- links -->
[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
[2]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
[3]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

<!-- comments -->
[^dynamic programming]: 动态规划是利用存储历史信息使得未来需要历史信息时，不需要重新计算，从而降低时间复杂度的算法
