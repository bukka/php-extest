--TEST--
Test function extest_compat_res_info_new() by calling it with its expected argument
--FILE--
<?php
var_dump(extest_compat_res_info_new("my resource"));
?>
--EXPECTF--
resource(%d) of type (Extest Compat Info)
