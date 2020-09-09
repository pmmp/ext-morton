--TEST--
Test that morton3d_decode() produces the same results as morton3d_encode() consumes
--SKIPIF--
<?php if(!extension_loaded("morton")) die("skip: extension not loaded"); ?>
--FILE--
<?php

foreach([
	[0, 0, 0],
	[1, 1, 1],
	[1, 2, 3],
	[0xfffff, 1, 0],
	[1, 0xfffff, 0],
	[1, 0, 0xfffff],
	[-1, 0, 1],
	[0, -1, 1],
	[0, 1, -1],
	] as $k => [$x, $y, $z]){
	[$nX, $nY, $nZ] = morton3d_decode(morton3d_encode($x, $y, $z));
	if($nX !== $x || $nY !== $y || $nZ !== $z){
		echo "mismatch with set $k: expected $x $y $z, got $nX $nY $nZ\n";
	}
}
echo "ok\n";
?>
--EXPECT--
ok
