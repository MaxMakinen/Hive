<?PHP
$file = "../private/passwd";
function auth($login, $passwd)
{
    $content = unserialize(file_get_contents("../private/passwd"));
    $hashedpw = hash("whirlpool", $passwd);
    foreach ($content as $key => $value)
    {
        if ($value["login"] === $login && $value["passwd"] === $hashedpw)
        {
            return (TRUE);
        }
    }
    return (FALSE);
}
?>