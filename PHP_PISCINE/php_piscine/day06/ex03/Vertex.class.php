<?PHP

require_once 'Color.class.php';

CLASS Vertex {
    private $_x;
    private $_y;
    private $_z;
    private $_w = 1.0;
    private $_color;
    public static $verbose = FALSE;

    public function __construct( array $kwargs )
    {
        if ( isset( $kwargs['x'] ) && isset( $kwargs['y'] ) && isset( $kwargs['z'] ) ) {
            $this->_x = $kwargs['x'];
            $this->_y = $kwargs['y'];
            $this->_z = $kwargs['z'];
            if ( isset( $kwargs['w'] ) ) {
                $this->_w = $kwargs['w'];
            }
            if ( isset( $kwargs['color'] ) ) {
                $this->_color = $kwargs['color'];
            }
            else {
                $this->_color = new Color( array( 'rgb' => 0xFFFFFFFF ) );
            }
        }
        if ( self::$verbose === TRUE ) {
            print($this." constructed" . PHP_EOL);
        }
        return;
    }
    public function __destruct() {
        if (self::$verbose === TRUE)
            print($this." destructed" . PHP_EOL);
        return;
    }
    public function __toString() {
        $str = sprintf( "Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f", $this->_x, $this->_y, $this->_z, $this->_w );
        if ( self::$verbose === TRUE )
            $str = $str.", ".$this->_color->__toString();
        return $str." )";

    }
    public static function doc(){
        if ( file_exists( "Vertex.doc.txt" ) ) {
            return file_get_contents( "Vertex.doc.txt" ) . PHP_EOL;
        }
    }
	public function __get($att) {
		if ($att == '_x')
			return $this->getX();
		if ($att == '_y')
			return $this->getY();
		if ($att == '_z')
			return $this->getZ();
		if ($att == '_w')
			return $this->getW();
		if ($att == '_color')
			return $this->getColor();
	}
	public function __set($att, $value) {
		if ($att == '_x')
			$this->setX($value);
		if ($att == '_y')
			$this->setY($value);
		if ($att == '_z')
			$this->setZ($value);
		if ($att == '_w')
			$this->setW($value);
		if ($att == '_color')
			$this->setColor($value);
	}
	private	 function getX() {
		return $this->_x;
	}
	private function getY() {
		return $this->_y;
	}
	private function getZ() {
		return $this->_z;
	}
	private function getW() {
		return $this->_w;
	}
	private function getColor() {
		return $this->_color;
	}
	private function setX( $num ) {
		$this->_x = $num;
	}
	private function setY( $num ) {
		$this->_y = $num;
	}
	private function setZ( $num ) {
		$this->_z = $num;
	}
	private function setW( $num ) {
		$this->_w = $num;
	}
	private function setColor( color $rgb ) {
		$this->_color = $rgb;
	}
}
?>