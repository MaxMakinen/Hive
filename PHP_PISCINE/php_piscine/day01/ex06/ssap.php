#!/usr/bin/php
<?PHP
if ($argc > 1)
{
	$num = 1;
	$total = array();
	while ($num < $argc)
	{
		$split = explode(" ", $argv[$num]);
		$split = \array_diff($split, [""]);
		$total = array_merge($total, $split);
		$num += 1;
	}
	sort($total);
	foreach ($total as $elem)
		print($elem."\n");
}
?>