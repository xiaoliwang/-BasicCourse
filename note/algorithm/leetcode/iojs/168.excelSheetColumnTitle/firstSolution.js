/**
 * @param {number} n
 * @return {string}
 */
var convertToTitle = function(n) {
	var T = '';
	var t;
	while (n > 0) {
		if (t = n % 26) {
			T = String.fromCharCode(64 + t) + T;
		} else {
			T = 'Z' + T;
		}
		n = Math.ceil(n / 26) - 1;
	}
    return T;
};

var a = convertToTitle(40);
console.log(a);