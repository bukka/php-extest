--TEST--
Test function ExtestCompat::readProp() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec->readProp());
$ec->prop = "test";
var_dump($ec->readProp());
?>
--EXPECTF--
string(7) "unknown"
string(4) "test"