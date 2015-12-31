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


ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_fcall, 0)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_res, 0)
ZEND_ARG_INFO(0, res)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_name, 0)
ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_extest_compat_count, 0)
ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_extest_compat_dump, 0, 0, 0)
ZEND_ARG_INFO(0, ...)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_extest_compat_sum, 0, 0, 1)
ZEND_ARG_INFO(0, n)
ZEND_ARG_INFO(0, ...)
ZEND_END_ARG_INFO()

const zend_function_entry extest_compat_functions[] = {
	PHP_FE(extest_compat_long,              arginfo_extest_compat_long)
	PHP_FE(extest_compat_str,               arginfo_extest_compat_value)
	PHP_FE(extest_compat_cstr,              NULL)
	PHP_FE(extest_compat_cstrl,             NULL)
	PHP_FE(extest_compat_cstr_rv,           NULL)
	PHP_FE(extest_compat_cstrl_rv,          NULL)
	PHP_FE(extest_compat_array,             arginfo_extest_compat_value)
	PHP_FE(extest_compat_array_mod,         arginfo_extest_compat_value)
	PHP_FE(extest_compat_array_gen,         NULL)
	PHP_FE(extest_compat_array_copy,        arginfo_extest_compat_value)
	PHP_FE(extest_compat_fcall,             arginfo_extest_compat_fcall)
	PHP_FE(extest_compat_fcall_separate,    arginfo_extest_compat_fcall)
	PHP_FE(extest_compat_res_info_new,      arginfo_extest_compat_name)
	PHP_FE(extest_compat_res_stat_new,      arginfo_extest_compat_count)
	PHP_FE(extest_compat_res_info_get_name, arginfo_extest_compat_res)
	PHP_FE(extest_compat_res_dump,          arginfo_extest_compat_res)
	PHP_FE(extest_compat_dump,              arginfo_extest_compat_dump)
	PHP_FE(extest_compat_sum,               arginfo_extest_compat_sum)
	PHPC_FE_END
};

