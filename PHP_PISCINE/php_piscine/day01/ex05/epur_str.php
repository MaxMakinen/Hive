#!/usr/bin/php
<?PHP
if ($argc == 2)
{
	$num = 1;
	$split = explode(" ", $argv[1]);
	$split = \array_diff($split, [""]);
	$split = \array_values($split);
	$length = count($split);
	print($split[0]);
	while ($num < $length)
	{
		print(" ".$split[$num]);
		$num += 1;
	}
	print("\n");
}
?>