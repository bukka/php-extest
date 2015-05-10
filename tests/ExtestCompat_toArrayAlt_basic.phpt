--TEST--
Test function ExtestCompat::toArrayAlt() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec->toArrayAlt());
?>
--EXPECT--
array(1) {
  ["name"]=>
  string(5) "hello"
}
