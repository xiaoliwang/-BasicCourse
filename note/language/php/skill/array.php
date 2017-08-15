<?php
// 在位置 i 插入数据 j
$a = [0, 1, 2, 4];
array_splice($a, 3, 0, 3);
print_r($a);