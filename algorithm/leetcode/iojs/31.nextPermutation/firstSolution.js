/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var nextPermutation = function(nums){
	var len = nums.length;
	if (len < 2) {
		return;
	}
	
	var index = len - 1;
	while (index > 0) {
		if (nums[index - 1] < nums[index])
			break;
		--index;
	}
	if (!index) {
		nums.reverse();
		return;
	}
		
	
	var val = nums[index - 1];
	var index1 = len - 1;
	while (index1 >= index) {
		if (nums[index1] > val)
			break;
		--index1;
	}
	array_swap(nums, index - 1, index1);
	reverseSubArray(nums, index, len - 1);
};

var array_swap = function(array, index1, index2){
	var val = array[index1];
	array[index1] = array[index2];
	array[index2] = val;
}

var reverseSubArray = function(array, i, j){
	while (j > i) {
		var val = array[i];
		array[i] = array[j];
		array[j] = val;
		++i; --j;
	}
}

var nums = [1];
//var nums = [1, 2, 5, 4, 1];
//var nums = [3, 2, 1];
var index = nextPermutation(nums);
console.log(index);

module.exports = nextPermutation;