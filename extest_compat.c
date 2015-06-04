/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 2013-2015 Jakub Zelenka                                |
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

PHPC_OBJ_STRUCT_BEGIN(extest_compat)
	char *name;
	int type;
PHPC_OBJ_STRUCT_END()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_long, 0)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, fail)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_value, 0)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_ExtestCompat_setName, 0)
ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

const zend_function_entry extest_compat_functions[] = {
	PHP_FE(extest_compat_long,            arginfo_extest_compat_long)
	PHP_FE(extest_compat_str,             arginfo_extest_compat_value)
	PHP_FE(extest_compat_cstr,            NULL)
	PHP_FE(extest_compat_cstrl,           NULL)
	PHP_FE(extest_compat_array,           arginfo_extest_compat_value)
	PHP_FE(extest_compat_array_mod,       arginfo_extest_compat_value)
	PHPC_FE_END
};

const zend_function_entry php_extest_compat_obj_funs[] = {
	PHP_ME(ExtestCompat, test,       NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, readProp,   NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, setName,    arginfo_ExtestCompat_setName,   ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, getName,    NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, toArray,    NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, toArrayAlt, NULL,                           ZEND_ACC_PUBLIC)
	PHPC_FE_END
};

zend_class_entry *extest_compat_ce;

PHPC_OBJ_DEFINE_HANDLER_VAR(extest_compat);

PHPC_OBJ_HANDLER_FREE(extest_compat)
{
	PHPC_OBJ_HANDLER_FREE_INIT(extest_compat);

	if (PHPC_THIS->name) {
		efree(PHPC_THIS->name);
	}

	PHPC_OBJ_HANDLER_FREE_DESTROY();
}

PHPC_OBJ_HANDLER_CREATE_EX(extest_compat)
{
	PHPC_OBJ_HANDLER_CREATE_EX_INIT(extest_compat);

	/* custom setup */
	PHPC_THIS->name = estrdup("hello");
	PHPC_THIS->type = 1;

	PHPC_OBJ_HANDLER_CREATE_EX_RETURN(extest_compat);
}

PHPC_OBJ_HANDLER_CREATE(extest_compat)
{
	PHPC_OBJ_HANDLER_CREATE_RETURN(extest_compat);
}

PHPC_OBJ_HANDLER_CLONE(extest_compat)
{
	PHPC_OBJ_HANDLER_CLONE_INIT(extest_compat);

	if (!strcmp(PHPC_THIS->name, PHPC_THAT->name)) {
		efree(PHPC_THAT->name);
		PHPC_THAT->name = estrdup(PHPC_THIS->name);
	}

	PHPC_OBJ_HANDLER_CLONE_RETURN();
}

