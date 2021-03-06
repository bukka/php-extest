/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 2013-2016 Jakub Zelenka                             |
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

#ifndef PHP_EXTEST_SERIALIZE_H
#define PHP_EXTEST_SERIALIZE_H

PHP_MINIT_FUNCTION(extest_serialize);

PHP_METHOD(ExtestSerialize, __construct);
PHP_METHOD(ExtestSerialize, setExam);
PHP_METHOD(ExtestSerialize, getExam);
PHP_METHOD(ExtestSerialize, setGlobalExam);
PHP_METHOD(ExtestSerialize, getGlobalExam);

#endif	/* PHP_EXTEST_SERIALIZE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
