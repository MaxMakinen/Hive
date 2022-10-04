#!/usr/bin/php
<?PHP
if ($argc > 2)
{
	$key = $argv[1];
	$num = 2;
	$arr = array();
	$result = "";
	while ($num < $argc)
	{
		$split = explode(":", $argv[$num]);
		if (!strcmp($key, $split[0]) && count($split) == 2)
			$result = $split[1];
		$num++;
	}
	if ($result)
		print($result."\n");
}
?>