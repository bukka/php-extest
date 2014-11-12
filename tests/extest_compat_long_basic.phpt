--TEST--
Test function extest_compat_long() by calling it with its expected arguments
--FILE--
<?php
var_dump(extest_compat_long(4000, true));
?>
--EXPECTF--
int(4000)