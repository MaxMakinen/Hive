#!/usr/bin/php
<?PHP
if ($argc == 2)
{
	$keys = fgetcsv(STDIN, 1000, ";");
	$total = array();
	$num = 0;
	$len = 0;
	$count = 0;
	while (($data = fgetcsv(STDIN, 1000, ";")) !== FALSE)
	{
		if ($len < 2)
			print_r($data);
		$len++;
		$deets = array(array_combine($keys, $data));
		$total = array_merge($total, $deets);
	}
	$len = 0;
	$lom = 0;
	echo count($total)."\n";
	if (!strcmp("average", $argv[1]))
	{
		$num = 0;
		foreach($total as $elem)
		{
			echo $num."\n";
			if (strcmp("moulinette", $elem[$keys[2]]) && $elem[$keys[1]])
			{
				if (strcmp($elem[$keys[0]], $elem[$keys[2]]))
				{
					if ($elem[$keys[1]])
					{
						$num += $elem[$keys[1]];
						$len++;
					}
				}
			}
			$lom++;
		}
		echo $lom."\n";
		printf("%f ; %f ; %f\n", $num, $len, $num / $len);
	}
}
?>