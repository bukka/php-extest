--TEST--
Test function ExtestCompat::test() by calling it
--FILE--
<?php
$ec = new ExtestCompat();
$ec->test();
?>
--EXPECTF--
ExtestCompat TEST - name: hello, type: 1