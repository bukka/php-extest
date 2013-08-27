<?php

$static = new ExtestSerializeS;
$dynamic = new ExtestSerializeD;
$custom = new ExtestSerializeC;

for ($i = 0; $i < EXTEST_NUM_EXAMS; $i++) {
	echo "STATIC" . PHP_EOL;
	$static->setExam($i);
	echo serialize($static) . PHP_EOL;

	echo "DYNAMIC" . PHP_EOL;
	$dynamic->setExam($i);
	echo serialize($dynamic) . PHP_EOL;

	echo "CUSTOM" . PHP_EOL;
	$custom->setExam($i);
	echo serialize($custom) . PHP_EOL;

}