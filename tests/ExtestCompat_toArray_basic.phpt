--TEST--
Test function ExtestCompat::toArray() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec->toArray());
?>
--EXPECT--
array(1) {
  ["name"]=>
  string(5) "hello"
}
