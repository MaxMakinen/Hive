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
	const NEW = "NEW";

    public function __construct( array $kwargs ) {
		if (isset($kwargs['preset'])){
			if ($kwargs['preset'] == self::IDENTITY){
				$this->_matrix = $this->init_matrix(1.0);
			}
			else if ($kwargs['preset'] == self::SCALE){
				$this->_matrix = $this->init_matrix($kwargs['scale']);
			}
			else if ($kwargs['preset'] == self::RX){
				$this->_matrix = $this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['y']['y'] = $cos;
				$this->_matrix['z']['y'] = $sin;
				$this->_matrix['y']['z'] = $sin * (-1);
				$this->_matrix['z']['z'] = $cos;
			}
			else if ($kwargs['preset'] == self::RY){
				$this->_matrix = $this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['x']['x'] = $cos;
				$this->_matrix['z']['x'] = $sin * (-1);
				$this->_matrix['x']['z'] = $sin;
				$this->_matrix['z']['z'] = $cos;

			}
			else if ($kwargs['preset'] == self::RZ){
				$this->_matrix = $this->init_matrix(1.0);
				$cos = cos($kwargs['angle']);
				$sin = sin($kwargs['angle']);
				$this->_matrix['x']['x'] = $cos;
				$this->_matrix['x']['y'] = $sin * (-1);
				$this->_matrix['y']['x'] = $sin;
				$this->_matrix['y']['y'] = $cos;
			}
			else if ($kwargs['preset'] == self::TRANSLATION){
				$this->_matrix = $this->init_matrix(1.0);
				$this->_matrix['x']['w'] = $kwargs['vtc']->_x;
				$this->_matrix['y']['w'] = $kwargs['vtc']->_y;
				$this->_matrix['z']['w'] = $kwargs['vtc']->_z;
			}
			else if ($kwargs['preset'] == self::PROJECTION){
				$this->_matrix = $this->init_matrix(0.0);
				$fov = 1 / tan(0.5 * deg2rad($kwargs['fov']));
				$viewDiff = $kwargs['far'] - $kwargs['near'];
				$this->_matrix['x']['x'] = $fov / $kwargs['ratio'];
				$this->_matrix['y']['y'] = $fov;
				$this->_matrix['z']['z'] = -1 * (($kwargs['far'] + $kwargs['near']) / $viewDiff);
				$this->_matrix['z']['w'] = -1 * ((2 * $kwargs['far'] * $kwargs['near']) / $viewDiff);
				$this->_matrix['w']['z'] = -1.0;
				$this->_matrix['w']['w'] = 0.0;
			}
			else if ($kwargs['preset'] == self::NEW) {
				$this->_matrix = $kwargs['matrix'];
			}
			if ( self::$verbose === TRUE) {
				$str = "";
				if ($kwargs['preset'] !== self::NEW)
					$str = $kwargs['preset'];
				if ($kwargs['preset'] !== self::IDENTITY)
					$str = $str." preset";
				print("Matrix ".$str." instance constructed" . PHP_EOL);
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
		$matrix = array(
			'x' => array('x' => $num, 'y' => 0.0, 'z' => 0.0, 'w' => 0.0),
			'y' => array('x' => 0.0, 'y' => $num, 'z' => 0.0, 'w' => 0.0),
			'z' => array('x' => 0.0, 'y' => 0.0, 'z' => $num, 'w' => 0.0),
			'w' => array('x' => 0.0, 'y' => 0.0, 'z' => 0.0, 'w' => 1.0));
			return $matrix;
	}
	public function mult( Matrix $rhs){
		if ($this->isValid($rhs)){
			$matrix = $this->init_matrix(0.0);
			$keys = array('x', 'y', 'z', 'w');
			for ($ar1 = 0; $ar1 < 4; $ar1++) {
				for ($ar2 = 0; $ar2 < 4; $ar2++){
					$sum = 0;
					for ($index = 0; $index < 4; $index++){
						$sum += $this->_matrix[$keys[$ar1]][$keys[$index]] * 
						$rhs->_matrix[$keys[$index]][$keys[$ar2]];
					}
					$matrix[$keys[$ar1]][$keys[$ar2]] = $sum;
				}
			}
			return new Matrix(array('preset' => self::NEW, 'matrix' => $matrix));
		}
	}
	public function transformVertex (Vertex $vtx){
		$x = $this->_matrix['x']['x'] * $vtx->x + $this->_matrix['x']['y'] * $vtx->y + $this->_matrix['x']['z'] * $vtx->z + $this->_matrix['x']['w'] * $vtx->w;
		$y = $this->_matrix['y']['x'] * $vtx->x + $this->_matrix['y']['y'] * $vtx->y + $this->_matrix['y']['z'] * $vtx->z + $this->_matrix['y']['w'] * $vtx->w;
		$z = $this->_matrix['z']['x'] * $vtx->x + $this->_matrix['z']['y'] * $vtx->y + $this->_matrix['z']['z'] * $vtx->z + $this->_matrix['z']['w'] * $vtx->w;
		$w = $this->_matrix['w']['x'] * $vtx->x + $this->_matrix['w']['y'] * $vtx->y + $this->_matrix['w']['z'] * $vtx->z + $this->_matrix['w']['w'] * $vtx->w;
		return new Vertex(array('x' => $x, 'y' => $y,'z' => $z,'w' => $w));
	}
	private function isValid( Matrix $matrix) {
		if (array_key_exists('x', $matrix->_matrix) && array_key_exists('y', $matrix->_matrix) && array_key_exists('z', $matrix->_matrix)){
			if (array_key_exists('x', $matrix->_matrix) && array_key_exists('y', $matrix->_matrix) && array_key_exists('z', $matrix->_matrix))
				return (TRUE);
		}
		return (FALSE);
	}
}
?>