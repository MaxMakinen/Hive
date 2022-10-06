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
	public function getShips() {
		$fleet = [];
		foreach ($this->_ships as $ship) {
			$fleet[] = array(
				'type' => 'ship', 
				'position' => $ship->getPosition(),
				'fill' => $ship->getFill(),
				'symbol' => 'S',
				'ship' => $ship,
				'player' => $ship->getPlayer()
			);
		}
		return $fleet;
	}
    private function _populateShips( array $fleet){
		if ($this->_name === 'Player1')
			$face = 'up';
		else
			$face = 'left';
        #if( $fleet === 1)
            $this->_ships[] = new Ironclad( array('name' => $this->_name.'\'s fighter', 
			'position' => $fleet[1], 
			'player' => $this->_name, 
			'facing' => $face));
    }
}
?>