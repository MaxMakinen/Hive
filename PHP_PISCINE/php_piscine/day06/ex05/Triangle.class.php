<?PHP
require_once 'Color.class.php';
require_once 'Vertex.class.php';
require_once 'Vector.class.php';
require_once 'Matrix.class.php';

class Triangle{

    private $_a;
    private $_b;
    private $_c;
	public static $verbose = FALSE;    
    public function __construct( array $kwarg ){
        if (isset($kwarg['A']) && isset($kwarg['B']) && isset($kwarg['C'])){
            $this->_a = $kwarg['A'];
            $this->_b = $kwarg['B'];
            $this->_c = $kwarg['C'];
        }
        if (self::$verbose === TRUE) {
            print("Triangle instance constructed" . PHP_EOL);
        }
        return;
    }
    public function __destruct()
    {
        if (self::$verbose === TRUE) {
            print("Triangle instance destructed" . PHP_EOL);
        }
    }
    public static function doc()
	{
		if (file_exists("Triangle.doc.txt")) {
			return file_get_contents("Triangle.doc.txt") . PHP_EOL;
		}
	}
    public function __get($att) {
		if ($att == '_a')
			return $this->_getA();
		if ($att == '_b')
			return $this->_getB();
		if ($att == '_c')
			return $this->_getC();
	}
	private	function _getA() {
		return $this->_a;
	}
	private function _getB() {
		return $this->_b;
	}
	private function _getC() {
		return $this->_c;
	}
}
?>