<?PHP
function ft_is_sort($input)
{
	$compare = $input;
	sort($compare);
	if ($input == $compare)
		return (TRUE);
	else
		return (FALSE);
}
?>