<?PHP
if (array_key_exists("action", $_GET))
    {
        if ($_GET["action"] === "set")
            setcookie($_GET["name"], $_GET["value"], time() + 3600);
        else if ($_GET["action"] === "get")
        {
            if (($name = $_GET["name"]) && $_COOKIE[$name])
                echo $_COOKIE[$name]. "\n";
        }
        else if ($_GET["action"] === "del")
            setcookie($_GET["name"], "", -1);
    }
?>