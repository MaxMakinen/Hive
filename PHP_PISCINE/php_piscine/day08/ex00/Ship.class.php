<?PHP

trait Ship {
    protected $_name;
    protected $_size;
    protected $_sprite;
    protected $_hullPoints;
    protected $_enginePower;
    protected $_origPP;
    protected $_speed;
    protected $_handling;
    protected $_shield;
    protected $_weapons;
    protected $_lastMove;
    public $position = [];
    public function resetPP() {
        $this->_enginePower = $this->_origPP;
    }
    function changeHull($value){
        if (is_numeric($value))
            $this->_hullPoints += $value;
        return $this->_hullPoints;
    }
    function getHull(){
        return $this->_hullPoints;
    }
    function changePP($value){
        if (is_numeric($value))
            $this->_enginePower += $value;
        return $this->_enginePower;
    }
    function getPP(){
        return $this->_enginePower;
    }

    function setLastMove($move){
        $this->_lastMove = $move;
    }
    function getLastMove(){
        return $this->_lastMove;
    }
    function setShield($value){
        if (is_numeric($value))
            $this->_shield += $value;
        return $this->_shield;
    }
    function getShield(){
        return $this->_shield;
    }
    function getWeapons(){
        return $this->_weapons;
    }
    function setPosition( array $pos){
        if (isset($pos['x']) && isset($pos['y'])){
            $this->position['x'] = $pos['x'];
            $this->position['y'] = $pos['y'];
        }
        return $this->position;
    }
    function getPosition(){
        return $this->position;
    }
    function __destruct(){}
}
?>