--TEST--
Test function ExtestCompat::__get_gc() by setting property
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec);
$ec->foo = "bar";
var_dump($ec);
echo "SUCCESS";
?>
--EXPECT--
object(ExtestCompat)#1 (2) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
}
object(ExtestCompat)#1 (3) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
  ["foo"]=>
  string(3) "bar"
}
SUCCESS
