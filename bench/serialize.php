<?php

$static = new ExtestSerializeS;
$dynamic = new ExtestSerializeD;

for ($i = 0; $i < EXTEST_NUM_EXAMS; $i++) {
	echo "STATIC" . PHP_EOL;
	$static->setExam($i);
	echo serialize($static) . PHP_EOL;

	echo "DYNAMIC" . PHP_EOL;
	$dynamic->setExam($i);
	echo serialize($dynamic) . PHP_EOL;
}