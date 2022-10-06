<?PHP

require_once 'Board.class.php';

interface IShip {
    function changeHull($value);
    function getHull();
    function changePP($value);
    function getPP();
    function resetPP();
    function setLastMove($move);
    function getLastMove();
    function setShield($valu);
    function getShield();
    function getWeapons();
    function setPosition( array $pos);
    function getPosition();
}
?>