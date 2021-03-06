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

#ifndef PHP_EXTEST_H
#define PHP_EXTEST_H

#include "php.h"

extern zend_module_entry extest_module_entry;
#define phpext_extest_ptr &extest_module_entry

#ifdef PHP_WIN32
#	define PHP_EXTEST_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_EXTEST_API __attribute__ ((visibility("default")))
#else
#	define PHP_EXTEST_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_EXTEST_SERIALIZE 0
#define PHP_EXTEST_COMPAT    1

ZEND_BEGIN_MODULE_GLOBALS(extest)
	long exam;
ZEND_END_MODULE_GLOBALS(extest)

#ifdef ZTS
#define EXTEST_G(v) TSRMG(extest_globals_id, zend_extest_globals *, v)
#else
#define EXTEST_G(v) (extest_globals.v)
#endif

ZEND_EXTERN_MODULE_GLOBALS(extest)

#endif	/* PHP_EXTEST_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
