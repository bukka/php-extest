<?php
$c = new ExtestSerializeC;


for ($i = 0; $i < EXTEST_NUM_EXAMS; $i++) {
	ExtestSerialize::setGlobalExam($i);
	$c->setExam($i);
	echo "---- EXAM $i ----" . PHP_EOL;
	$s = serialize($c);
	echo "Serialized: $s" . PHP_EOL;
	unserialize($s);
}