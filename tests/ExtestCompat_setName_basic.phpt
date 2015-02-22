--TEST--
Test function ExtestCompat::setName() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
$ec->setName("test");
var_dump($ec->getName());
?>
--EXPECTF--
string(4) "test"