PHPC_OBJ_HANDLER_COMPARE(extest_compat)
{
	PHPC_OBJ_HANDLER_COMPARE_INIT(extest_compat);

	return strcmp(PHPC_THIS->name, PHPC_THAT->name);
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(extest_compat)
{
	zend_class_entry ce_compat;

	/* init classes */
	INIT_CLASS_ENTRY(ce_compat, "ExtestCompat", php_extest_compat_obj_funs);
	PHPC_CLASS_SET_HANDLER_CREATE(ce_compat, extest_compat);
	extest_compat_ce = PHPC_CLASS_REGISTER(ce_compat);
	PHPC_OBJ_INIT_HANDLERS(extest_compat);
	PHPC_OBJ_SET_HANDLER_OFFSET(extest_compat);
	PHPC_OBJ_SET_HANDLER_FREE(extest_compat);
	PHPC_OBJ_SET_HANDLER_CLONE(extest_compat);
	PHPC_OBJ_SET_HANDLER_COMPARE(extest_compat);

	zend_declare_property_null(extest_compat_ce,
			"prop", sizeof("prop")-1, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ proto ExtestCompat::test() */
PHP_METHOD(ExtestCompat, test)
{
	PHPC_THIS_DECLARE_AND_FETCH(extest_compat);

	php_printf("ExtestCompat TEST - name: %s, type: %d\n", PHPC_THIS->name, PHPC_THIS->type);
}
/* }}} */

/* {{{ proto ExtestCompat::readProp() */
PHP_METHOD(ExtestCompat, readProp)
{
	PHPC_THIS_DECLARE_AND_FETCH(extest_compat);
	zval *prop;
	PHPC_READ_PROPERTY_RV_DECLARE;

	prop = PHPC_READ_PROPERTY(extest_compat_ce, getThis(), "prop", sizeof("prop")-1, 1);

	if (Z_TYPE_P(prop) != IS_STRING) {
		zend_update_property_string(extest_compat_ce, getThis(),
			"prop", sizeof("prop")-1, "unknown" TSRMLS_CC);

		PHPC_CSTR_RETURN("unknown");
	}

	RETURN_ZVAL(prop, 1, 0);
}
/* }}} */

/* {{{ proto ExtestCompat::setName($name) */
PHP_METHOD(ExtestCompat, setName)
{
	char *name;
	phpc_str_size_t name_len;
	PHPC_THIS_DECLARE(extest_compat);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}

	PHPC_THIS_FETCH(extest_compat);

	if (PHPC_THIS->name) {
		efree(PHPC_THIS->name);
	}
	PHPC_THIS->name = estrdup(name);
}
/* }}} */

/* {{{ proto ExtestCompat::getName() */
PHP_METHOD(ExtestCompat, getName)
{
	PHPC_STR_DECLARE(name);
	PHPC_THIS_DECLARE_AND_FETCH(extest_compat);

	PHPC_STR_INIT(name, PHPC_THIS->name, strlen(PHPC_THIS->name));
	PHPC_STR_RETURN(name);
}
/* }}} */

/* {{{ proto ExtestCompat::toArray() */
PHP_METHOD(ExtestCompat, toArray)
{
	PHPC_THIS_DECLARE(extest_compat);

	if (zend_parse_parameters_none()) {
		return;
	}

	PHPC_THIS_FETCH(extest_compat);

	PHPC_ARRAY_INIT_SIZE(return_value, 1);
	PHPC_ARRAY_ADD_ASSOC_CSTR(return_value, "name", PHPC_THIS->name);
}
/* }}} */

/* {{{ proto ExtestCompat::toArrayAlt()
   Alternative implementation of toArray (not recommended) */
PHP_METHOD(ExtestCompat, toArrayAlt)
{
	HashTable *aht;
	PHPC_THIS_DECLARE(extest_compat);
	phpc_val value;
	zval *pzv;

	if (zend_parse_parameters_none()) {
		return;
	}

	PHPC_THIS_FETCH(extest_compat);

	PHPC_HASH_ALLOC(aht);
	PHPC_HASH_INIT(aht, 1, NULL, ZVAL_PTR_DTOR, 0);

	PHPC_VAL_MAKE(value);
	PHPC_VAL_CSTR(value, PHPC_THIS->name);
	PHPC_VAL_TO_PZVAL(value, pzv);
	PHPC_HASH_CSTR_UPDATE(aht, "name", pzv);

	PHPC_HASH_RETURN(aht);
}

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
	PHPC_STR_DECLARE(tmp_value);
	phpc_str_size_t tmp_len = PHPC_STR_LEN(value) / 2;

	PHPC_STR_ALLOC(tmp_value, tmp_len);
	memcpy(PHPC_STR_VAL(tmp_value), PHPC_STR_VAL(value), tmp_len);
	PHPC_STR_VAL(tmp_value)[tmp_len] = '\0';
	php_printf("half string(%" PHPC_STR_LEN_FMT ") : \"%s\"\n",
			PHPC_STR_LEN(tmp_value), PHPC_STR_VAL(tmp_value));
	tmp_len = PHPC_STR_LEN(value) * 2;
	PHPC_STR_REALLOC(tmp_value, tmp_len);
	memcpy(PHPC_STR_VAL(tmp_value), PHPC_STR_VAL(value), PHPC_STR_LEN(value));
	memcpy(PHPC_STR_VAL(tmp_value) + PHPC_STR_LEN(value), PHPC_STR_VAL(value), PHPC_STR_LEN(value));
	PHPC_STR_VAL(tmp_value)[tmp_len] = '\0';
	php_printf("double string(%" PHPC_STR_LEN_FMT ") : \"%s\"\n",
			PHPC_STR_LEN(tmp_value), PHPC_STR_VAL(tmp_value));
	PHPC_STR_RELEASE(tmp_value);
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

/* {{{ proto extest_compat_cstr()
   C string function test */
PHP_FUNCTION(extest_compat_cstr)
{
	if (zend_parse_parameters_none()) {
		return;
	}

	PHPC_CSTR_RETURN("cstr test");
}
/* }}} */

/* {{{ proto extest_compat_cstrl()
   C string function test */
PHP_FUNCTION(extest_compat_cstrl)
{
	if (zend_parse_parameters_none()) {
		return;
	}

	PHPC_CSTRL_RETURN("cstr with len test (not visible)", 18);
}
/* }}} */

/* {{{ proto extest_compat_array(string value)
   Array function test */
PHP_FUNCTION(extest_compat_array)
{
	zval *arr;
	phpc_ulong_t idx;
	phpc_val *ppv;
	PHPC_STR_DECLARE(key);
	PHPC_STR_LEN_UNUSED(key);
	HashPosition pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		return;
	}

	php_printf("array with %d elements\n", PHPC_HASH_NUM_ELEMENTS(Z_ARRVAL_P(arr)));

	PHPC_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), ppv) {
		/*
		 * it can be used only with phpc_val as it's ptr ptr in 5 and ptr in 7
		 * - the same is true for php_debug_zval_dump
		 */
		php_var_dump(ppv, 1 TSRMLS_CC);
	} PHPC_HASH_FOREACH_END();

	PHPC_HASH_FOREACH_STR_KEY_VAL(Z_ARRVAL_P(arr), key, ppv) {
		php_printf("key: \"%s\"\n", PHPC_STR_EXISTS(key) ? PHPC_STR_VAL(key) : "");
		php_var_dump(ppv, 1 TSRMLS_CC);
	} PHPC_HASH_FOREACH_END();

	PHPC_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), idx, key, ppv) {
		if (PHPC_STR_EXISTS(key)) {
			php_printf("key: \"%s\"\n", PHPC_STR_VAL(key));
		} else {
			php_printf("index: %lu\n", idx);
		}
		php_var_dump(ppv, 1 TSRMLS_CC);
	} PHPC_HASH_FOREACH_END();

	/* custom ex getters */
	PHPC_HASH_INTERNAL_POINTER_RESET_EX(Z_ARRVAL_P(arr), &pos);
	if (PHPC_HASH_HAS_MORE_ELEMENTS_EX(Z_ARRVAL_P(arr), &pos) == SUCCESS) {
		PHPC_HASH_GET_CURRENT_DATA_EX(Z_ARRVAL_P(arr), ppv, &pos);
		PHPC_HASH_GET_CURRENT_KEY_EX(Z_ARRVAL_P(arr), key, idx, &pos);
		if (PHPC_STR_EXISTS(key)) {
			php_printf("key: \"%s\"\n", PHPC_STR_VAL(key));
		} else {
			php_printf("index: %lu\n", idx);
		}
		php_var_dump(ppv, 1 TSRMLS_CC);
	}

	/* custom getters */
	PHPC_HASH_INTERNAL_POINTER_RESET(Z_ARRVAL_P(arr));
	if (PHPC_HASH_HAS_MORE_ELEMENTS(Z_ARRVAL_P(arr)) == SUCCESS) {
		PHPC_HASH_GET_CURRENT_DATA(Z_ARRVAL_P(arr), ppv);
		PHPC_HASH_GET_CURRENT_KEY(Z_ARRVAL_P(arr), key, idx);
		if (PHPC_STR_EXISTS(key)) {
			php_printf("key: \"%s\"\n", PHPC_STR_VAL(key));
		} else {
			php_printf("index: %lu\n", idx);
		}
		php_var_dump(ppv, 1 TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto extest_compat_array_mod(string value)
   Array function test */
PHP_FUNCTION(extest_compat_array_mod)
{
	zval *arr, *pzv;
	phpc_val *ppv, pv;
	PHPC_STR_DECLARE(key);
	PHPC_STR_LEN_UNUSED(key);
	HashTable *aht;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		return;
	}

	aht = Z_ARRVAL_P(arr);

	/* index */
	if (PHPC_HASH_INDEX_EXISTS(aht, 1)) {
		PHPC_HASH_INDEX_FIND(aht, 1, ppv);
		php_printf("Deleting value 1:\n");
		php_var_dump(ppv, 1 TSRMLS_CC);
		PHPC_HASH_INDEX_DELETE(aht, 1);
		php_printf("Value exists : %s\n", PHPC_HASH_INDEX_EXISTS(aht, 1) ? "yes" : "no");

		PHPC_VAL_MAKE(pv);
		PHPC_VAL_CSTR(pv, "index1");
		PHPC_VAL_TO_PZVAL(pv, pzv);
		PHPC_HASH_INDEX_UPDATE(aht, 1, pzv);
	}

	/* cstr */
	if (PHPC_HASH_CSTR_EXISTS(aht, "key1")) {
		PHPC_HASH_CSTR_FIND(aht, "key1", ppv);
		php_printf("Deleting value key1:\n");
		php_var_dump(ppv, 1 TSRMLS_CC);
		PHPC_HASH_CSTR_DELETE(aht, "key1");
		php_printf("Value exists : %s\n", PHPC_HASH_CSTR_EXISTS(aht, "key1") ? "yes" : "no");

		PHPC_VAL_MAKE(pv);
		PHPC_VAL_CSTR(pv, "key1v");
		PHPC_VAL_TO_PZVAL(pv, pzv);
		PHPC_HASH_CSTR_UPDATE(aht, "key1", pzv);
	}

	/* cstrl */
	if (PHPC_HASH_CSTRL_EXISTS(aht, "key2", 4)) {
		PHPC_HASH_CSTRL_FIND(aht, "key2", 4, ppv);
		php_printf("Deleting value key2:\n");
		php_var_dump(ppv, 1 TSRMLS_CC);
		PHPC_HASH_CSTRL_DELETE(aht, "key2", 4);
		php_printf("Value exists : %s\n", PHPC_HASH_CSTRL_EXISTS(aht, "key2", 4) ? "yes" : "no");

		PHPC_VAL_MAKE(pv);
		PHPC_VAL_CSTR(pv, "key2v");
		PHPC_VAL_TO_PZVAL(pv, pzv);
		PHPC_HASH_CSTRL_UPDATE(aht, "key2", 4, pzv);
	}

	/* str */
	PHPC_STR_INIT(key, "key3", 4);
	if (PHPC_HASH_STR_EXISTS(aht, key)) {
		PHPC_HASH_STR_FIND(aht, key, ppv);
		php_printf("Deleting value key3:\n");
		php_var_dump(ppv, 1 TSRMLS_CC);
		PHPC_HASH_STR_DELETE(aht, key);
		php_printf("Value exists : %s\n", PHPC_HASH_STR_EXISTS(aht, key) ? "yes" : "no");

		PHPC_VAL_MAKE(pv);
		PHPC_VAL_CSTR(pv, "key3v");
		PHPC_VAL_TO_PZVAL(pv, pzv);
		PHPC_HASH_STR_UPDATE(aht, key, pzv);
	}
	PHPC_STR_RELEASE(key);
}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
