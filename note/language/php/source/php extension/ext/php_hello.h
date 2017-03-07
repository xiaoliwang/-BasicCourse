#ifndef PHP_HELLO_H
#define PHP_HELLO_H 1

#ifdef ZTS
#include "TSRM.h"
#endif
//ZEND_BEGIN_MODULE_GLOBALS and ZEND_END_MODULE_GLOBALS 
//create a struct named zend_hello_globals
//containg one variable of type long
ZEND_BEGIN_MODULE_GLOBALS(hello)
    long counter;
    zend_bool direction;
ZEND_END_MODULE_GLOBALS(hello)

#ifdef ZTS
#define HELLO_G(v) TSRMG(hello_globals_id, zend_hello_globals *, v)
#else
#define HELLO_G(v) (hello_globals.v)
#endif

#define PHP_HELLO_WORLD_VERSION "1.0"
#define PHP_HELLO_WORLD_EXTNAME "hello"

PHP_MINIT_FUNCTION(hello);
PHP_MSHUTDOWN_FUNCTION(hello);
PHP_RINIT_FUNCTION(hello);

PHP_FUNCTION(hello_world);
PHP_FUNCTION(hello_world_test);
PHP_FUNCTION(hello_world_greeting);
PHP_FUNCTION(hello_long);
PHP_FUNCTION(hello_long2);
PHP_FUNCTION(hello_long3);

PHP_FUNCTION(hello_longer);
PHP_FUNCTION(hello_longer_direction);
PHP_FUNCTION(hello_double);
PHP_FUNCTION(hello_bool);
PHP_FUNCTION(hello_null);
PHP_FUNCTION(hello_true);
PHP_FUNCTION(hello_false);

PHP_FUNCTION(hello_greetme);
PHP_FUNCTION(hello_greetme2);
PHP_FUNCTION(hello_greetme3);
PHP_FUNCTION(hello_add);
PHP_FUNCTION(hello_dump);

PHP_FUNCTION(hello_array);
PHP_FUNCTION(hello_array_strings);
PHP_FUNCTION(hello_array_strings2);
PHP_FUNCTION(hello_array_walk);

extern zend_module_entry hello_module_entry;
#define phpext_hello_ptr &hello_module_entry

#endif