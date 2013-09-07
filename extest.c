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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_extest.h"
#include "php_extest_serialize.h"
#include "ext/standard/info.h"

ZEND_DECLARE_MODULE_GLOBALS(extest)

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(extest)
{
	ZEND_INIT_MODULE_GLOBALS(extest, NULL, NULL);

	PHP_MINIT(extest_serialize)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(extest)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(extest)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "extest support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ extest_functions[]
 */
const zend_function_entry extest_functions[] = {
	PHP_FE_END
};
/* }}} */

/* {{{ extest_module_entry
 */
zend_module_entry extest_module_entry = {
	STANDARD_MODULE_HEADER,
	"extest",
	extest_functions,
	PHP_MINIT(extest),
	PHP_MSHUTDOWN(extest),
	NULL,
	NULL,
	PHP_MINFO(extest),
	"0.1", /* Replace with version number for your extension */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EXTEST
ZEND_GET_MODULE(extest)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
