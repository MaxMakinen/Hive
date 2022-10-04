<?PHP
$path = "../private";
$file = $path."/passwd";
if ($_POST["login"] && $_POST["passwd"] && $_POST["submit"] === "OK")
{
    if (!file_exists($path))
    {
        mkdir($path);
    }
    if (!file_exists($file))
    {
        file_put_contents($file, NULL);
    }
    $content = unserialize(file_get_contents($file));
    foreach ($content as $key => $val)
    {
        if ($_POST["login"] === $val["login"])
        {
            echo "ERROR\n";
            exit;
        }
    }
    $user["login"] = $_POST["login"];
    $user["passwd"] = hash("whirlpool", $_POST["passwd"]);
    $content[] = $user;
    file_put_contents($file, serialize($content));
    echo "OK\n";
}
else
{
    echo "ERROR\n";
}
?>