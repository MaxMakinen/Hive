<?PHP

require_once 'Player.class.php';
require_once 'IShip.class.php';
require_once 'Ship.class.php';
require_once 'Ironclad.class.php';

class Board{
    private $_players = [];
    private $_board = [];
    private $_boardObjects = [];
    private $_turnCount = 0;
    function __construct()
    {
        $this->_board = array_fill(0, 100, array_fill(0, 150 , 0));
        $this->_createObstacles(20);
        $this->_players[] = new Player( array('name' => 'Player1', 'fleet' => 1, 'start' => array('x' => 50, 'y' => 50)));
        $this->_players[] = new Player( array('name' => 'Player2', 'fleet' => 1, 'start' => array('x' => 50, 'y' => 100)));
		$this->_addFleets();
        $this->_populateBoard();
        print($this);
	#	print_r($this->_boardObjects);

    }
    function __destruct(){}
    private function _rollDice($num) {
        $dice = [];
        while ($num > 0)
        {
            $dice[] = random_int(1,6);
            $num--;
        }
        return $dice;
    }
    private function _createObstacles($num){
		while ($num > 0) {
            $x = rand(0, 99);
            $y = rand(0, 149);
            $this->_boardObjects[] = array(
				'type' => 'obstacle', 
				'position' => array('x' => $x, 'y' => $y), 
				'symbol' => 'A');
            $num--;
		}
	}
	private function _addFleets() {
		foreach ($this->_players as $player) {
			$this->_boardObjects = array_merge($this->_boardObjects, $player->getShips());
		}
	}
	private function _populateBoard(){
		foreach ($this->_boardObjects as $item) {
			if ($item['type'] === 'obstacle') {
				$x = $item['position']['x'];
				$y = $item['position']['y'];
				$this->_board[$x][$y] = $item['symbol'];
			}
			else if ($item['type'] === 'ship') {
				foreach ($item['fill'] as $pos) {
					$this->_board[$pos['x']][$pos['y']] = $item['symbol'];
				}
#				$x = $item['position']['x'];
#				$y = $item['position']['y'];
#				$this->_board[$x][$y] = $item['symbol'];
			}
        }
    }
    public function checkWin(){
        if ($this->_players[0]->checkShips == FALSE){
            print("player 2 win".PHP_EOL);
            return TRUE;
        }
        if ($this->_players[1]->checkShips == FALSE){
            print("player 1 win".PHP_EOL);
            return TRUE;
        }
        else
            return FALSE;
    }
    public function __toString()
    {
        $str = "";
        foreach ($this->_board as $line){
			foreach ($line as $key) {
				if ($key === 0)
					$str = $str.'.';
				else
					$str = $str.$key;
			}
			$str = $str.PHP_EOL;
        }
        return $str;
    }
    private function _placeShip($ship, $position){
        if ($this->_board[$position['x']][$position['y']] === 0)
        {
            $this->_board[$position['x']][$position['y']] = $ship;
            $ship->changePos($position);
            return TRUE;
        }
        else
            return FALSE;
        }
    private function _removeShip($ship, $position){
        if ($this->_board[$position['x']][$position['y']] === $ship)
        {
            $this->_board[$position['x']][$position['y']] = 0;
            $ship->clearPos();
            return TRUE;
        }
        else
            return FALSE;
    }
    private function _moveShip($ship, $newPosition){
        if ($this->_board[$newPosition->y][$newPosition->y] === 0) {
            $this->_removeShip($ship, $ship->position);
            $this->_placeShip($ship, $newPosition);
            return TRUE;
        }
        else
            return FALSE;
    }
    public function __get($att){
        return $this->_get($att);
    }
    public function __set($att, $val){
        $this->_set($att, $val);
    }
    private function _get($att){
        if ($att == 'ship')
        return $this->_board['x']['y'];
    }
    private function _set($att, $val){
        if ($att == 'ship')
        $this->_board['x']['y'] = 'ship';
    }
    public function throwDice($num){
        return $this->_rollDice($num);
    }
}
?>