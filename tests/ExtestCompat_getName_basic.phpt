--TEST--
Test function ExtestCompat::test() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
var_dump($ec->getName());
?>
--EXPECTF--
string(5) "hello"