const zend_function_entry php_extest_compat_obj_funs[] = {
	PHP_ME(ExtestCompat, test,       NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, readProp,   NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(ExtestCompat, setName,    arginfo_extest_compat_name,     ZEND_ACC_PUBLIC)
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
	if (PHPC_OBJ_HANDLER_CREATE_EX_IS_NEW()) {
		PHPC_THIS->name = estrdup("hello");
	} else {
		PHPC_THIS->name = estrdup("hello clone");
	}
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

PHPC_OBJ_HANDLER_GET_GC(extest_compat)
{
	*PHPC_GC_TABLE = NULL;
	*PHPC_GC_N = 0;

	return zend_std_get_properties(PHPC_SELF TSRMLS_CC);
}

PHPC_OBJ_HANDLER_GET_DEBUG_INFO(extest_compat)
{
	HashTable *props;
	phpc_val value;
	zval *pzv;
	PHPC_THIS_DECLARE_AND_FETCH_FROM_SELF(extest_compat);

	*PHPC_DEBUG_INFO_IS_TEMP = 0;

	props = zend_std_get_properties(PHPC_SELF TSRMLS_CC);

	PHPC_VAL_MAKE(value);
	PHPC_VAL_CSTR(value, PHPC_THIS->name);
	PHPC_VAL_TO_PZVAL(value, pzv);
	PHPC_HASH_CSTR_UPDATE(props, "name_debug", pzv);

	return props;
}

PHPC_OBJ_HANDLER_GET_PROPERTIES(extest_compat)
{
	HashTable *props;
	phpc_val value;
	zval *pzv;
	PHPC_THIS_DECLARE_AND_FETCH_FROM_SELF(extest_compat);

	props = zend_std_get_properties(PHPC_SELF TSRMLS_CC);

	PHPC_VAL_MAKE(value);
	PHPC_VAL_CSTR(value, PHPC_THIS->name);
	PHPC_VAL_TO_PZVAL(value, pzv);
	PHPC_HASH_CSTR_UPDATE(props, "name", pzv);

	return props;
}

#define PHP_EXTEST_COMPAT_RES_INFO 1
#define PHP_EXTEST_COMPAT_RES_STAT 2

typedef struct extest_compat_res_info_entry_struct {
	int type;
	char *name;
} extest_compat_res_info_entry;

typedef struct extest_compat_res_stat_entry_struct {
	int type;
	phpc_long_t count;
} extest_compat_res_stat_entry;

static int extest_compat_res_info_type;
static int extest_compat_res_stat_type;

static void php_extest_compat_res_info_free(phpc_res_entry_t *rsrc TSRMLS_DC) /* {{{ */
{
	extest_compat_res_info_entry *entry = (extest_compat_res_info_entry *) rsrc->ptr;
	efree(entry->name);
	efree(entry);
}
/* }}} */

static void php_extest_compat_res_stat_free(phpc_res_entry_t *rsrc TSRMLS_DC) /* {{{ */
{
	efree(rsrc->ptr);
}
/* }}} */

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
	PHPC_OBJ_SET_HANDLER_GET_GC(extest_compat);
	PHPC_OBJ_SET_HANDLER_GET_DEBUG_INFO(extest_compat);
	PHPC_OBJ_SET_HANDLER_GET_PROPERTIES(extest_compat);

	zend_declare_property_null(extest_compat_ce,
			"prop", sizeof("prop")-1, ZEND_ACC_PUBLIC TSRMLS_CC);

	extest_compat_res_info_type = zend_register_list_destructors_ex(
			php_extest_compat_res_info_free, NULL, "Extest Compat Info", module_number);

	extest_compat_res_stat_type = zend_register_list_destructors_ex(
			php_extest_compat_res_stat_free, NULL, "Extest Compat Stat", module_number);

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
/* }}} */

/* {{{ proto extest_compat_long(int value, string str, boolean fail)
   Scalar function test */
PHP_FUNCTION(extest_compat_long)
{
	phpc_long_t value;
	long lv;
	int iv;
	char *cstr;
	phpc_str_size_t len;
	zend_bool fail;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsb", &value, &cstr, &len, &fail) == FAILURE) {
		return;
	}

	if (fail) {
		PHPC_SIZE_TO_LONG_EX(len, lv, RETURN_FALSE);
	} else {
		PHPC_SIZE_TO_LONG(len, lv);
	}

	if (fail) {
		PHPC_SIZE_TO_INT_EX(len, iv, RETURN_FALSE);
	} else {
		PHPC_SIZE_TO_INT(len, iv);
	}

	php_printf("SIZE - long: %ld; int: %d\n", lv, iv);

	if (fail) {
		PHPC_LONG_TO_LONG_EX(value, lv, RETURN_FALSE);
	} else {
		PHPC_LONG_TO_LONG(value, lv);
	}

	if (fail) {
		PHPC_LONG_TO_INT_EX(value, iv, RETURN_FALSE);
	} else {
		PHPC_LONG_TO_INT(value, iv);
	}

	php_printf("LONG - long: %ld; int: %d\n", lv, iv);

	RETURN_LONG(lv);
}
/* }}} */

static void php_extest_print_str_val(PHPC_STR_ARG_VAL(value)) { /* {{{ */
	PHPC_STR_LEN_DECLARE_AND_FETCH(value);

	php_printf("str_val(%" PHPC_STR_LEN_FMT "): %s\n", PHPC_STR_LEN(value), PHPC_STR_VAL(value));
}
/* }}} */

static void php_extest_print_str_ptr_val(PHPC_STR_ARG_PTR_VAL(pvalue)) { /* {{{ */
	PHPC_STR_DECLARE(value);
	PHPC_STR_FROM_PTR_VAL(value, pvalue);

	php_printf("str_ptr_val(%" PHPC_STR_LEN_FMT "): %s\n", PHPC_STR_LEN(value), PHPC_STR_VAL(value));
}
/* }}} */

static void php_extest_print_str_ptr(PHPC_STR_ARG_PTR(pvalue)) { /* {{{ */
	PHPC_STR_DECLARE(value);
	PHPC_STR_FROM_PTR_STR(value, pvalue);

	php_printf("str_ptr(%" PHPC_STR_LEN_FMT "): %s\n", PHPC_STR_LEN(value), PHPC_STR_VAL(value));
}
/* }}} */

static void php_extest_print_mult_str(PHPC_STR_ARG(value)) { /* {{{ */
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

	php_extest_print_str_val(PHPC_STR_PASS_VAL(value));
	php_extest_print_str_ptr_val(PHPC_STR_PASS_PTR_VAL(value));
	php_extest_print_str_ptr(PHPC_STR_PASS_PTR(value));
	php_extest_print_mult_str(PHPC_STR_PASS(value));

	PHPC_STR_RETURN(value);
}
/* }}} */

/* {{{ proto extest_compat_cstr()
   C string function test */
PHP_FUNCTION(extest_compat_cstr)
{
	PHPC_CSTR_RETURN("cstr test");
}
/* }}} */

/* {{{ proto extest_compat_cstrl()
   C string function test */
PHP_FUNCTION(extest_compat_cstrl)
{
	PHPC_CSTRL_RETURN("cstr with len test (not visible)", 18);
}
/* }}} */

/* {{{ proto extest_compat_cstr_rv()
   C string function test */
PHP_FUNCTION(extest_compat_cstr_rv)
{
	char *test = (char *) malloc(14);
	strcpy(test, "cstr_rv test");
	test[13] = '\0';

	PHPC_CSTR_RETVAL(test);
	free(test);
}
/* }}} */

/* {{{ proto extest_compat_cstrl_rv()
   C string function test */
PHP_FUNCTION(extest_compat_cstrl_rv)
{
	char *test = strdup("cstr_rv with len test (not visible)");

	PHPC_CSTRL_RETVAL(test, 21);
	free(test);
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
			php_printf("key: \"%s\" (len: %"PHPC_STR_LEN_FMT")\n",
					PHPC_STR_VAL(key), PHPC_STR_LEN(key));
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
/* }}} */

/* {{{ proto extest_compat_array_gen()
   Array function test for adding values */
PHP_FUNCTION(extest_compat_array_gen)
{
	PHPC_STR_DECLARE(str);
	phpc_val pv;

	PHPC_ARRAY_INIT(return_value);

	PHPC_ARRAY_ADD_NEXT_INDEX_BOOL(return_value, 1);
	PHPC_ARRAY_ADD_NEXT_INDEX_LONG(return_value, 5);
	PHPC_ARRAY_ADD_NEXT_INDEX_DOUBLE(return_value, 5.1);
	PHPC_STR_INIT(str, "str_next_index_val", sizeof("str_next_index_val")-1);
	PHPC_ARRAY_ADD_NEXT_INDEX_STR(return_value, str);
	PHPC_ARRAY_ADD_NEXT_INDEX_CSTR(return_value, "cstr_next_index_val");
	PHPC_ARRAY_ADD_NEXT_INDEX_CSTRL(return_value,
			"cstrl_next_index_val", sizeof("cstrl_next_index_val")-1);
	PHPC_VAL_MAKE(pv);
	PHPC_VAL_CSTR(pv, "zval_next_index_val");
	PHPC_ARRAY_ADD_NEXT_INDEX_VAL(return_value, pv);

	PHPC_ARRAY_ADD_INDEX_BOOL(return_value, 10, 0);
	PHPC_ARRAY_ADD_INDEX_LONG(return_value, 11, 4);
	PHPC_ARRAY_ADD_INDEX_DOUBLE(return_value, 12, 4.1);
	PHPC_STR_INIT(str, "str_index_val", sizeof("str_index_val")-1);
	PHPC_ARRAY_ADD_INDEX_STR(return_value, 13, str);
	PHPC_ARRAY_ADD_INDEX_CSTR(return_value, 14, "cstr_index_val");
	PHPC_ARRAY_ADD_INDEX_CSTRL(return_value, 15,
			"cstrl_index_val", sizeof("cstrl_index_val")-1);
	PHPC_VAL_MAKE(pv);
	PHPC_VAL_CSTR(pv, "zval_val");
	PHPC_ARRAY_ADD_INDEX_VAL(return_value, 16, pv);

	PHPC_ARRAY_ADD_ASSOC_BOOL(return_value, "bool", 1);
	PHPC_ARRAY_ADD_ASSOC_LONG(return_value, "long", 3);
	PHPC_ARRAY_ADD_ASSOC_DOUBLE(return_value, "double", 3.1);
	PHPC_STR_INIT(str, "str_assoc_val", sizeof("str_assoc_val")-1);
	PHPC_ARRAY_ADD_ASSOC_STR(return_value, "str", str);
	PHPC_ARRAY_ADD_ASSOC_CSTR(return_value, "cstr", "cstr_assoc_val");
	PHPC_ARRAY_ADD_ASSOC_CSTRL(return_value, "cstrl",
			"cstrl_assoc_val", sizeof("cstrl_assoc_val")-1);
	PHPC_VAL_MAKE(pv);
	PHPC_VAL_CSTR(pv, "zval_assoc_val");
	PHPC_ARRAY_ADD_ASSOC_VAL(return_value, "zval", pv);

	PHPC_ARRAY_ADD_ASSOC_BOOL_EX(return_value, "bool_ex", sizeof("bool_ex")-1, 0);
	PHPC_ARRAY_ADD_ASSOC_LONG_EX(return_value, "long_ex", sizeof("long_ex")-1, 2);
	PHPC_ARRAY_ADD_ASSOC_DOUBLE_EX(return_value, "double_ex", sizeof("double_ex")-1, 2.1);
	PHPC_STR_INIT(str, "str_assoc_val_ex", sizeof("str_assoc_val_ex")-1);
	PHPC_ARRAY_ADD_ASSOC_STR_EX(return_value, "str_ex", sizeof("str_ex")-1, str);
	PHPC_ARRAY_ADD_ASSOC_CSTR_EX(return_value, "cstr_ex", sizeof("cstr_ex")-1,
			"cstr_assoc_val_ex");
	PHPC_ARRAY_ADD_ASSOC_CSTRL_EX(return_value, "cstrl_ex", sizeof("cstrl_ex")-1,
			"cstrl_assoc_val_ex", sizeof("cstrl_assoc_val_ex")-1);
	PHPC_VAL_MAKE(pv);
	PHPC_VAL_CSTR(pv, "zval_assoc_val_ex");
	PHPC_ARRAY_ADD_ASSOC_VAL_EX(return_value, "zval_ex", sizeof("zval_ex")-1, pv);
}
/* }}} */

/* {{{ proto extest_compat_array_copy($value)
   Array function test for copying array value */
PHP_FUNCTION(extest_compat_array_copy)
{
	zval *arr;
	HashTable *aht, *aht_copy;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		return;
	}

	aht = Z_ARRVAL_P(arr);

	PHPC_HASH_ALLOC(aht_copy);
	PHPC_HASH_INIT(aht_copy, 1, NULL, ZVAL_PTR_DTOR, 0);
	PHPC_HASH_COPY(aht_copy, aht);
	PHPC_HASH_RETURN(aht_copy);
}
/* }}} */

/* {{{ proto extest_compat_fcall($callback)
   Call function */
PHP_FUNCTION(extest_compat_fcall)
{
	PHPC_FCALL_PARAMS_DECLARE(callback, 3);
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
	phpc_val retval;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
		return;
	}

	PHPC_FCALL_PARAMS_INIT(callback);
	/* param 0 is null */
	PHPC_VAL_MAKE(PHPC_FCALL_PARAM_VAL(callback, 0));
	PHPC_FCALL_PARAM_UNDEF(callback, 0);
	/* param 1 is int */
	PHPC_VAL_MAKE(PHPC_FCALL_PARAM_VAL(callback, 1));
	ZVAL_LONG(PHPC_FCALL_PARAM_PZVAL(callback, 1), 11);
	/* param 1 is string */
	PHPC_VAL_MAKE(PHPC_FCALL_PARAM_VAL(callback, 2));
	PHPC_VAL_CSTR(PHPC_FCALL_PARAM_VAL(callback, 2), "param");
	/* set fci */
	PHPC_FCALL_RETVAL(fci, retval);
	fci.params = PHPC_FCALL_PARAMS_NAME(callback);
	fci.param_count = 3;
	fci.no_separation = 1;

	if (zend_call_function(&fci, &fci_cache TSRMLS_CC) != SUCCESS || PHPC_VAL_ISUNDEF(retval)) {
		php_printf("FCALL failed\n");
	}

	zval_ptr_dtor(&PHPC_FCALL_PARAM_VAL(callback, 0));
	zval_ptr_dtor(&PHPC_FCALL_PARAM_VAL(callback, 1));
	zval_ptr_dtor(&PHPC_FCALL_PARAM_VAL(callback, 2));
	zval_ptr_dtor(&retval);

}
/* }}} */

