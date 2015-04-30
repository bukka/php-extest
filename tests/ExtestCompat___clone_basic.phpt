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
object(ExtestCompat)#1 (0) {
}
object(ExtestCompat)#2 (0) {
}
object(ExtestCompat)#3 (0) {
}
