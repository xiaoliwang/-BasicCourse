#!/usr/bin/php
<?php
// 该文件用于压缩
$this_month = date('Ym');
$dir = __DIR__;

$logs = glob($dir . '/*.log', GLOB_BRACE);

$months = array_unique(array_map(function($log){
    return substr(basename($log), 0, 6);
}, $logs));

if ($key = array_search($this_month, $months)) {
    unset($months[$key]);
}

if (!$months) return;

foreach($months as $month) {
    chdir($dir);
    mkdir($month);
    echo `cp -r ${month}*log ${month}`;
    echo `tar cJf {$month}.tar.xz ${month}`;
    echo `rm -rf ./{$month}`;
    echo `rm -rf ${month}*log`;
}