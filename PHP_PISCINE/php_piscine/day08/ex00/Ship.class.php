<?PHP

trait Ship {
	protected $_player;
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
    protected $_facing;
	protected $_fill = [];
	private $_facings = array('up', 'down', 'left', 'right');
    private $_position = [];
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
            $this->_position['x'] = $pos['x'];
            $this->_position['y'] = $pos['y'];
        }
        return $this->_position;
    }
    function getPosition(){
        return $this->_position;
    }
	function getName(){
		return $this->_name;
	}
	function getPlayer(){
		return $this->_player;
	}
	function getFacing(){
		return $this->_facing;
	}
	function setFacing($newFacing){
		if (in_array($newFacing, $this->_facings))
			$this->_facing = $newFacing;
		else
			print('ILLEGAL FACING'.PHP_EOL);
	}
	private function setFill(){
		unset($this->_fill);
		$this->_fill = [];
		$half_len = (int)$this->_size['len'] / 2;
		$pX = $this->_position['x'];
		$pY = $this->_position['y'];
		if ($this->_facing === 'right') {
			for ($i = 0; $i < $this->_size['width']; $i++){
				$start = $pY - $half_len;
				for ($j = 0; $j < $this->_size['len']; $j++){
					$this->_fill[] = array('x' => $pX + $i, 'y' => $start + $j);
				}
			}
		}
		else if ($this->_facing === 'left') {
			for ($i = 0; $i < $this->_size['width']; $i++){
				$start = $pY + $half_len;
				for ($j = 0; $j < $this->_size['len']; $j++){
					$this->_fill[] = array('x' => $pX - $i, 'y' => $start - $j);
				}
			}
		}
		else if ($this->_facing === 'up') {
			for ($i = 0; $i < $this->_size['width']; $i++){
				$start = $pX - $half_len;
				for ($j = 0; $j < $this->_size['len']; $j++){
					$this->_fill[] = array('x' => $start + $j, 'y' => $pY + $i);
				}
			}
		}
		else if ($this->_facing === 'down') {
			for ($i = 0; $i < $this->_size['width']; $i++){
				$start = $pY + $half_len;
				for ($j = 0; $j < $this->_size['len']; $j++){
					$this->_fill[] = array('x' => $start - $j, 'y' => $pY - $i);
				}
			}
		}
	}
	function getFill(){
		return $this->_fill;
	}
    function __destruct(){}
}
?>