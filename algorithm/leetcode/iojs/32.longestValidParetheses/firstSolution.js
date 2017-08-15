/**
 * @param {string} s
 * @return {number}
 */
var longestValidParentheses = function(s) {
	var len = s.length;
	var max = 0;
	var stack = [];
	for (var i = 0; i < len; ++i) {
		if (s[i] === '(') {
			stack.push(i);
		} else {
			if (stack) {
				if (s[stack.top()] === '(') {
					stack.pop();
				} else {
					stack.push(i);
				}
			} else {
				stack.push(i);
			}
		}
	}
	console.log(stack);
	if (!stack) {
		max = len;
	} else {
		var a = len, b = 0;
		while (stack.length) {
			b = stack.pop();
			max = Math.max(max, a - b - 1);
			a = b;
		}
		max = Math.max(max, a);
	}	
	return max;
};

Array.prototype.top = function(){
	return this[this.length - 1];
}

var a = longestValidParentheses(')))(()((');
console.log(a);
