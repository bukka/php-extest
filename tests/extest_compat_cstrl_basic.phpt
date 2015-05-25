--TEST--
Test function extest_compat_cstrl() by calling it
--FILE--
<?php
var_dump(extest_compat_cstrl());
?>
--EXPECTF--
string(18) "cstr with len test"