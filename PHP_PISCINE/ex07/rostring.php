#!/usr/bin/php
<?PHP
if ($argc > 1)
{
	$num = 1;
	$split = explode(" ", $argv[1]);
	$split = \array_diff($split, [""]);
	$split = \array_values($split);
	$length = count($split);
	while ($num < $length)
	{
		print($split[$num]." ");
		$num += 1;
	}
	print($split[0]."\n");
}
?>