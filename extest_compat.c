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
#include "ext/standard/php_var.h"

#include "phpc/phpc.h"

typedef struct _php_extest_compat_obj {
	PHPC_OBJ_MEMBER_FIRST
	char *name;
	int type;
	PHPC_OBJ_MEMBER_LAST
} php_extest_compat_obj;

const zend_function_entry php_extest_compat_obj_funs[] = {
	PHP_ME(ExtestCompat, test, NULL, ZEND_ACC_PUBLIC)
	PHPC_FE_END
};

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

zend_class_entry *extest_compat_ce;

PHPC_OBJ_GET_HANDLER_VAR_DEF(extest_compat);

PHPC_OBJ_HANDLER_FREE_OBJ(extest_compat)
{
	/* PHP_OBJ_FROM_ZOBJ(object, php_extest_compat_obj) */
	php_extest_compat_obj *intern =  PHP_OBJ_GET_HANDLER_OBJ_FROM_ZOBJ(php_extest_compat_obj);

	if (intern->name) {
		efree(intern->name);
	}

	PHPC_OBJ_HANDLER_FREE_OBJ_FREE(intern);
}

PHPC_OBJ_HANDLER_CREATE_EX(extest_compat, php_extest_compat_obj)
{
	PHPC_OBJ_HANDLER_CREATE_EX_INIT();
	php_extest_compat_obj *intern;

	intern = PHPC_OBJ_HANDLER_CREATE_EX_ALLOC(php_extest_compat_obj);
	PHPC_OBJ_HANDLER_INIT_CREATE_EX_PROPS(intern);

	PHPC_OBJ_HANDLER_CREATE_EX_RETURN(extest_compat, intern);
}

PHPC_OBJ_HANDLER_CREATE(extest_compat, php_extest_compat_obj)
{
	PHPC_OBJ_HANDLER_CREATE_RETURN(extest_compat);
}

PHPC_OBJ_HANDLER_CLONE(extest_compat)
{
	PHPC_OBJ_HANDLER_CLONE_INIT();
	php_extest_compat_obj *old_obj, *new_obj;

	old_obj = PHPC_OBJ_FROM_THIS(php_extest_compat_obj);
	PHPC_OBJ_HANDLER_CLONE_MEMBERS(new_obj, old_obj)

	PHPC_OBJ_HANDLER_CLONE_RETURN();
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_compat)
{
	zend_class_entry ce_compat;

	/* init classes */
	INIT_CLASS_ENTRY(ce_compat, "ExtestCompat", php_extest_compat_obj_funs);
	PHPC_CLASS_SET_HANDLER_CREATE(ce_compat, extest_compat); /* ce_compat.create_object = extest_compat_obj_create; */
	extest_compat_ce = PHPC_CLASS_REGISTER(ce_compat);
	memcpy(&PHPC_OBJ_GET_HANDLER_VAR_NAME(extest_compat), zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	PHPC_OBJ_SET_HANDLER_OFFSET(PHPC_OBJ_GET_HANDLER_VAR_NAME(extest_compat), php_extest_compat_obj);
	PHPC_OBJ_SET_HANDLER_FREE_OBJ(PHPC_OBJ_GET_HANDLER_VAR_NAME(extest_compat), extest_compat_obj_free);

	return SUCCESS;
}
/* }}} */

/* {{{ proto ExtestCompat::test() */
PHP_METHOD(ExtestCompat, test)
{
	
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
	phpc_ulong_t idx;
	phpc_val *val;
	PHPC_STR_DECLARE(key);
	PHPC_STR_LEN_UNUSED(key);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		return;
	}

	PHPC_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), val) {
		/*
		 * it can be used only with phpc_val as it's ptr ptr in 5 and ptr in 7
		 * - the same is true for php_debug_zval_dump
		 */
		php_var_dump(val, 1 TSRMLS_CC);
	} PHPC_HASH_FOREACH_END();

	PHPC_HASH_FOREACH_STR_KEY_VAL(Z_ARRVAL_P(arr), key, val) {
		php_printf("key: \"%s\"\n", PHPC_STR_EXISTS(key) ? PHPC_STR_VAL(key) : "");
		php_var_dump(val, 1 TSRMLS_CC);
	} PHPC_HASH_FOREACH_END();

	PHPC_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), idx, key, val) {
		if (PHPC_STR_EXISTS(key)) {
			php_printf("key: \"%s\"\n", PHPC_STR_VAL(key));
		} else {
			php_printf("index: %lu\n", idx);
		}
		php_var_dump(val, 1 TSRMLS_CC);
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
