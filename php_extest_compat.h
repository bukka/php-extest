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

#ifndef PHP_EXTEST_COMPAT_H
#define PHP_EXTEST_COMPAT_H

PHP_MINIT_FUNCTION(extest_compat);

PHP_FUNCTION(extest_compat_long);
PHP_FUNCTION(extest_compat_str);
PHP_FUNCTION(extest_compat_cstr);
PHP_FUNCTION(extest_compat_cstrl);
PHP_FUNCTION(extest_compat_array);

PHP_METHOD(ExtestCompat, test);
PHP_METHOD(ExtestCompat, setName);
PHP_METHOD(ExtestCompat, getName);
PHP_METHOD(ExtestCompat, toArray);
PHP_METHOD(ExtestCompat, toArrayAlt);

extern const zend_function_entry extest_compat_functions[];

#endif	/* PHP_EXTEST_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
