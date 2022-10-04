#!/usr/bin/php
<?PHP
if ($argc == 2 && file_exists($argv[1]))
{
    $file = file_get_contents($argv[1]);
    $dom = new DOMDocument;
    $dom->loadHTML($file);
    foreach ($dom->getElementsByTagName('a') as $node)
    {
        $temp = $node->nodeValue;
        $file = str_replace($temp, strtoupper($temp), $file);
        $temp = $node->getAttribute("title");
        $file = str_replace($temp, strtoupper($temp), $file);
    }
}
print($file);
?>