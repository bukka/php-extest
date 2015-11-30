--TEST--
Test function extest_compat_res_info_get_name() by calling it with its expected argument
--FILE--
<?php
$res = extest_compat_res_info_new("my resource");
var_dump(extest_compat_res_info_get_name($res));
?>
--EXPECTF--
string(11) "my resource"
