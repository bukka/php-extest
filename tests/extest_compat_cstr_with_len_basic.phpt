--TEST--
Test function extest_compat_cstr_with_len() by calling it
--FILE--
<?php
var_dump(extest_compat_cstr_with_len());
?>
--EXPECTF--
string(18) "cstr with len test"