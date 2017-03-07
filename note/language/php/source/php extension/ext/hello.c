#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#include "php_hello.h"

// instantiate the zend_hello_globals
ZEND_DECLARE_MODULE_GLOBALS(hello)

static zend_function_entry hello_functions[] = {
    PHP_FE(hello_world, NULL)
    PHP_FE(hello_world_test, NULL)
    PHP_FE(hello_world_greeting, NULL)
    PHP_FE(hello_long, NULL)
    PHP_FE(hello_long2, NULL)
    PHP_FE(hello_long3, NULL)
    PHP_FE(hello_longer, NULL)
    PHP_FE(hello_longer_direction, NULL)
    PHP_FE(hello_double, NULL)
    PHP_FE(hello_bool, NULL)
    PHP_FE(hello_null, NULL)
    PHP_FE(hello_true, NULL)
    PHP_FE(hello_false, NULL)
    PHP_FE(hello_greetme, NULL)
    PHP_FE(hello_greetme2, NULL)
    PHP_FE(hello_greetme3, NULL)
    PHP_FE(hello_add, NULL)
    PHP_FE(hello_dump, NULL)
    PHP_FE(hello_array, NULL)
    PHP_FE(hello_array_strings, NULL)
    PHP_FE(hello_array_strings2, NULL)
    PHP_FE(hello_array_walk, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry hello_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_HELLO_WORLD_EXTNAME,
    hello_functions,
    PHP_MINIT(hello),
    PHP_MSHUTDOWN(hello),
    PHP_RINIT(hello),
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_HELLO_WORLD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(hello)
#endif

PHP_INI_BEGIN()
/**
 * @param1 [string] the name of the entry in php.ini
 * @param2 [string] initial value
 * @param3 [bitmask] access mode modifier
 *     PHP_INI_ALL value may be changed anywhere
 *     PHP_INI_SYSTEM|PHP_INI_PERDIR value may be changed in the php.ini or .htacess
 *     PHP_INI_SYSTEM value only be changed in the php.ini
 * @para4 callback
 *
 */
PHP_INI_ENTRY("hello.greeting", "Hello World", PHP_INI_ALL, NULL)

//1. OnUpdateBool will automatically convert any value provided in 
//   php.ini, .htaccess or ini_set()
//2. The last three parameters of 
STD_PHP_INI_ENTRY("hello.direction", "1", PHP_INI_ALL,
    OnUpdateBool, direction, zend_hello_globals, hello_globals)
PHP_INI_END()

// only called when a new process or thread is started
static void php_hello_init_globals(zend_hello_globals *hello_globals)
{
    hello_globals->direction = 1;
}

PHP_RINIT_FUNCTION(hello)
{
    HELLO_G(counter) = 0;
    return SUCCESS;
}

PHP_MINIT_FUNCTION(hello)
{
    ZEND_INIT_MODULE_GLOBALS(hello, php_hello_init_globals, NULL);
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(hello)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

//real code
PHP_FUNCTION(hello_world)
{
    RETURN_STRING("Hello World");
}

PHP_FUNCTION(hello_world_test)
{
    char *str;
    str = estrdup("Hello world ha");
    RETURN_STRING(str);
}

PHP_FUNCTION(hello_world_greeting)
{
    RETURN_STRING(INI_STR("hello.greeting"));
}

PHP_FUNCTION(hello_long)
{
    RETURN_LONG(42);
}

PHP_FUNCTION(hello_long2)
{
    RETVAL_LONG(42);
    return;
}

PHP_FUNCTION(hello_long3)
{
    ZVAL_LONG(return_value, 42);
    return;
}

PHP_FUNCTION(hello_longer)
{
    HELLO_G(counter)++;
    RETURN_LONG(HELLO_G(counter));
}

PHP_FUNCTION(hello_longer_direction)
{
    if (HELLO_G(direction)) {
        HELLO_G(counter)++;
    } else {
        HELLO_G(counter)--;
    }
    RETURN_LONG(HELLO_G(counter));
}

PHP_FUNCTION(hello_double)
{
    RETURN_DOUBLE(3.1415926535);
}

PHP_FUNCTION(hello_bool)
{
    RETURN_BOOL(1);
}

PHP_FUNCTION(hello_null)
{
    RETURN_NULL();
}

PHP_FUNCTION(hello_true)
{
    RETURN_TRUE;
}

PHP_FUNCTION(hello_false)
{
    RETURN_FALSE;
}

PHP_FUNCTION(hello_greetme)
{
    char *name;
    size_t name_len;
    // "s" to indicate that this function expects one
    // and only one parameter to be passed and that parameter 
    // should be converted into a string
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", 
        &name, &name_len) == FAILURE) {
        RETURN_NULL();
    }

    php_printf("Hello ");
    PHPWRITE(name, name_len);
    php_printf("\n");
    RETURN_TRUE;
}

PHP_FUNCTION(hello_greetme2)
{
    zend_string *name;
    // "s" to indicate that this function expects one
    // and only one parameter to be passed and that parameter 
    // should be converted into a string
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S", 
        &name) == FAILURE) {
        RETURN_NULL();
    }

    php_printf("Hello %s\n", name->val);
    RETURN_TRUE;
}

PHP_FUNCTION(hello_greetme3)
{
    zval *zname;
    // "s" to indicate that this function expects one
    // and only one parameter to be passed and that parameter 
    // should be converted into a string
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", 
        &zname) == FAILURE) {
        RETURN_NULL();
    }

    convert_to_string(zname);
    php_printf("Hello ");
    PHPWRITE(Z_STRVAL_P(zname), Z_STRLEN_P(zname));
    php_printf("\n");
    RETURN_TRUE;
}

