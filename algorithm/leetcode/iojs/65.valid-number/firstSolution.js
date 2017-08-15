/**
 * @param {string} s
 * @return {boolean}
 */
var isNumber = function(s) {
	s = s.trim();
	if (s && s !== '.') {
		var match = s.match(/^[+-]?((\d+\.?\d*|\d*\.\d+)([eE][+-]?\d+)?)$/);
		var e = match && match[0];
		return e === s;
	} else {
		return false;
	}
};

var a = isNumber('3');
console.log(a);

//[+-]?(([0-9]*\\.?[0-9]+)|([0-9]+\\.?[0-9]*))([eE][+-]?[0-9]+)?

//[+-]?(\d*\.?\d+)|(\d+\.?\d*)([eE][+-]\d+)?