--TEST--
Test function extest_compat_res_dump() by calling it with its expected argument
--FILE--
<?php
$res_info = extest_compat_res_info_new("my resource");
$res_stat = extest_compat_res_stat_new(4);

extest_compat_res_dump($res_info);
extest_compat_res_dump($res_stat);
?>
--EXPECTF--
INFO resource (name: my resource)
STAT resource (count: 4)
