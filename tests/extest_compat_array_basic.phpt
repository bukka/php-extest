--TEST--
Test function extest_compat_array() by calling it with its expected arguments
--FILE--
<?php
$a = array(
	'key1' => 23,
	'key2' => "data",
);
var_dump(extest_compat_array($a));
?>
--EXPECTF--
NO STRING
STRING
NULL
