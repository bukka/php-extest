--TEST--
Test function extest_compat_str() by calling it with its expected arguments
--FILE--
<?php
var_dump(extest_compat_str("test data"));
?>
--EXPECTF--
str_val(9): test data
str_ptr_val(9): test data
str_ptr(9): test data
half string(4) : "test"
double string(18) : "test datatest data"
string(9) "test data"