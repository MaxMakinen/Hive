#!/usr/bin/php
<?PHP
	include("ft_is_sort.php");
	$tab = array("!/@#;^", "42", "Hello World", "hi", "zZzZzZz");
	$tab[] = "What are we doing now ?";
	$tib = $tab;
	sort($tib);
	if (ft_is_sort($tab))
		echo "The array is sorted\n";
	else
		echo "The array is not sorted\n";
	if (ft_is_sort($tib))
		echo "The array is sorted\n";
	else
		echo "The array is not sorted\n";
?>