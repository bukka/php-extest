--TEST--
Test function extest_compat_res_stat_new() by calling it with its expected argument
--FILE--
<?php
var_dump(extest_compat_res_stat_new(3));
?>
--EXPECTF--
resource(%d) of type (Extest Compat Stat)
