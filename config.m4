dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(extest, whether to enable extest support,
[  --enable-extest           Enable extest support])

if test "$PHP_EXTEST" != "no"; then
  AC_DEFINE(HAVE_EXTEST,1,[ ])
  PHP_NEW_EXTENSION(extest, extest.c extest_compat.c extest_serialize.c, $ext_shared)
fi
