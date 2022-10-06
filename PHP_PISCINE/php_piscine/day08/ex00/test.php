<?php
require_once 'Board.class.php';
require_once 'Player.class.php';
require_once 'IShip.class.php';
require_once 'Ship.class.php';
require_once 'Ironclad.class.php';

$board = new Board;
print_r($board->throwDice(4));
print("end".PHP_EOL);
?>