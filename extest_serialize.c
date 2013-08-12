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

PHP_EXTEST_API zend_class_entry *extest_serialize_existing_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_virtual_ce;
PHP_EXTEST_API zend_class_entry *extest_serialize_custom_ce;


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_serialize)
{
	zend_class_entry ce;

	/* Default serialization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeReal", NULL);
	extest_serialize_existing_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zend_declare_property_null(extest_serialize_existing_ce, "algorithm", sizeof("algorithm")-1, ZEND_ACC_PUBLIC TSRMLS_CC);

	/* Serailization of object properties */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeVirtual", NULL);
	extest_serialize_existing_ce = zend_register_internal_class(&ce TSRMLS_CC);

	/* Custom serialization using new API */
	INIT_CLASS_ENTRY(ce, "ExtestSerializeCustom", NULL);
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
