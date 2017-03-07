function example(a, b) {
  // 期望a,b都为数值类型
  ++a * ++b;
};


function getExecutionTime(func, args = []) {
    var time = process.hrtime();
    for (let i = 0; i < 1000000; ++i) {
        func(...args);
    }
    var diff = process.hrtime(time);
    console.log(diff);
}

getExecutionTime(example);
getExecutionTime(example, [1, 1]);
getExecutionTime(example, ['1', 1]);
getExecutionTime(example, [1]);