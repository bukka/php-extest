--TEST--
Test function extest_compat_cstr_rv() by calling it
--FILE--
<?php
var_dump(extest_compat_cstr_rv());
?>
--EXPECTF--
string(12) "cstr_rv test"
