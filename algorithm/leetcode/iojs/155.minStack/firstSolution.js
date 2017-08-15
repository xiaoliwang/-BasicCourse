/**
 * @constructor
 */
var MinStack = function() {
	this.value = [];
};

/**
 * @param {number} x
 * @returns {void}
 */
MinStack.prototype.push = function(x) {
	this.value.push(x);
};

/**
 * @returns {void}
 */
MinStack.prototype.pop = function() {
	this.value.pop();
};

/**
 * @returns {number}
 */
MinStack.prototype.top = function() {
	var len = this.value.length;
	return this.value[len - 1];
};

/**
 * @returns {number}
 */
MinStack.prototype.getMin = function() {

};