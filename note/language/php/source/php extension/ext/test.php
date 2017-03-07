<?php
var_dump(hello_world());
var_dump(hello_bool());
var_dump(hello_null());
var_dump(hello_true());
var_dump(hello_false());
var_dump(hello_world_greeting());
var_dump(hello_longer());
var_dump(hello_longer());
var_dump(hello_longer_direction());
ini_set('hello.direction', 0);
var_dump(hello_longer_direction());
var_dump(hello_longer_direction());

hello_greetme("TomCao");
hello_greetme2("TomCao2");
hello_greetme3("TomCao3");

var_dump(hello_add(1.1, 2));
var_dump(hello_add(1.1, 2, true));

hello_dump(null);
hello_dump(true);
hello_dump(false);

hello_dump([]);
hello_dump('hello world');
hello_dump(new stdClass);

var_dump(hello_long2());
var_dump(hello_long3());

var_dump(hello_array());

$a = [
    'ceshi' => 'ceshi',
    'hahah' => 'lalal',
    'test'
];
var_dump($a);
hello_array_strings($a);
hello_array_strings2($a);
var_dump($a);

echo "hello_array_walk\n";

hello_array_walk($a);
var_dump($a);
