--TEST--
Test function extest_compat_array_gen() by calling it
--FILE--
<?php

var_dump(extest_compat_array_gen());
?>
--EXPECT--
array(28) {
  [0]=>
  bool(true)
  [1]=>
  int(5)
  [2]=>
  float(5.1)
  [3]=>
  string(18) "str_next_index_val"
  [4]=>
  string(19) "cstr_next_index_val"
  [5]=>
  string(20) "cstrl_next_index_val"
  [6]=>
  string(19) "zval_next_index_val"
  [10]=>
  bool(false)
  [11]=>
  int(4)
  [12]=>
  float(4.1)
  [13]=>
  string(13) "str_index_val"
  [14]=>
  string(14) "cstr_index_val"
  [15]=>
  string(15) "cstrl_index_val"
  [16]=>
  string(8) "zval_val"
  ["bool"]=>
  bool(true)
  ["long"]=>
  int(3)
  ["double"]=>
  float(3.1)
  ["str"]=>
  string(13) "str_assoc_val"
  ["cstr"]=>
  string(14) "cstr_assoc_val"
  ["cstrl"]=>
  string(15) "cstrl_assoc_val"
  ["zval"]=>
  string(14) "zval_assoc_val"
  ["bool_ex"]=>
  bool(false)
  ["long_ex"]=>
  int(2)
  ["double_ex"]=>
  float(2.1)
  ["str_ex"]=>
  string(16) "str_assoc_val_ex"
  ["cstr_ex"]=>
  string(17) "cstr_assoc_val_ex"
  ["cstrl_ex"]=>
  string(18) "cstrl_assoc_val_ex"
  ["zval_ex"]=>
  string(17) "zval_assoc_val_ex"
}