PHP_FUNCTION(hello_add)
{
    long a;
    double b;
    zend_bool return_long = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld|b",
        &a, &b, &return_long) == FAILURE) {
        RETURN_NULL();
    }
    if (return_long) {
        RETURN_LONG(a + b);
    } else {
        RETURN_DOUBLE(a + b);
    }
}

PHP_FUNCTION(hello_dump)
{
    zval *uservar;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &uservar) == FAILURE) {
        RETURN_NULL();
    }

    switch (Z_TYPE_P(uservar)) {
        case IS_NULL:
            php_printf("NULL\n");
            break;
        case IS_TRUE:
            php_printf("Boolean: TRUE\n");
            break;
        case IS_FALSE:
            php_printf("Boolean: FALSE\n");
            break;
        case IS_LONG:
            php_printf("Long:%ld\n", Z_LVAL_P(uservar));
            break;
        case IS_DOUBLE:
            php_printf("Double: %f\n", Z_DVAL_P(uservar));
            break;
        case IS_STRING:
            php_printf("String: ");
            PHPWRITE(Z_STRVAL_P(uservar), Z_STRLEN_P(uservar));
            php_printf("\n");
            break;
        case IS_RESOURCE:
            php_printf("Resource\n");
            break;
        case IS_ARRAY:
            php_printf("Array\n");
            break;
        case IS_OBJECT:
            php_printf("Object\n");
            break;
        default:
            php_printf("Unknown");
    }
    RETURN_TRUE;
}

PHP_FUNCTION(hello_array)
{
    char *mystr;
    zval mysubarray;

    array_init(return_value);
    add_index_long(return_value, 42, 123);

    add_next_index_string(return_value, "I should now be found at index 43");
    add_next_index_stringl(return_value, "I'm at 44!", 10);

    mystr = estrdup("Forty Five");
    add_next_index_string(return_value, mystr);

    add_assoc_double(return_value, "pi", 3.1415926535);

    mystr = estrdup("Forty Five");
    add_next_index_string(return_value, mystr);

    add_assoc_double(return_value, "pi", 3.1415926535);

    array_init(&mysubarray);
    add_next_index_string(&mysubarray, "hello");
    add_assoc_zval(return_value, "subarray", &mysubarray);
}

PHP_FUNCTION(hello_array_strings)
{
    HashTable *arr_hash;
    zval *arr;
    long num_key;
    zend_string *key;
    zval *val;
    zval temp;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
        RETURN_NULL();
    }

    arr_hash = Z_ARRVAL_P(arr);

    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
        //php_printf("%d\n", num_key); // 打印index
        //if (key) { // 键值为字符串时
            // convert_to_string(val); //会改变原值
            // PHPWRITE(Z_STRVAL_P(val), Z_STRLEN_P(val));
            // printf("\n");
        //}
        temp = *val;
        zval_copy_ctor(&temp); // copy additional resource
        convert_to_string(&temp); //会改变原值
        PHPWRITE(Z_STRVAL(temp), Z_STRLEN(temp));
        printf("\n");
        zval_dtor(&temp); //get rid of the resource used by copy
    } ZEND_HASH_FOREACH_END();
    RETURN_TRUE;
}

PHP_FUNCTION(hello_array_strings2)
{
    HashTable *arr_hash;
    zval *arr;
    long num_key;
    zend_string *key;
    zval *val;
    zval temp;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
        RETURN_NULL();
    }

    arr_hash = Z_ARRVAL_P(arr);

    ZEND_HASH_FOREACH_KEY_VAL(arr_hash, num_key, key, val) {
        temp = *val;
        zval_copy_ctor(&temp);
        if (key) {
            php_printf("%s", key->val);
        } else {
            php_printf("%d", num_key);
        }
        php_printf(" => ");
        convert_to_string(&temp); //会改变原值
        PHPWRITE(Z_STRVAL(temp), Z_STRLEN(temp));
        printf("\n");
        zval_dtor(&temp);
    } ZEND_HASH_FOREACH_END();
    RETURN_TRUE;
}

static int php_hello_array_walk(zval **element TSRMLS_DC)
{
    zval temp;
    temp = **element;
    zval_copy_ctor(&temp);
    convert_to_string(&temp);
    PHPWRITE(Z_STRVAL(temp), Z_STRLEN(temp));
    php_printf("\n");
    zval_dtor(&temp);

    return ZEND_HASH_APPLY_KEEP;
}

static int php_hello_array_walk_arg(zval **element, char *greeting TSRMLS_DC)
{
    php_printf("%s", greeting);
    php_hello_array_walk(element TSRMLS_CC);

    return ZEND_HASH_APPLY_KEEP;
}

static int php_hello_array_walk_args(zval **element, int num_args, va_list args, zend_hash_key *hash_key)
{
    char *prefix = va_arg(args, char*);
    char *suffix = va_arg(args, char*);
    TSRMLS_FETCH();

    php_printf("%s", prefix);
    php_hello_array_walk(element TSRMLS_CC);
    php_printf("%s\n", suffix);

    return ZEND_HASH_APPLY_KEEP;
}

PHP_FUNCTION(hello_array_walk)
{
    zval *zarray;
    int print_newline = 1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &zarray) == FAILURE) {
        RETURN_NULL();
    }

    zend_hash_apply(Z_ARRVAL_P(zarray), (apply_func_t)php_hello_array_walk TSRMLS_CC);
    zend_hash_apply_with_argument(Z_ARRVAL_P(zarray), (apply_func_arg_t)php_hello_array_walk_arg, "Hello " TSRMLS_CC);
    zend_hash_apply_with_arguments(Z_ARRVAL_P(zarray), (apply_func_args_t)php_hello_array_walk_args, 2, "Hello ", "Welcome to my extension!");

    RETURN_TRUE;
}