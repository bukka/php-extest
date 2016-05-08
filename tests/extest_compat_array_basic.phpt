--TEST--
Test function extest_compat_array() by calling it with its expected arguments
--FILE--
<?php
$empty = array();
$indexed = array(
	'str1',
	20,
	1.22,
	true,
	null
);
$assoc = array(
	'key1' => 'str1',
	'key2' => 20,
	'key3' => 1.22,
	'key4' => true,
	'key5' => null
);
echo "EMPTY\n";
extest_compat_array($empty);
echo "\nINDEXED\n";
extest_compat_array($indexed);
echo "\nASSOC\n";
extest_compat_array($assoc);
?>
--EXPECTF--
EMPTY
array with 0 elements

INDEXED
array with 5 elements
index: 0
index: 1
index: 2
index: 3
index: 4
value type code: %d
string(4) "str1"
value type code: %d
int(20)
value type code: %d
float(1.22)
value type code: %d
bool(true)
value type code: %d
NULL
key: ""
value type code: %d
string(4) "str1"
key: ""
value type code: %d
int(20)
key: ""
value type code: %d
float(1.22)
key: ""
value type code: %d
bool(true)
key: ""
value type code: %d
NULL
index: 0
string(4) "str1"
index: 1
int(20)
index: 2
float(1.22)
index: 3
bool(true)
index: 4
NULL
index: 0
string(4) "str1"
index: 0
string(4) "str1"

ASSOC
array with 5 elements
key: "key1" (len: 4)
key: "key2" (len: 4)
key: "key3" (len: 4)
key: "key4" (len: 4)
key: "key5" (len: 4)
value type code: %d
string(4) "str1"
value type code: %d
int(20)
value type code: %d
float(1.22)
value type code: %d
bool(true)
value type code: %d
NULL
key: "key1"
value type code: %d
string(4) "str1"
key: "key2"
value type code: %d
int(20)
key: "key3"
value type code: %d
float(1.22)
key: "key4"
value type code: %d
bool(true)
key: "key5"
value type code: %d
NULL
key: "key1"
string(4) "str1"
key: "key2"
int(20)
key: "key3"
float(1.22)
key: "key4"
bool(true)
key: "key5"
NULL
key: "key1" (len: 4)
string(4) "str1"
key: "key1"
string(4) "str1"
