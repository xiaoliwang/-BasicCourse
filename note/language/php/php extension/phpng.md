# PHPNG
> the next generation of php

## Value Representation
The new implementation uses more VM stack space instead of space on heap.

##CELL Format(zval)
| value(64-bit) |
|---|---|---|---|---|
| unused(32-bit) | UNUSED | const_flags | type_flags | TYPE |
|63            32| 31   24| 23        16| 15        8| 7   0|

```c
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

data type
IS_UNDER
IS_NULL

zend_string