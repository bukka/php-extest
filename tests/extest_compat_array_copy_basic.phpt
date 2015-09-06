--TEST--
Test function extest_compat_array_copy() by calling it with its expected argument
--FILE--
<?php
$arr = array(
	'str1',
	20,
	1.2
);

var_dump(extest_compat_array_copy($arr));
?>
--EXPECT--
array(3) {
  [0]=>
  string(4) "str1"
  [1]=>
  int(20)
  [2]=>
  float(1.2)
}
