# Binary Search Tree
该文档包含2个关于二叉搜索树的应用

[TOC]

## [Convert Sorted Array to Binary Search Tree][1]
> Given an array where elements are sorted in ascending order, convert it to a height balanced BST[^1].

这道题的关键在于如何将一个数组变成一颗AVL树。需要注意的是，这是一个排好序列的数组，所以我们在生成AVL树的时候，只需要使用二分法分割，就能够很容易的得到最终的结果。下面得到解法1：

```js
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {number[]} nums
 * @return {TreeNode}
 */
var sortedArrayToBST = function(nums) {
    var len = nums.length;
    if (len < 1) return null;
    var tree_root = Tree_helper(nums, 0 , len - 1);
    return tree_root;
};

var Tree_helper = function(head, low, heigh) {
    if (low > heigh) return null;
    var mid = low + ((heigh - low) >>> 1); // avoid overflow
    var temp_root = new TreeNode(head[mid]);
    temp_root.left = Tree_helper(head, low, mid - 1);
    temp_root.right = Tree_helper(head, mid + 1, heigh);
    return temp_root;
};
```

其实只要仔细观察，我们可以很容易的将下面的辅助函数也并入到主函数中，得到解法2：

```js
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {number[]} nums
 * @return {TreeNode}
 */
var sortedArrayToBST = function(nums) {
    var len = nums.length;
    if (len === 0) return null;
    if (len === 1) return new TreeNode(nums[0]);
    var mid = (len + 1) >>> 1;
    var tree_root = new TreeNode(nums[mid - 1]);
    tree_root.left = sortedArrayToBST(nums.slice(0, mid - 1));
    tree_root.right = sortedArrayToBST(nums.slice(mid));
    return tree_root;
};
```

## [Convert Sorted List to Binary Search Tree][2]
> Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

本题与上题的改动在于将数组换成了链表。这样我们将不能再利用索引找到中间值。这道题的关键在于中序遍历(inorder traversal)。代码如下:

```js
/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {ListNode} head
 * @return {TreeNode}
 */
var node;

var sortedListToBST = function(head) {
    if (!head) return null;

    var runner = head;
    node = head;
    var len = 0;
    while (runner = runner.next) {
        ++len;
    }
    return inorder(0, len);
};

var inorder = function(start, end){
    if (start > end) return null;
    var mid = start + ((end - start) >>> 1);
    var left = inorder(start, mid - 1);
    var tree_node = new TreeNode(node.val);
    tree_node.left = left;
    node = node.next;
    tree_node.right = inorder(mid + 1, end);
    return tree_node;
}
```

<!-- links -->
[1]: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
[2]: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

<!-- comments -->
[^1]: Height Balanced Binary Search Tree 又称为 AVL。是最先发明的自平衡二叉查找树。它的每个结点的左右子树的深度差不超过1。
