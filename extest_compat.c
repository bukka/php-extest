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
#include "php_extest_compat.h"

#include "phpc/phpc.h"

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_long, 0)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, fail)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_value, 0)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

const zend_function_entry extest_compat_functions[] = {
	PHP_FE(extest_compat_long,   arginfo_extest_compat_long)
	PHP_FE(extest_compat_str,    arginfo_extest_compat_value)
	PHP_FE(extest_compat_array,  arginfo_extest_compat_value)
	PHPC_FE_END
};


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_compat)
{
	
	return SUCCESS;
}
/* }}} */

/* {{{ proto extest_compat_long(int value)
   Scalar function test */
PHP_FUNCTION(extest_compat_long)
{
	phpc_long_t value;
	long lv;
	zend_bool fail;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lb", &value, &fail) == FAILURE) {
		return;
	}

	if (fail) {
		PHPC_LONG_TO_LONG_EX(value, lv, RETURN_FALSE);
	} else {
		PHPC_LONG_TO_LONG(value, lv);
	}

	RETURN_LONG(lv);
}
/* }}} */

static void php_extest_print_half_str(PHPC_STR_ARG(value)) { /* {{{ */
	PHPC_STR_DECLARE(hv);
	phpc_str_size_t hl = PHPC_STR_LEN(value) / 2;

	PHPC_STR_ALLOC(hv, hl);
	memcpy(PHPC_STR_VAL(hv), PHPC_STR_VAL(value), hl);
	PHPC_STR_VAL(hv)[hl] = '\0';
	php_printf("half string(%" PHPC_STR_LEN_FMT ") : \"%s\"\n", PHPC_STR_LEN(hv), PHPC_STR_VAL(hv));
	PHPC_STR_RELEASE(hv);
}
/* }}} */

/* {{{ proto extest_compat_str(string value)
   String function test */
PHP_FUNCTION(extest_compat_str)
{
	char *cstr;
	phpc_str_size_t len;
	PHPC_STR_DECLARE(value);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &cstr, &len) == FAILURE) {
		return;
	}

	PHPC_STR_INIT(value, cstr, len);

	php_extest_print_half_str(PHPC_STR_PASS(value));

	PHPC_STR_RETURN(value);
}
/* }}} */

/* {{{ proto extest_compat_array(string value)
   Array function test */
PHP_FUNCTION(extest_compat_array)
{
	zval *arr;
	phpc_val *val;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		return;
	}

	 PHPC_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), val) {
		switch (PHPC_TYPE_P(val)) {
			case IS_STRING:
				php_printf("STRING\n");
				break;
			default:
				php_printf("NO STRING\n");
				break;
		}
	} PHPC_HASH_FOREACH_END();
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
