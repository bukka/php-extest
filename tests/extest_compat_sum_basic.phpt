--TEST--
Test function extest_compat_sum() by calling it with its expected arguments
--FILE--
<?php
// errors
extest_compat_sum();
extest_compat_sum(0, 2);
extest_compat_sum(2, 2);
// valid sums
var_dump(extest_compat_sum(0));
var_dump(extest_compat_sum(1, 2));
var_dump(extest_compat_sum(2, 1, 2));
var_dump(extest_compat_sum(5, 1, 2, 3, 4, 5));
?>
--EXPECTF--
Warning: extest_compat_sum() expects at least 1 parameter, 0 given in %s

Warning: extest_compat_sum(): Invalid number of arguments in %s

Warning: extest_compat_sum(): Invalid number of arguments in %s
int(0)
int(2)
int(3)
int(15)