/* {{{ proto extest_compat_fcall_separate($callback)
   Call function */
PHP_FUNCTION(extest_compat_fcall_separate)
{
	PHPC_FCALL_PARAMS_DECLARE(callback, 2);
	zval *z_callback;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
	phpc_val retval;
	char *error_msg = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_callback) == FAILURE) {
		return;
	}

	if (PHPC_FCALL_INFO_INIT(z_callback, 0, &fci, &fci_cache,	NULL, &error_msg) == FAILURE) {
		if (error_msg) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING,
					"Callback is not a valid callback, %s", error_msg);
			efree(error_msg);
		}
		else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Callback is not a valid callback");
		}
		RETURN_FALSE;
	}

	PHPC_FCALL_PARAMS_INIT(callback);
	/* param 0 is int */
	PHPC_VAL_MAKE(PHPC_FCALL_PARAM_VAL(callback, 0));
	ZVAL_LONG(PHPC_FCALL_PARAM_PZVAL(callback, 0), 11);
	/* param 1 is string */
	PHPC_VAL_MAKE(PHPC_FCALL_PARAM_VAL(callback, 1));
	PHPC_VAL_CSTR(PHPC_FCALL_PARAM_VAL(callback, 1), "param");
	/* set fci */
	PHPC_FCALL_RETVAL(fci, retval);
	fci.params = PHPC_FCALL_PARAMS_NAME(callback);
	fci.param_count = 2;
	fci.no_separation = 0;

	if (zend_call_function(&fci, &fci_cache TSRMLS_CC) != SUCCESS || PHPC_VAL_ISUNDEF(retval)) {
		php_printf("FCALL failed\n");
	}

	zval_ptr_dtor(&PHPC_FCALL_PARAM_VAL(callback, 0));
	zval_ptr_dtor(&PHPC_FCALL_PARAM_VAL(callback, 1));
	zval_ptr_dtor(&retval);

}
/* }}} */

