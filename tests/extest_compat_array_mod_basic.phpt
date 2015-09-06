--TEST--
Test function extest_compat_array_mod() by calling it with its expected argument
--FILE--
<?php
$empty = array();
$indexed = array(
	'str1',
	20,
    1.2
);
$assoc = array(
	'key1' => 'str1',
	'key2' => 20,
	'key3' => 1.22,
	'key4' => true,
	'key5' => null
);
echo "EMPTY\n";
extest_compat_array_mod($empty);
echo "\nINDEXED\n";
extest_compat_array_mod($indexed);
var_dump($indexed);
echo "\nASSOC\n";
extest_compat_array_mod($assoc);
var_dump($assoc);
?>
--EXPECTF--
EMPTY

INDEXED
Deleting value 1:
int(20)
Value exists : no
array(3) {
  [0]=>
  string(4) "str1"
  [2]=>
  float(1.2)
  [1]=>
  string(6) "index1"
}

ASSOC
Deleting value key1:
string(4) "str1"
Value exists : no
Deleting value key2:
int(20)
Value exists : no
Deleting value key3:
float(1.22)
Value exists : no
array(5) {
  ["key4"]=>
  bool(true)
  ["key5"]=>
  NULL
  ["key1"]=>
  string(5) "key1v"
  ["key2"]=>
  string(5) "key2v"
  ["key3"]=>
  string(5) "key3v"
}
