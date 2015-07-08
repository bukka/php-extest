--TEST--
Test function ExtestCompat::__get_gc() by setting property
--FILE--
<?php
$ec = new ExtestCompat();
var_dump((array) $ec);
$ec->foo = "bar";
var_dump((array) $ec);
echo "SUCCESS";
?>
--EXPECT--
array(2) {
  ["prop"]=>
  NULL
  ["name"]=>
  string(5) "hello"
}
array(3) {
  ["prop"]=>
  NULL
  ["name"]=>
  string(5) "hello"
  ["foo"]=>
  string(3) "bar"
}
SUCCESS
