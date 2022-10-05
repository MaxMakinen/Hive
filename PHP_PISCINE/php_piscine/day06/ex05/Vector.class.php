<?PHP

require_once 'Color.class.php';
require_once 'Vertex.class.php';

class Vector
{
	private $_x;
    private $_y;
    private $_z;
    private $_w = 0.0;
    public static $verbose = FALSE;

    public function __construct( array $kwargs )
    {
		if ( isset( $kwargs['orig'] ) ){
			$orig = $kwargs['orig'];
		}
		else {
			$orig = new Vertex( array( 'x' => 0.0, 'y' => 0.0, 'z' => 0.0));
		}
		if ( isset( $kwargs['dest'] ) ) {

            $this->_x = $kwargs['dest']->_x - $orig->_x;
            $this->_y = $kwargs['dest']->_y - $orig->_y;
            $this->_z = $kwargs['dest']->_z - $orig->_z;
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
        return sprintf( "Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f )", $this->_x, $this->_y, $this->_z, $this->_w );
    }
    public static function doc(){
        if ( file_exists( "Vector.doc.txt" ) ) {
            return file_get_contents( "Vector.doc.txt" ) . PHP_EOL;
        }
    }
	public function __get($att) {
		if ($att == '_x')
			return $this->_getX();
		if ($att == '_y')
			return $this->_getY();
		if ($att == '_z')
			return $this->_getZ();
		if ($att == '_w')
			return $this->_getW();
	}
	private	 function _getX() {
		return $this->_x;
	}
	private function _getY() {
		return $this->_y;
	}
	private function _getZ() {
		return $this->_z;
	}
	private function _getW() {
		return $this->_w;
	}
	public function magnitude() {
		$value = sqrt($this->_x ** 2 +
		$this->_y ** 2 + 
		$this->_z **2);
		if ($value == 1)
			return "norm";
		else
			return $value;
	}
	public function normalize() {
		$magnitude = $this->magnitude();
		if ($magnitude === "norm")
			return clone $this;
		else {
			return new Vector( array('dest' =>
				new Vertex( array(
					'x' => $this->_x / $magnitude,
					'y' => $this->_y / $magnitude,
					'z' => $this->_z / $magnitude
				))));
		}
	}
	public function add( Vector $rhs) {
		return new Vector( array('dest' =>
		new Vertex( array(
			'x' => $this->_x + $rhs->_x,
			'y' => $this->_y + $rhs->_y,
			'z' => $this->_z + $rhs->_z
		))));

	}
	public function sub( Vector $rhs) {
		return new Vector( array('dest' =>
		new Vertex( array(
			'x' => $this->_x - $rhs->_x,
			'y' => $this->_y - $rhs->_y,
			'z' => $this->_z - $rhs->_z
		))));

	}
	public function opposite() {
		return new Vector( array('dest' =>
		new Vertex( array(
			'x' => $this->_x * (-1),
			'y' => $this->_y * (-1),
			'z' => $this->_z * (-1)
		))));

	}
	public function scalarProduct( $k ) {
		return new Vector( array('dest' =>
		new Vertex( array(
			'x' => $this->_x * $k,
			'y' => $this->_y * $k,
			'z' => $this->_z * $k
		))));

	}
	public function dotProduct( Vector $rhs) {
		return (float)($this->_x * $rhs->_x + $this->_y * $rhs->_y + $this->_z * $rhs->_z);
	}
	public function crossProduct( Vector $rhs) {
		return new Vector( array('dest' => new Vertex( array(
			'x' => $this->_y * $rhs->_z - $this->_z * $rhs->_y,
			'y' => $this->_z * $rhs->_x - $this->_x * $rhs->_z,
			'z' => $this->_x * $rhs->_y - $this->_y * $rhs->_x
		))));
	}
	public function cos( Vector $rhs) {
		$m1 = $this->magnitude();
		$m2 = $rhs->magnitude();
		if ($m1 == "norm" || $m2 == "norm")
			return (0);
		else
			return ($this->dotProduct($rhs) / ($m1 * $m2));
	}
}
?>