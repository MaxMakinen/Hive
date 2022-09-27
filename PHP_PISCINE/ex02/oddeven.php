#!/usr/bin/php
<?PHP
while (1)
{
	print("Enter a number: ");
	$input = fgets(STDIN);
	if ($input == FALSE)
	{
		print("\n");
		break;
	}
	$input = str_replace("\n", "", $input);
	if (!is_numeric($input))
	{
		printf("'%s' is not a number\n", $input);
		continue;
	}
	if ($input % 2)
		printf("The number %ld is odd\n", $input);
	else
		printf("The number %ld is even\n", $input);
}
?>