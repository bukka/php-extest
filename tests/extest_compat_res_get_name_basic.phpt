--TEST--
Test function extest_compat_res_get_name() by calling it
--FILE--
<?php
$res = extest_compat_res_new("my resource");
var_dump(extest_compat_res_get_name($res));
?>
--EXPECTF--
string(11) "my resource"
