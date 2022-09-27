#!/usr/bin/php
<?PHP
if ($argc > 1)
{
	$num = 1;
	$total = array();
	$arr1 = array();
	$arr2 = array();
	$arr3 = array();
	while ($num < $argc)
	{
		$split = preg_split("/ +/", trim($argv[$num]));
		$total = array_merge($total, $split);
		$num += 1;
	}
	foreach ($total as $val) 
	{
		$test = substr($val, 0, 1);
		if (is_numeric($test)) 
			array_push($arr2, $val);
		else if (!ctype_alnum($test))
			array_push($arr3, $val);
		else 
			array_push($arr1, $val);
	} 
	natcasesort($arr1);
	sort($arr2);
	sort($arr3);
	foreach ($arr1 as $elem)
		print($elem."\n");
	foreach ($arr2 as $elem)
		print($elem."\n");
	foreach ($arr3 as $elem)
		print($elem."\n");
}
?>
