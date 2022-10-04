#!/usr/bin/php
<?PHP
$split = preg_split("/[\n\s\t]+/", trim($argv[1]));
$num = 0;
print($split[0]);
foreach ($split as $elem)
{
    if ($num > 0)
    {
        print(" ".$elem);
    }
    $num++;
}
echo "\n";
?>