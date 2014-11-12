--TEST--
Test function extest_compat_str() by calling it with its expected arguments
--FILE--
<?php
var_dump(extest_compat_str("test data"));
?>
--EXPECTF--
half string(4) : "test"
string(9) "test data"