/* {{{ proto extest_compat_res_info_new($name)
   Create a new info resource */
PHP_FUNCTION(extest_compat_res_info_new)
{
	char *name;
	phpc_str_size_t name_len;
	extest_compat_res_info_entry *entry;
	phpc_res_value_t res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}

	entry = emalloc(sizeof(extest_compat_res_info_entry));
	entry->type = PHP_EXTEST_COMPAT_RES_INFO;
	entry->name = estrndup(name, name_len);

	res = PHPC_RES_REGISTER(entry, extest_compat_res_info_type);

	/* the PHPC_RES_PZVAL is outstandin - just for testing */
	PHPC_RES_PZVAL(res, return_value);
	PHPC_RES_RETURN(res);
}
/* }}} */

/* {{{ proto extest_compat_res_stat_new($name)
   Create a new stat resource */
PHP_FUNCTION(extest_compat_res_stat_new)
{
	phpc_long_t count;
	extest_compat_res_stat_entry *entry;
	phpc_res_value_t res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &count) == FAILURE) {
		return;
	}

	entry = emalloc(sizeof(extest_compat_res_stat_entry));
	entry->type = PHP_EXTEST_COMPAT_RES_STAT;
	entry->count = count;

	res = PHPC_RES_REGISTER(entry, extest_compat_res_stat_type);

	PHPC_RES_RETVAL(res);
}
/* }}} */

