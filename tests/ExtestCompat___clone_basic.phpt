--TEST--
Test function ExtestCompat::__clone() by cloning object
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec);
$ecc = clone $ec;
var_dump($ecc);
$ec->setName("dataaa");
$eccc = clone $ec;
var_dump($eccc);
?>
--EXPECT--
object(ExtestCompat)#1 (2) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
}
object(ExtestCompat)#2 (2) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
}
object(ExtestCompat)#3 (2) {
  ["prop"]=>
  NULL
  ["name_debug"]=>
  string(5) "hello"
}
