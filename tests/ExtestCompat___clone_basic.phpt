--TEST--
Test function ExtestCompat::__clone() by cloning object
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec);
$ecc = clone $ec;
var_dump($ecc);
?>
--EXPECT--
object(ExtestCompat)#1 (0) {
}
object(ExtestCompat)#2 (0) {
}