/* {{{ proto extest_compat_res_info_get_name($res)
   Get resource name */
PHP_FUNCTION(extest_compat_res_info_get_name)
{
	extest_compat_res_info_entry *entry;
	zval *res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &res) == FAILURE) {
		return;
	}

	entry = PHPC_RES_FETCH(res, "Extest Compat Info", extest_compat_res_info_type);

	PHPC_CSTR_RETURN(entry->name);
}
/* }}} */

/* {{{ proto extest_compat_res_dump($res)
   Dump extest compat resource */
PHP_FUNCTION(extest_compat_res_dump)
{
	extest_compat_res_info_entry *info_entry;
	extest_compat_res_stat_entry *stat_entry;
	int *ptype;
	zval *res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &res) == FAILURE) {
		return;
	}

	ptype = PHPC_RES_FETCH2(res, NULL,
			extest_compat_res_info_type, extest_compat_res_stat_type);

	switch (*ptype) {
		case PHP_EXTEST_COMPAT_RES_STAT:
			stat_entry = (extest_compat_res_stat_entry *) ptype;
			php_printf("STAT resource (count: %d)\n", stat_entry->count);
			break;
		case PHP_EXTEST_COMPAT_RES_INFO:
			info_entry = (extest_compat_res_info_entry *) ptype;
			php_printf("INFO resource (name: %s)\n", info_entry->name);
			break;
		default:
			php_printf("Resource type unkonwn %d\n", *ptype);
			break;
	}

}
/* }}} */

