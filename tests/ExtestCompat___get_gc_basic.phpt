--TEST--
Test function ExtestCompat::__get_gc() by setting property
--FILE--
<?php
$ec = new ExtestCompat();
$ec->foo = "bar";
unset($ec);
echo "SUCCESS";
?>
--EXPECT--
SUCCESS
