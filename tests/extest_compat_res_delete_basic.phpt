--TEST--
Test function extest_compat_res_delete() by calling it with its expected argument
--FILE--
<?php
$res_info = extest_compat_res_info_new("my resource");
var_dump($res_info);
extest_compat_res_delete($res_info);
var_dump($res_info);
?>
--EXPECTF--
resource(%d) of type (Extest Compat Info)
resource(%d) of type (Unknown)
