<?PHP
require_once 'Vector.class.php';

class Matrix {
	private $_scale;
	private $_angle;
	private $_vtc;
	private $_fov;
	private $_ratio;
	private $_near;
	private $_far;
	private $_matrix;
	public static $verbose = FALSE;

	const IDENTITY = "IDENTITY";
	const SCALE = "SCALE";
	const RX = "Ox ROTATION";
	const RY = "Oy ROTATION";
	const RZ = "Oz ROTATION";
	const TRANSLATION = "TRANSLATION";
	const PROJECTION = "PROJECTION";

    public function __construct( array $kwargs ) {
		if (isset($kwargs['preset'])){
			if ($kwargs['preset'] == self::IDENTITY){
				$this->init_matrix(1.0);
			}
			else if ($kwargs['preset'] == self::SCALE){
				$this->init_matrix($kwargs['scale']);
			}
			else if ($kwargs['preset'] == self::RX){
				$this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['y']['y'] = $cos;
				$this->_matrix['z']['y'] = $sin;
				$this->_matrix['y']['z'] = $sin * (-1);
				$this->_matrix['z']['z'] = $cos;
			}
			else if ($kwargs['preset'] == self::RY){
				$this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['x']['x'] = $cos;
				$this->_matrix['z']['x'] = $sin * (-1);
				$this->_matrix['x']['z'] = $sin;
				$this->_matrix['z']['z'] = $cos;

			}
			else if ($kwargs['preset'] == self::RZ){
				$this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['x']['x'] = $cos;
				$this->_matrix['x']['y'] = $sin * (-1);
				$this->_matrix['y']['x'] = $sin;
				$this->_matrix['y']['y'] = $cos;
			}
			else if ($kwargs['preset'] == self::TRANSLATION){
				$this->init_matrix(1.0);
				$this->_matrix['x']['w'] = $kwargs['vtc']->_x;
				$this->_matrix['y']['w'] = $kwargs['vtc']->_y;
				$this->_matrix['z']['w'] = $kwargs['vtc']->_z;
			}
			else if ($kwargs['preset'] == self::PROJECTION){
				$this->init_matrix(0.0);
				$fov = 1 / tan(0.5 * deg2rad($kwargs['fov']));
				$viewDiff = $kwargs['far'] - $kwargs['near'];
				$this->_matrix['x']['x'] = $fov / $kwargs['ratio'];
				$this->_matrix['y']['y'] = $fov;
				$this->_matrix['z']['z'] = -1 * (($kwargs['far'] + $kwargs['near']) / $viewDiff);
				$this->_matrix['z']['w'] = -1 * ((2 * $kwargs['far'] * $kwargs['near']) / $viewDiff);
				$this->_matrix['w']['z'] = -1.0;
				$this->_matrix['w']['w'] = 0.0;
			}
			if ( self::$verbose === TRUE ) {
				$str = "Matrix ".$kwargs['preset'];
				if ($kwargs['preset'] !== self::IDENTITY)
					$str = $str." preset";
				print($str." instance constructed" . PHP_EOL);
			}
		}
		return;
	}
    public function __toString() {
		return sprintf("M | vtcX | vtcY | vtcZ | vtxO\n-----------------------------\nx | %.2f | %.2f | %.2f | %.2f\ny | %.2f | %.2f | %.2f | %.2f\nz | %.2f | %.2f | %.2f | %.2f\nw | %.2f | %.2f | %.2f | %.2f", 
		$this->_matrix['x']['x'], $this->_matrix['x']['y'], $this->_matrix['x']['z'], $this->_matrix['x']['w'],
		$this->_matrix['y']['x'], $this->_matrix['y']['y'], $this->_matrix['y']['z'], $this->_matrix['y']['w'],
		$this->_matrix['z']['x'], $this->_matrix['z']['y'], $this->_matrix['z']['z'], $this->_matrix['z']['w'],
		$this->_matrix['w']['x'], $this->_matrix['w']['y'], $this->_matrix['w']['z'], $this->_matrix['w']['w']);
    }
	public function __destruct() {
        if (self::$verbose === TRUE)
            print("Matrix instance destructed" . PHP_EOL);
        return;
    }
    public static function doc(){
        if ( file_exists( "Matrix.doc.txt" ) ) {
            return file_get_contents( "Matrix.doc.txt" ) . PHP_EOL;
        }
    }
	private function init_matrix( $num ){
		$this->_matrix = array(
			'x' => array('x' => $num, 'y' => 0.0, 'z' => 0.0, 'w' => 0.0),
			'y' => array('x' => 0.0, 'y' => $num, 'z' => 0.0, 'w' => 0.0),
			'z' => array('x' => 0.0, 'y' => 0.0, 'z' => $num, 'w' => 0.0),
			'w' => array('x' => 0.0, 'y' => 0.0, 'z' => 0.0, 'w' => 1.0));
	}
	public function mult(){
		
	}
}
?>