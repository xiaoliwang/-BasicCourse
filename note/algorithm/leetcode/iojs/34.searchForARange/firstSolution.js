/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var searchRange = function(nums, target) {
	var start = 0, end = nums.length - 1;
	while (start <= end) {
		
	}
	
	
	while (start <= end) {
		var half = Math.ceil((start + end) / 2);
		if (nums[half] > target) {
			if (half < end) {
				end = half;
				half = Math.ceil((start + end) / 2);
			} else {
				--end;
			}
		} else if (nums[half] < target) {
			if (half > start ) {
				start = half;
				half = Math.ceil((start + end) / 2);
			} else {
				++start;
			}
		} else {
			break;
		}
	}
	
	if (start >= end) {
		return [-1, -1];
	}
	console.log(start);
	console.log(end);
	console.log(half);
	return -1;
};

var re = searchRange([5,7,7,8,8,10,11,12,13], 12);
console.log(re);