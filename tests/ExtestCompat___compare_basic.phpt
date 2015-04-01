--TEST--
Test function ExtestCompat::__compare() [internal] by comparing object
--FILE--
<?php
$ec1 = new ExtestCompat();
$ec1->setName("a");
$ec2 = new ExtestCompat();
$ec2->setName("b");
var_dump($ec1 <= $ec2);
?>
--EXPECT--
bool(true)
