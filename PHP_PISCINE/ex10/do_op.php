#!/usr/bin/php
<?PHP
if ($argc == 4)
{
	$num1 = trim($argv[1]);
	$op = trim($argv[2]);
	$num2 = trim($argv[3]);
	if (is_numeric($num1) && is_numeric($num2))
	{
		if ($op === "+")
			print($num1 + $num2."\n");
		else if ($op === "-")
			print($num1 - $num2."\n");
		else if ($op === "*")
			print($num1 * $num2."\n");
		else if ($op === "/")
			print($num1 / $num2."\n");
		else if ($op === "%")
			print($num1 % $num2."\n");
		else
			print("Incorrect Parameters\n");
	}
	else
		print("Incorrect Parameters\n");
}
else
	print("Incorrect Parameters\n");
?>