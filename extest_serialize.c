/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 2013-2016 Jakub Zelenka                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Jakub Zelenka <bukka@php.net>                                |
   +----------------------------------------------------------------------+
*/

#include "php.h"
#include "php_extest.h"

#if PHP_EXTEST_SERIALIZE

#include "php_extest_serialize.h"
#include "ext/standard/php_smart_str.h"
#include "ext/standard/php_var.h"



#define EXTEST_NUM_EXAMS 7

typedef struct {
	zend_object zo;
	HashTable *props;
	int exam;
} extest_serialize_object;

ZEND_BEGIN_ARG_INFO(arginfo_extest_serialize_exam, 0)
ZEND_ARG_INFO(0, exam)
ZEND_END_ARG_INFO()

static const zend_function_entry extest_serialize_methods[] = {
	PHP_ME(ExtestSerialize, __construct,   arginfo_extest_serialize_exam,  ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(ExtestSerialize, setExam,       arginfo_extest_serialize_exam,  ZEND_ACC_PUBLIC)
	PHP_ME(ExtestSerialize, getExam,       NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestSerialize, setGlobalExam, arginfo_extest_serialize_exam,  ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	PHP_ME(ExtestSerialize, getGlobalExam, NULL,                           ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_EXTEST_API zend_class_entry *extest_serialize_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_static_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_dynamic_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_custom_ce;

/* object handlers */
static zend_object_handlers extest_serialize_object_handlers;
static zend_object_handlers extest_serialize_static_object_handlers;
static zend_object_handlers extest_serialize_dynamic_object_handlers;
static zend_object_handlers extest_serialize_custom_object_handlers;

/* {{{ extest_serialize_object_free */
static void extest_serialize_object_free(zend_object *object TSRMLS_DC)
{
	extest_serialize_object *intern = (extest_serialize_object *) object;
	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ extest_serialize_object_create_ex */
static zend_object_value extest_serialize_object_create_ex(zend_class_entry *class_type, extest_serialize_object **ptr TSRMLS_DC)
{
	zend_object_value retval;
	extest_serialize_object *intern;

	/* Allocate memory for it */
	intern = (extest_serialize_object *) emalloc(sizeof(extest_serialize_object));
	memset(intern, 0, sizeof(extest_serialize_object));
	if (ptr) {
		*ptr = intern;
	}
	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);

	if (class_type == extest_serialize_static_ce) {
		retval.handlers = &extest_serialize_static_object_handlers;
	} else if (class_type == extest_serialize_dynamic_ce) {
		retval.handlers = &extest_serialize_dynamic_object_handlers;
	} else if (class_type == extest_serialize_custom_ce) {
		retval.handlers = &extest_serialize_custom_object_handlers;
	} else {
		retval.handlers = &extest_serialize_object_handlers;
	}

	retval.handle = zend_objects_store_put(
		intern,
		(zend_objects_store_dtor_t) zend_objects_destroy_object,
		(zend_objects_free_object_storage_t) extest_serialize_object_free,
		NULL TSRMLS_CC);

	return retval;
}
/* }}} */

/* {{{ extest_serialize_object_create */
static zend_object_value extest_serialize_object_create(zend_class_entry *class_type TSRMLS_DC)
{
	return extest_serialize_object_create_ex(class_type, NULL TSRMLS_CC);
}
/* }}} */

/* {{{ extest_serialize_object_clone */
static zend_object_value extest_serialize_object_clone(zval *this_ptr TSRMLS_DC)
{
	extest_serialize_object *new_obj = NULL;
	extest_serialize_object *old_obj = (extest_serialize_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = extest_serialize_object_create_ex(old_obj->zo.ce, &new_obj TSRMLS_CC);

	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);

	return new_ov;
}
/* }}} */

/* {{{ extest_serialize_propset_long */
static inline void extest_serialize_propset_bool_ex(const char *key, int value, HashTable *ht) {
	zval *tmp;
	MAKE_STD_ZVAL(tmp);
	ZVAL_BOOL(tmp, value);
	zend_hash_update(ht, key, strlen(key) + 1, (void *) &tmp, sizeof(zval *), NULL);
}
/* }}} */

/* {{{ extest_serialize_propset_long */
static inline void extest_serialize_propset_long_ex(const char *key, long value, HashTable *ht) {
	zval *tmp;
	MAKE_STD_ZVAL(tmp);
	ZVAL_LONG(tmp, value);
	zend_hash_update(ht, key, strlen(key) + 1, (void *) &tmp, sizeof(zval *), NULL);
}
/* }}} */

/* {{{ extest_serialize_propset_double */
static inline void extest_serialize_propset_double_ex(const char *key, double value, HashTable *ht) {
	zval *tmp;
	MAKE_STD_ZVAL(tmp);
	ZVAL_DOUBLE(tmp, value);
	zend_hash_update(ht, key, strlen(key) + 1, (void *) &tmp, sizeof(zval *), NULL);
}
/* }}} */

/* {{{ extest_serialize_propset_string */
static inline void extest_serialize_propset_string_ex(const char *key, char *value, HashTable *ht) {
	zval *tmp;
	MAKE_STD_ZVAL(tmp);
	ZVAL_STRING(tmp, value, 1);
	zend_hash_update(ht, key, strlen(key) + 1, (void *) &tmp, sizeof(zval *), NULL);
}
/* }}} */

/* macros allowing passing of zend_object */
#define extest_serialize_propset_bool(key, value, zo) extest_serialize_propset_bool_ex(key, value, zo->properties)
#define extest_serialize_propset_long(key, value, zo) extest_serialize_propset_long_ex(key, value, zo->properties)
#define extest_serialize_propset_double(key, value, zo) extest_serialize_propset_double_ex(key, value, zo->properties)
#define extest_serialize_propset_string(key, value, zo) extest_serialize_propset_string_ex(key, value, zo->properties)


/* {{{ extest_serialize_set_properties */
static void extest_serialize_set_properties(zend_object *zo, int exam, int destroy)
{
	if (destroy || !zo->properties) {
		if (zo->properties) {
			zend_hash_destroy(zo->properties);
		} else {
			ALLOC_HASHTABLE(zo->properties);
		}
		zend_hash_init(zo->properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	}

	switch (exam) {
		case 0:
			break;

		case 1:
			extest_serialize_propset_string("key1", "value1", zo);
			extest_serialize_propset_string("key2", "value2", zo);
			extest_serialize_propset_string("key3", "value3", zo);
			extest_serialize_propset_string("key4", "value4", zo);
			extest_serialize_propset_string("key5", "value5", zo);
			break;

		case 2:
			extest_serialize_propset_bool("key1", 1, zo);
			extest_serialize_propset_long("key2", 2, zo);
			extest_serialize_propset_long("key3", 3, zo);
			extest_serialize_propset_long("key4", 4, zo);
			extest_serialize_propset_long("key5", -5, zo);
			break;

		case 3:
			extest_serialize_propset_double("key1", 1.1, zo);
			extest_serialize_propset_double("key2", 1.2, zo);
			extest_serialize_propset_double("key3", -1.3, zo);
			break;

		case 4:
		case 6:
			extest_serialize_propset_string("zstring", "test", zo);
			extest_serialize_propset_bool("zbool", 1, zo);
			extest_serialize_propset_long("zlong", 23, zo);
			extest_serialize_propset_double("zdouble", 23.23, zo);
			break;

		case 5:
			{
				zval *parray;
				MAKE_STD_ZVAL(parray);
				/* init array */
				ALLOC_HASHTABLE(Z_ARRVAL_P(parray));
				zend_hash_init(Z_ARRVAL_P(parray), 0, NULL, ZVAL_PTR_DTOR, 0);
				Z_TYPE_P(parray) = IS_ARRAY;
				/* set values */
				add_next_index_bool(parray, 1);
				add_next_index_long(parray, 23);
				add_next_index_double(parray, 23.23);
				add_next_index_string(parray, "test", 1);
				/* save to props */
				zend_hash_update(zo->properties, "zarray", sizeof("zarray"), (void *) &parray, sizeof(zval *), NULL);
			}
			break;
	}

}
/* }}} */

/* {{{ extest_serialize_get_properties */
static HashTable *extest_serialize_get_properties(zval *object TSRMLS_DC)
{
	extest_serialize_object *intern = (extest_serialize_object *) zend_object_store_get_object(object TSRMLS_CC);
	extest_serialize_set_properties(&intern->zo, intern->exam, 0);
	return intern->zo.properties;
}
/* }}} */

/* {{{ extest_serialize_custom_callback */
static int extest_serialize_custom_callback(zval *object, unsigned char **buffer, zend_uint *buf_len, zend_serialize_data *data TSRMLS_DC)
{
	extest_serialize_object *intern = (extest_serialize_object *) zend_object_store_get_object(object TSRMLS_CC);
	smart_str buf = {0};

	switch (intern->exam) {
		case 0:
			/* empty */
			php_var_serialize_object_start(&buf, object, 0 TSRMLS_CC);
			php_var_serialize_object_end(&buf);
			break;

		case 1:
			/* string properties */
			php_var_serialize_object_start(&buf, object, 5 TSRMLS_CC);
			php_var_serialize_property_string(&buf, "key1", "value1");
			php_var_serialize_property_string(&buf, "key2", "value2");
			php_var_serialize_property_stringl(&buf, "key3", "value3x", sizeof("value3x")-1);
			php_var_serialize_property_string(&buf, "key4", "value4");
			php_var_serialize_property_string(&buf, "key5", "value5");
			php_var_serialize_object_end(&buf);
			break;

		case 2:
			/* int and bool properties */
			php_var_serialize_object_start(&buf, object, 5 TSRMLS_CC);
			php_var_serialize_property_bool(&buf, "key1", 1);
			php_var_serialize_property_long(&buf, "key2", 2);
			php_var_serialize_property_long(&buf, "key3", 3);
			php_var_serialize_property_long(&buf, "key4", 4);
			php_var_serialize_property_long(&buf, "key5", -5);
			php_var_serialize_object_end(&buf);
			break;

		case 3:
			/* double properties */
			php_var_serialize_object_start(&buf, object, 3 TSRMLS_CC);
			php_var_serialize_property_double(&buf, "key1", 1.1 TSRMLS_CC);
			php_var_serialize_property_double(&buf, "key2", 1.2 TSRMLS_CC);
			php_var_serialize_property_double(&buf, "key3", -1.3 TSRMLS_CC);
			php_var_serialize_object_end(&buf);
			break;

		case 4:
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
			break;

		case 5:
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
			break;

		case 6:
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
			break;
	}

	smart_str_0(&buf);
	*buffer = (unsigned char *) buf.c;
	*buf_len = buf.len;

	return PHP_SERIALIZE_OBJECT;
}
/* }}} */

/* {{{ extest_unserialize_dump_property */
static void extest_unserialize_dump_property(zval *key, zval *value TSRMLS_DC) {
	php_printf("Key: %s; Value: ", Z_STRVAL_P(key));
	zend_print_zval_r(value, 0 TSRMLS_CC);
	php_printf("\n");
	zval_dtor(key);
	zval_dtor(value);
}
/* }}} */

/* {{{ extest_unserialize_custom_callback */
static int extest_unserialize_custom_callback(zval **object, zend_class_entry *ce, const unsigned char *buf, zend_uint buf_len, zend_unserialize_data *data TSRMLS_DC)
{
	zval key, value;

	if (EXTEST_G(exam) == 6) {
		/* use array for easy printing */
		zval array;
		int rc;
		/* init array */
		ALLOC_HASHTABLE(Z_ARRVAL(array));
		zend_hash_init(Z_ARRVAL(array), 4, NULL, ZVAL_PTR_DTOR, 0);
		Z_TYPE(array) = IS_ARRAY;
		/* unserialize HashTable */
		if (php_var_unserialize_properties(Z_ARRVAL(array), &buf, &buf_len, data TSRMLS_CC)) {
			zend_print_zval_r(&array, 0 TSRMLS_CC);
			rc = (int) buf_len;
		} else {
			rc = -1;
		}
		zend_hash_destroy(Z_ARRVAL(array));
		FREE_HASHTABLE(Z_ARRVAL(array));
		return rc;
	}

	while (php_var_unserialize_has_properties(buf, buf_len))
	{
		if (php_var_unserialize_property(&key, &value, &buf, &buf_len, data TSRMLS_CC)) {
			extest_unserialize_dump_property(&key, &value TSRMLS_CC);
		} else {
			return -1;
		}
	}

	return (int) buf_len;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_serialize)
{
	zend_class_entry ce;

	/* reset exam */
	EXTEST_G(exam) = 0;

	/* Default serialization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerialize", extest_serialize_methods);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_ce = zend_register_internal_class(&ce TSRMLS_CC);

	/* Default serialization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeS", NULL);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_static_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_static_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_static_ce = zend_register_internal_class_ex(&ce, extest_serialize_ce, NULL TSRMLS_CC);

	/* Serailization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeD", NULL);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_dynamic_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_dynamic_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_dynamic_object_handlers.get_properties = extest_serialize_get_properties;
	extest_serialize_dynamic_ce = zend_register_internal_class_ex(&ce, extest_serialize_ce, NULL TSRMLS_CC);

	/* Custom serialization using new API */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeC", NULL);
	ce.create_object = extest_serialize_object_create;
	ce.serialize = extest_serialize_custom_callback;
	ce.unserialize = extest_unserialize_custom_callback;
	memcpy(&extest_serialize_custom_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_custom_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_static_ce = zend_register_internal_class_ex(&ce, extest_serialize_ce, NULL TSRMLS_CC);

	/* Number of exams */
	REGISTER_LONG_CONSTANT("EXTEST_NUM_EXAMS", EXTEST_NUM_EXAMS, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ extest_serialize_read_exam */
static int extest_serialize_read_exam(INTERNAL_FUNCTION_PARAMETERS, long default_exam)
{
	long exam = default_exam;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &exam) == FAILURE) {
		return default_exam;
	}

	if (exam < 0 || exam >= EXTEST_NUM_EXAMS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Requested exam is out of range");
		exam = default_exam;
	}

	return exam;
}
/* }}} */

/* {{{ extest_serialize_set_exam */
static int extest_serialize_set_exam(INTERNAL_FUNCTION_PARAMETERS)
{
	extest_serialize_object *intern;
	long exam = extest_serialize_read_exam(INTERNAL_FUNCTION_PARAM_PASSTHRU, EXTEST_G(exam));

	intern = (extest_serialize_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	intern->exam = exam;
	extest_serialize_set_properties(&intern->zo, exam, 1);
	return SUCCESS;
}
/* }}} */


/* {{{ proto ExtestSerialize::__construct(int exam)
   ExtestSerialize constructor */
PHP_METHOD(ExtestSerialize, __construct)
{
	extest_serialize_set_exam(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void ExtestSerialize::setExam(int exam)
   Sets exam */
PHP_METHOD(ExtestSerialize, setExam)
{
	RETURN_BOOL(extest_serialize_set_exam(INTERNAL_FUNCTION_PARAM_PASSTHRU) == SUCCESS);
}
/* }}} */

/* {{{ proto int ExtestSerialize::getExam()
   Returns exam */
PHP_METHOD(ExtestSerialize, getExam)
{
	extest_serialize_object *intern = (extest_serialize_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	RETURN_LONG(intern->exam);
}
/* }}} */

/* {{{ proto void ExtestSerialize::setGlobalExam(int exam)
   Sets global exam */
PHP_METHOD(ExtestSerialize, setGlobalExam)
{
	EXTEST_G(exam) = extest_serialize_read_exam(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto int ExtestSerialize::getExam()
   Returns global exam */
PHP_METHOD(ExtestSerialize, getGlobalExam)
{
	RETURN_LONG(EXTEST_G(exam));
}
/* }}} */

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
