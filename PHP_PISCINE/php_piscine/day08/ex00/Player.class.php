<?PHP

require_once 'Board.class.php';

class Player extends Board {

    private $_ships = [];
    private $_name;
    
    public function __construct( array $kvarg)
    {
        $this->_name = $kvarg['name'];
        $this->_populateShips( array($kvarg['fleet'], $kvarg['start']));
    }
    function __destruct(){}
    private function _populateShips( array $fleet){
        if( $fleet[0] === 1)
            $this->_ships[] = new Ironclad( array('name' => $this->_name.'s fighter', 'position' => $$fleet[1]));
    }
}
?>