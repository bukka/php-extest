--TEST--
Test function extest_compat_dump() by calling it with its expected arguments
--FILE--
<?php
extest_compat_dump();
extest_compat_dump(1);
extest_compat_dump(1, "test", 2.11);
?>
--EXPECT--
Number of items to dump: 0
Number of items to dump: 1
int(1)
Number of items to dump: 3
int(1)
string(4) "test"
float(2.11)
