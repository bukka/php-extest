--TEST--
Test function ExtestCompat::__construct() by creating object
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec);
?>
--EXPECT--
object(ExtestCompat)#1 (2) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
}