/* {{{ proto extest_compat_dump(...)
   Dump all elements */
PHP_FUNCTION(extest_compat_dump)
{
	PHPC_ZPP_ARGS_DECLARE();

	PHPC_ZPP_ARGS_LOAD(*);

	php_printf("Number of items to dump: %d\n", PHPC_ZPP_ARGS_COUNT);

	PHPC_ZPP_ARGS_LOOP_START() {
		php_var_dump(PHPC_ZPP_ARGS_GET_CURRENT_PVAL(), 0 TSRMLS_CC);
	} PHPC_ZPP_ARGS_LOOP_END();

	PHPC_ZPP_ARGS_FREE();
}
/* }}} */

/* {{{ proto extest_compat_sum($n, ...)
   Sum $n following arguments */
PHP_FUNCTION(extest_compat_sum)
{
	phpc_val *ppv;
	phpc_long_t n, total = 0;
	PHPC_ZPP_ARGS_DECLARE();

	PHPC_ZPP_ARGS_LOAD_EX(+, ZEND_NUM_ARGS(), return);

	ppv = PHPC_ZPP_ARGS_GET_PVAL(0);
	if (PHPC_TYPE_P(ppv) != IS_LONG) {
		PHPC_ZPP_ARGS_FREE();
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First parameter has to be integer");
		RETURN_FALSE;
	}

	n = PHPC_LVAL_P(ppv);
	if (n != PHPC_ZPP_ARGS_COUNT - 1) {
		PHPC_ZPP_ARGS_FREE();
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid number of arguments");
		RETURN_FALSE;
	}


	PHPC_ZPP_ARGS_LOOP_START_EX(1) {
		total += PHPC_LVAL_P(PHPC_ZPP_ARGS_GET_CURRENT_PVAL());
	} PHPC_ZPP_ARGS_LOOP_END();

	PHPC_ZPP_ARGS_FREE();

	RETURN_LONG(total)
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
