<?PHP
function ft_split($input)
{
	$split = explode(" ", $input);
	$split = \array_diff($split, [""]);
	$split = \array_values($split);
	sort($split);
	return($split);
}
?>