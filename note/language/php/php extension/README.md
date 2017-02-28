### PHP Core

**the Zend Engine(ZE)**
> ZE handles parsing a human-readable script into machine-readable tokens  
> Ze also handles memory management, variable scope, and dispatching function calls

**SAPI(Server Application Programming Interfase)**

### Lifecycles
start up subsystems

**Module Initialization routine** (MINIT)

**Request Initialization** (RINIT)

once the request is initialized, PHP script -> tokens -> opcodes

**Request Shutdown** (RSHUTDOWN)

**Module Shutdown** (MSHUTDOWN)

shut down subsystems

### Memory Allocation

- persistent allocation (longer than a single page request)
- non-persistent allocation (freed at the end of the request)

\* emalloc(1234) is the same as pemalloc(1234, 0)





### configuration file


### header file

containing references used by PHP to load your extension

### source file

used by phpize to prepare your extension for compiling




PHP_FE:function_entry struct

a complementary `ORIG` get the origin value in php.ini before being altered by .htaccess or `ini_set()` statements

TSRM(Thread Safe Resource Management) ZTS(Zend Thread Safety)

the structure of a zval:
```c
// php 5.6
struct {
    union {
        long lval;
        double dval;
        struct {
            char *val;
            int len;
        } str;
        HashTable *ht;
        zend_object_value obj;
    } value;
    zend_uint refcount;
    zend_uchar type;
    zend_uchar is_ref;
} zval;

// phpng
struct _zval_struct {
    zend_value        value;            /* value */
    union {
        struct {
            ZEND_ENDIAN_LOHI_4(
                zend_uchar    type,         /* active type */
                zend_uchar    type_flags,
                zend_uchar    const_flags,
                zend_uchar    reserved)     /* various IS_VAR flags */
        } v;
        zend_uint type_info;
    } u1;
    union {
        zend_uint     var_flags;
        zend_uint     next;                 /* hash collision chain */
        zend_uint     str_offset;           /* string offset */
        zend_uint     cache_slot;           /* literal cache slot */
    } u2;
};
```