/**
 * @param {number[]} nums
 * @param {number} k
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var rotate = function(nums, k) {
	var len = nums.length;
	var temp_nums = nums.slice(0);
	
	for (var i = 0; i < len; ++i) {
		nums[(i + k) % len] = temp_nums[i];
	}
};

var arr = [1, 2, 3, 4, 5, 6, 7];
rotate(arr, 1);
console.log(arr);