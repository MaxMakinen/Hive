<?PHP

require_once 'Board.class.php';

class Ironclad extends Board implements IShip {
    
    use Ship;
    
    public function __construct(array $kvars)
    {
        $this->_name = $kvars['name'];
        $this->position = $kvars['position'];
        $this->_size = array('len' => 7, 'width' => 2);
        $this->_sprite = 'X';
        $this->_sprite = 'x';
        $this->_hullPoints = 8;
        $this->_enginePower = 12;
        $this->_origPP = 12;
        $this->_speed = 10;
        $this->_handling = 5;
        $this->_shield = 2;
        $this->_weapons = ['NL', 'NL'];
    }
    function __destruct(){}
}
?>