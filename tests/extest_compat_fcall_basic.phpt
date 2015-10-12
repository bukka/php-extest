--TEST--
Test function extest_compat_cstrl_rv() by calling it
--FILE--
<?php
function test($a, $b) {
	var_dump($a, $b);
}

var_dump(extest_compat_fcall("test"));
?>
--EXPECTF--
int(11)
string(5) "param"
NULL
