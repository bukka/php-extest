--TEST--
Test function extest_compat_cstr() by calling it
--FILE--
<?php
var_dump(extest_compat_cstr());
?>
--EXPECTF--
string(9) "cstr test"