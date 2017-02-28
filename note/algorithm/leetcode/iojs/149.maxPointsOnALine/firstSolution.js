/**
 * Definition for a point.
 * function Point(x, y) {
 *     this.x = x;
 *     this.y = y;
 * }
 */
/**
 * @param {Point[]} points
 * @return {number}
 */
var maxPoints = function(points) {
	var len = points.length;
	var max = 0;
	if (len < 2) {
		return max;
	}
	$start = points[0];
	$end = points[1];
	var distance = measure($start, $end);
    for (var i = 2; i < len; ++i) {
		if (distance > max) {
			
		}
	}
	
	return max;
};