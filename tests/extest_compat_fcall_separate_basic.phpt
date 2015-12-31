--TEST--
Test function extest_compat_fcall_separate() by calling it with its expected argument
--FILE--
<?php
function test($b, $c) {
	var_dump($b, $c);
}

var_dump(extest_compat_fcall_separate("test"));
?>
--EXPECT--
int(11)
string(5) "param"
NULL
