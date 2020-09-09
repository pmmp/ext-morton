--TEST--
Test that morton2d_decode() produces the same results as morton2d_encode() consumes
--SKIPIF--
<?php if(!extension_loaded("morton")) die("skip: extension not loaded"); ?>
--FILE--
<?php

foreach([
	[0, 0],
	[1, 1],
	[1, 2],
	[0x7fffffff, 1],
	[1, 0x7fffffff],
	[-1, 0],
	[0, -1],
	] as [$x, $y]){
	[$nX, $nY] = morton2d_decode(morton2d_encode($x, $y));
	if($nX !== $x || $nY !== $y){
		echo "mismatch: expected $x $y, got $nX $nY\n";
	}
}
echo "ok\n";
?>
--EXPECT--
ok
