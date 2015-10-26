--TEST--
Test function extest_compat_fcall() by calling it with its expected argument
--FILE--
<?php
function test($a, $b, $c) {
	var_dump(isset($a), $b, $c);
}

var_dump(extest_compat_fcall("test"));
?>
--EXPECTF--
bool(false)
int(11)
string(5) "param"
NULL
