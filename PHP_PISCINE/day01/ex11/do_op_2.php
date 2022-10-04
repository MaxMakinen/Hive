#!/usr/bin/php
<?PHP
if ($argc == 2)
{
	$split = preg_split("/ +/", trim($argv[1]));
	if (count($split) != 3)
	{
		print("Syntax Error\n");
		return (-1);
	}
	$num1 = $split[0];
	$op = $split[1];
	$num2 = $split[2];
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
			print("Syntax Error\n");
	}
	else
		print("Syntax Error\n");
}
else
	print("Incorrect Parameters\n");
?>