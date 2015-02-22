--TEST--
Test function ExtestCompat::getName() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec->getName());
?>
--EXPECTF--
string(5) "hello"