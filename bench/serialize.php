<?php

$iters = isset($argv[1]) ? $argv[1] : 100000;

$static = new ExtestSerializeS;
$dynamic = new ExtestSerializeD;
$custom = new ExtestSerializeC;

function test_serialization($object) {
	global $iters;
	
	// output serialization
	echo serialize($object) . PHP_EOL;
	$start = microtime(true);
	for ($j = 0; $j < $iters; $j++) {
		serialize($object);
	}
	$end = microtime(true);
	$duration = $end - $start;
	printf("time for %d iterations: %f" . PHP_EOL, $iters, $duration);
}

for ($i = 0; $i < EXTEST_NUM_EXAMS; $i++) {
	echo "---- EXAM $i ----" . PHP_EOL;

	echo "STATIC" . PHP_EOL;
	$static->setExam($i);
	test_serialization($static);
	
	echo "DYNAMIC" . PHP_EOL;
	$dynamic->setExam($i);
	test_serialization($dynamic);

	echo "CUSTOM" . PHP_EOL;
	$custom->setExam($i);
	test_serialization($custom);

	echo PHP_EOL;
}