/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2013 The PHP Group                                |
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
#include "php_extest_serialize.h"

typedef struct {
	zend_object zo;
	int exam;
} extest_serialize_object;

PHP_EXTEST_API zend_class_entry *extest_serialize_existing_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_virtual_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_custom_ce;

/* object handlers */
static zend_object_handlers extest_serialize_existing_object_handlers;
static zend_object_handlers extest_serialize_virtual_object_handlers;
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
	object_properties_init(&intern->zo, class_type);

	if (class_type == extest_serialize_existing_ce) {
		retval.handlers = &extest_serialize_existing_object_handlers;
	} else if (class_type == extest_serialize_virtual_ce) {
		retval.handlers = &extest_serialize_virtual_object_handlers;
	} else {
		retval.handlers = &extest_serialize_custom_object_handlers;
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
zend_object_value extest_serialize_object_clone(zval *this_ptr TSRMLS_DC)
{
	extest_serialize_object *new_obj = NULL;
	extest_serialize_object *old_obj = (extest_serialize_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = extest_serialize_object_create_ex(old_obj->zo.ce, &new_obj TSRMLS_CC);

	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);

	return new_ov;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_serialize)
{
	zend_class_entry ce;

	/* Default serialization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeReal", NULL);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_existing_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_existing_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_existing_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zend_declare_property_null(extest_serialize_existing_ce, "algorithm", sizeof("algorithm")-1, ZEND_ACC_PUBLIC TSRMLS_CC);

	/* Serailization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeVirtual", NULL);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_virtual_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_virtual_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_existing_ce = zend_register_internal_class(&ce TSRMLS_CC);

	/* Custom serialization using new API */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeCustom", NULL);
	ce.create_object = extest_serialize_object_create;
	memcpy(&extest_serialize_custom_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	extest_serialize_custom_object_handlers.clone_obj = extest_serialize_object_clone;
	extest_serialize_existing_ce = zend_register_internal_class(&ce TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
