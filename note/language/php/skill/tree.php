<?php
/**
 * $item = ['pid' => 1, 'value' => 123];
 */
function generateTree($items)
{
    $tree = [];
    foreach ($items as $item) {
        if (isset($items[$item['pid']])) {
            $items[$item['pid']]['son'][] = &$items[$item['pid']];
        } else {
            $tree[] = &$items[$item['pid']];
        }
    }
    return tree;
}
// 改进算法
function generateTreeExt($items)
{
    foreach ($items as $item) {
        $items[$item['pid']]['son'][$item['id']] = &$items[$item['pid']];
    }
    return $items[0]['son'] ?? [];
}