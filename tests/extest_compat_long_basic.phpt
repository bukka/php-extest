--TEST--
Test function extest_compat_long() by calling it with its expected arguments
--FILE--
<?php
var_dump(extest_compat_long(4000, "str", false));
var_dump(extest_compat_long(4000, "str", true));
?>
--EXPECTF--
SIZE - long: 3; int: 3
LONG - long: 4000; int: 4000
int(4000)
SIZE - long: 3; int: 3
LONG - long: 4000; int: 4000
int(4000)
