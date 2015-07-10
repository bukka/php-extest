--TEST--
Test function extest_compat_cstrl_rv() by calling it
--FILE--
<?php
var_dump(extest_compat_cstrl_rv());
?>
--EXPECTF--
string(21) "cstr_rv with len test"
