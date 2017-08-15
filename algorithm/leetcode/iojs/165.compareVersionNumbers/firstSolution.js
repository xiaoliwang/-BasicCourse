/**
 * @param {string} version1
 * @param {string} version2
 * @return {number}
 */
var compareVersion = function(version1, version2) {
	var version1s = version1.split('.').map(function(item, index){
		return parseInt(item);
	});
	var version2s = version2.split('.').map(function(item, index){
		return parseInt(item);
	});
	
	var len = Math.max(version1s.length, version2s.length);
	
	for (var i = 0; i < len; ++i) {
		version2s[i] = version2s[i] || 0;
		version1s[i] = version1s[i] || 0;
		if (version1s[i] > version2s[i]) {
			return 1;
		} else if (version1s[i] < version2s[i]) {
			return -1;
		} else if (i === len - 1) {
			return 0;
		}
	}
};


var a = compareVersion('1.0', '1');
console.log(a);