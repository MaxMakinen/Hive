<?PHP
$path = "../private";
$file = $path."/passwd";
if ($_POST["login"] && $_POST["oldpw"] && $_POST["newpw"] && $_POST["submit"] === "OK")
{
    $content = unserialize(file_get_contents($file));
    $oldpw = hash("whirlpool", $_POST["oldpw"]);
    $newpw = hash("whirlpool", $_POST["newpw"]);
    foreach ($content as $key => $value)
    {
        if ($value["login"] === $_POST["login"] && $oldpw === $value["passwd"] && $oldpw !== $newpw)
        {
            $content[$key]["passwd"] = $newpw;
            file_put_contents($file, serialize($content));
            echo "OK\n";
            return;
        }
    }
}
echo "ERROR\n";
return;
?>