/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var moveZeroes = function(nums) {
    var len = nums.length;
	var j = 0;
    for (var i = 0; i < len; ++i) {
		if (nums[i]) {
			nums[j++] = nums[i];
		}
	}
	for (j ; j < len; ++j) {
		nums[j] = 0;
	}
};

var a = moveZeroes([0, 1, 0, 3, 12]);
console.log(a);