# Internal Serialization API test

This part of the Extest extension tests the new internal serialization API proposed in the [RFC on PHP wiki](https://wiki.php.net/rfc/internal_serialize_api) . The source of this extension part is in [extest_serialize.c](https://github.com/bukka/php-extest/blob/master/extest_serialize.c).


## Serialization

There are 7 examples with benchmarks for the serialization API. For that purpose there are defined 3 internal classes:

* STATIC: `ExtestSerializeS` - The properties are created when object is initialized. The object properties are used when object is serialized. This is for static objects that don't change their state that needs to serialized.
* DYNAMIC: `ExtestSerializeD` - The properties are regenerated every time the serialization is executed. This is usual method that is used for example in DateTime object (the first existing method described in RFC)
* CUSTOM: `ExtestSerializeC` - Serialization created with the new (code example in each exam subsection)

The following examples shows code used in `zend_class_entry` `serialize` callback (in place of the CODE comment):

```
static int extest_serialize_custom_callback(zval *object, unsigned char **buffer, zend_uint *buf_len, zend_serialize_data *data TSRMLS_DC)
{
	smart_str buf = {0};

	/* CODE */

	smart_str_0(&buf);
	*buffer = (unsigned char *) buf.c;
	*buf_len = buf.len;

	return PHP_SERIALIZE_OBJECT;
}
```

The results of running the benchmark for 100000 calling of `serialize` are bellow the example. The code for the script is available at [bench/serialize.php](https://github.com/bukka/php-extest/blob/master/bench/serialize.php). Then the short description follows.

### EXAM 0 (empty)

#### Source
```
php_var_serialize_object_start(&buf, object, 0 TSRMLS_CC);
php_var_serialize_object_end(&buf);
```

#### Result 
#### Description
In this case it wouldn't really make sense to use custom serialization. There is no point in generating string for empty object. No state is saved so it's better to use normal properties which is also slightly faster. This example is just for testing if custom serialization works correctly for empty data.

### EXAM 1 (string)

#### Source
```
php_var_serialize_object_start(&buf, object, 5 TSRMLS_CC);
php_var_serialize_property_string(&buf, "key1", "value1");
php_var_serialize_property_string(&buf, "key2", "value2");
php_var_serialize_property_stringl(&buf, "key3", "value3x", sizeof("value3x")-1);
php_var_serialize_property_string(&buf, "key4", "value4");
php_var_serialize_property_string(&buf, "key5", "value5");
php_var_serialize_object_end(&buf);
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":5:{s:4:"key1";s:6:"value1";s:4:"key2";s:6:"value2";s:4:"key3";s:6:"value3";s:4:"key4";s:6:"value4";s:4:"key5";s:6:"value5";}
time for 100000 iterations: 0.365737
DYNAMIC
O:16:"ExtestSerializeD":5:{s:4:"key1";s:6:"value1";s:4:"key2";s:6:"value2";s:4:"key3";s:6:"value3";s:4:"key4";s:6:"value4";s:4:"key5";s:6:"value5";}
time for 100000 iterations: 0.518077
CUSTOM
O:16:"ExtestSerializeC":5:{s:4:"key1";s:6:"value1";s:4:"key2";s:6:"value2";s:4:"key3";s:7:"value3x";s:4:"key4";s:6:"value4";s:4:"key5";s:6:"value5";}
time for 100000 iterations: 0.219088
```

#### Description
This example shows the main use case for the new API. String serialization is exactly what would be used in `DateTime`. The performance boost compare to dynamic is almost 150%.

### EXAM 2 (int)

#### Source
```
php_var_serialize_object_start(&buf, object, 5 TSRMLS_CC);
php_var_serialize_property_bool(&buf, "key1", 1);
php_var_serialize_property_long(&buf, "key2", 2);
php_var_serialize_property_long(&buf, "key3", 3);
php_var_serialize_property_long(&buf, "key4", 4);
php_var_serialize_property_long(&buf, "key5", -5);
php_var_serialize_object_end(&buf);
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":5:{s:4:"key1";b:1;s:4:"key2";i:2;s:4:"key3";i:3;s:4:"key4";i:4;s:4:"key5";i:-5;}
time for 100000 iterations: 0.367760
DYNAMIC
O:16:"ExtestSerializeD":5:{s:4:"key1";b:1;s:4:"key2";i:2;s:4:"key3";i:3;s:4:"key4";i:4;s:4:"key5";i:-5;}
time for 100000 iterations: 0.460683
CUSTOM
O:16:"ExtestSerializeC":5:{s:4:"key1";b:1;s:4:"key2";i:2;s:4:"key3";i:3;s:4:"key4";i:4;s:4:"key5";i:-5;}
time for 100000 iterations: 0.238169
```

#### Description
The `integer` and `boolean` serialization could be quite useful as well. It would be used in `DateTime` as well. The performance boost is about 100% compare to dynamic.

### EXAM 3 (double)

#### Source
```
php_var_serialize_object_start(&buf, object, 3 TSRMLS_CC);
php_var_serialize_property_double(&buf, "key1", 1.1 TSRMLS_CC);
php_var_serialize_property_double(&buf, "key2", 1.2 TSRMLS_CC);
php_var_serialize_property_double(&buf, "key3", -1.3 TSRMLS_CC);
php_var_serialize_object_end(&buf);
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":3:{s:4:"key1";d:1.1000000000000001;s:4:"key2";d:1.2;s:4:"key3";d:-1.3;}
time for 100000 iterations: 0.695046
DYNAMIC
O:16:"ExtestSerializeD":3:{s:4:"key1";d:1.1000000000000001;s:4:"key2";d:1.2;s:4:"key3";d:-1.3;}
time for 100000 iterations: 0.754162
CUSTOM
O:16:"ExtestSerializeC":3:{s:4:"key1";d:1.1000000000000001;s:4:"key2";d:1.2;s:4:"key3";d:-1.3;}
time for 100000 iterations: 0.583356
```

#### Description
The `double` serialization makes sometimes sense. The custom serialization is still fastest than others. However the difference is not as big as for `int` or `string`. The reason is that the most time is spent on `double` to `string` conversion. 


### EXAM 4 (zval)

#### Source
```
{
	zval value;
	php_var_serialize_object_start(&buf, object, 1 TSRMLS_CC);
	ZVAL_STRING(&value, "test", 0);
	php_var_serialize_property_zval(&buf, "zstring", &value, data TSRMLS_CC);
	ZVAL_BOOL(&value, 1);
	php_var_serialize_property_zval(&buf, "zbool", &value, data TSRMLS_CC);
	ZVAL_LONG(&value, 23);
	php_var_serialize_property_zval(&buf, "zlong", &value, data TSRMLS_CC);
	ZVAL_DOUBLE(&value, 23.23);
	php_var_serialize_property_zval(&buf, "zdouble", &value, data TSRMLS_CC);
	php_var_serialize_object_end(&buf);
}
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":4:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.491317
DYNAMIC
O:16:"ExtestSerializeD":4:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.606595
CUSTOM
O:16:"ExtestSerializeC":1:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.495575
```

#### Description
Serialization of zvals is not as useful as serialization specific types but it's still faster when used in CUSTOM serialization than in DYNAMIC serialization


### EXAM 5 (zval array)

#### Source
```
{
	zval array;
	/* init array */
	ALLOC_HASHTABLE(Z_ARRVAL(array));
	zend_hash_init(Z_ARRVAL(array), 0, NULL, ZVAL_PTR_DTOR, 0);
	Z_TYPE(array) = IS_ARRAY;
	/* set values */
	add_next_index_bool(&array, 1);
	add_next_index_long(&array, 23);
	add_next_index_double(&array, 23.23);
	add_next_index_string(&array, "test", 1);
	/* serialize */
	php_var_serialize_object_start(&buf, object, 1 TSRMLS_CC);
	php_var_serialize_property_zval(&buf, "zarray", &array, data TSRMLS_CC);
	php_var_serialize_object_end(&buf);
	/* clean up */
	zend_hash_destroy(Z_ARRVAL(array));
	FREE_HASHTABLE(Z_ARRVAL(array));
}
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":1:{s:6:"zarray";a:4:{i:0;b:1;i:1;i:23;i:2;d:23.23;i:3;s:4:"test";}}
time for 100000 iterations: 0.524991
DYNAMIC
O:16:"ExtestSerializeD":1:{s:6:"zarray";a:4:{i:0;b:1;i:1;i:23;i:2;d:23.23;i:3;s:4:"test";}}
time for 100000 iterations: 0.715717
CUSTOM
O:16:"ExtestSerializeC":1:{s:6:"zarray";a:4:{i:0;b:1;i:1;i:23;i:2;d:23.23;i:3;s:4:"test";}}
time for 100000 iterations: 0.708698
```

#### Description
This is not something particulary useful for serializing an object state. Array are usually serialized for object properties. But it's still possible to do it using new API.

### EXAM 6 (HashTable)

#### Source
```
{
	HashTable *ht;
	/* init array */
	ALLOC_HASHTABLE(ht);
	zend_hash_init(ht, 0, NULL, ZVAL_PTR_DTOR, 0);
	/* set values */
	extest_serialize_propset_string_ex("zstring", "test", ht);
	extest_serialize_propset_bool_ex("zbool", 1, ht);
	extest_serialize_propset_long_ex("zlong", 23, ht);
	extest_serialize_propset_double_ex("zdouble", 23.23, ht);
	/* serialize */
	php_var_serialize_object_start(&buf, object, 1 TSRMLS_CC);
	php_var_serialize_properties(&buf, ht, data TSRMLS_CC);
	php_var_serialize_object_end(&buf);
	/* clean up */
	zend_hash_destroy(ht);
	FREE_HASHTABLE(ht);
}
```

#### Result
```
STATIC
O:16:"ExtestSerializeS":4:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.485998
DYNAMIC
O:16:"ExtestSerializeD":4:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.603935
CUSTOM
O:16:"ExtestSerializeC":1:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
time for 100000 iterations: 0.687798
```

#### Description
This test is just to show that serialization of HashTable works. This wouldn't be a real case as HashTable would be saved in the object and the times would be different than.


## Unserialization

The unserialization depends on the specific use use cases. The following code examples just dumps the properties. To print all properties one has to now the number of properties in the object. This shouldn't be a problem because the unserialization API should be used as a counterpart of the serialization API and the author should now the number of unserialized properties though.

### Method 1: using php_var_unserialize_property
```
static int extest_unserialize_custom_callback(zval **object, zend_class_entry *ce, const unsigned char *buf, zend_uint buf_len, zend_unserialize_data *data TSRMLS_DC)
{
	n = extest_get_number_of_properties(object);

	for (i = 0; i < n; i++) {
		if (php_var_unserialize_property(&key, &value, &buf, &buf_len, data TSRMLS_CC)) {
			php_printf("Key: %s; Value: ", Z_STRVAL(key));
			zend_print_zval_r(&value, 0 TSRMLS_CC);
			php_printf("\n");
			zval_dtor(&key);
			zval_dtor(&value);
		} else {
			return -1;
		}
	}
	return (int) buf_len;
}
```

### Method 2: using php_var_unserialize_properties
```
static int extest_unserialize_custom_callback(zval **object, zend_class_entry *ce, const unsigned char *buf, zend_uint buf_len, zend_unserialize_data *data TSRMLS_DC)
{
	n = extest_get_number_of_properties(object);

	/* use array for easy printing */
	zval array;
	int rc;
	/* init array */
	ALLOC_HASHTABLE(Z_ARRVAL(array));
	zend_hash_init(Z_ARRVAL(array), n, NULL, ZVAL_PTR_DTOR, 0);
	Z_TYPE(array) = IS_ARRAY;
	/* unserialize HashTable */
	if (php_var_unserialize_properties(Z_ARRVAL(array), &buf, &buf_len, n, data TSRMLS_CC)) {
		zend_print_zval_r(&array, 0 TSRMLS_CC);
		rc = (int) buf_len;
	} else {
		rc = -1;
	}
	zend_hash_destroy(Z_ARRVAL(array));
	FREE_HASHTABLE(Z_ARRVAL(array));
	return rc;
}
```

### Results

The exams 0-5 were serialized using of Method 1 and exam 6 using Method 2. The code for the script is at [bench/unserialize.php](https://github.com/bukka/php-extest/blob/master/bench/unserialize.php)

```
---- EXAM 0 ----
Serialized: O:16:"ExtestSerializeC":0:{}
---- EXAM 1 ----
Serialized: O:16:"ExtestSerializeC":5:{s:4:"key1";s:6:"value1";s:4:"key2";s:6:"value2";s:4:"key3";s:7:"value3x";s:4:"key4";s:6:"value4";s:4:"key5";s:6:"value5";}
Key: key1; Value: value1
Key: key2; Value: value2
Key: key3; Value: value3x
Key: key4; Value: value4
Key: key5; Value: value5
---- EXAM 2 ----
Serialized: O:16:"ExtestSerializeC":5:{s:4:"key1";b:1;s:4:"key2";i:2;s:4:"key3";i:3;s:4:"key4";i:4;s:4:"key5";i:-5;}
Key: key1; Value: 1
Key: key2; Value: 2
Key: key3; Value: 3
Key: key4; Value: 4
Key: key5; Value: -5
---- EXAM 3 ----
Serialized: O:16:"ExtestSerializeC":3:{s:4:"key1";d:1.1000000000000001;s:4:"key2";d:1.2;s:4:"key3";d:-1.3;}
Key: key1; Value: 1.1
Key: key2; Value: 1.2
Key: key3; Value: -1.3
---- EXAM 4 ----
Serialized: O:16:"ExtestSerializeC":1:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
Key: zstring; Value: test
Key: zbool; Value: 1
Key: zlong; Value: 23
Key: zdouble; Value: 23.23
---- EXAM 5 ----
Serialized: O:16:"ExtestSerializeC":1:{s:6:"zarray";a:4:{i:0;b:1;i:1;i:23;i:2;d:23.23;i:3;s:4:"test";}}
Key: zarray; Value: Array
(
    [0] => 1
    [1] => 23
    [2] => 23.23
    [3] => test
)

---- EXAM 6 ----
Serialized: O:16:"ExtestSerializeC":1:{s:7:"zstring";s:4:"test";s:5:"zbool";b:1;s:5:"zlong";i:23;s:7:"zdouble";d:23.23;}
Array
(
    [zstring] => test
    [zbool] => 1
    [zlong] => 23
    [zdouble] => 23.23
)
```

