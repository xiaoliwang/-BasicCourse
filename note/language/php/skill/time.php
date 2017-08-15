<?php
// http://php.net/manual/en/datetime.formats.relative.php
// 明天午夜的时间戳
$time = strtotime('tomorrow');
echo $time, "\n";

// 上周天午夜时间
$time = strtotime('-1 Sunday');
echo $time;