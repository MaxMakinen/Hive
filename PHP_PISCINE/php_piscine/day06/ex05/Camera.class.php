<?PHP

require_once 'Color.class.php';
require_once 'Vertex.class.php';
require_once 'Vector.class.php';
require_once 'Matrix.class.php';

class Camera
{
    private $_pos;
    private $_orient;
    private $_dir;
    private $_width;
    private $_height;
    private $_fov;
    private $_near;
    private $_far;
    private $_ratio;
    private $_proj;
    private $_tT;
    private $_tR;
    private $_tR2;
    public static $verbose = FALSE;

    public function __construct(array $kwargs)
    {
        if (
            isset($kwargs['origin'])
            && isset($kwargs['orientation'])
            && isset($kwargs['width'])
            && isset($kwargs['height'])
            && isset($kwargs['fov'])
            && isset($kwargs['near'])
            && isset($kwargs['far'])
        ) {
            $this->_pos = $kwargs['origin'];
            $this->_orient = $kwargs['orientation'];
            $this->_width = $kwargs['width'];
            $this->_height = $kwargs['height'];
            $this->_fov = $kwargs['fov'];
            $this->_near = $kwargs['near'];
            $this->_far = $kwargs['far'];
            if ($kwargs['width'] > $kwargs['height'])
                $this->_ratio = $kwargs['width'] / $kwargs['height'];
            else
                $this->_ratio = $kwargs['height'] / $kwargs['width'];
            $this->_dir = new Vector(array('dest' => $this->_pos));
            $this->_tT = new Matrix(array('preset' => Matrix::TRANSLATION, 'vtc' => $this->_dir->opposite()));
            $this->_tR = $this->_orient->transpose();
            $this->_tR2 = $this->_tR->mult($this->_tT);
            $this->_proj = new Matrix(array(
                'preset' => Matrix::PROJECTION,
                'fov' => $kwargs['fov'],
                'ratio' => $this->_ratio,
                'near' => $kwargs['near'],
                'far' => $kwargs['far']
            ));
        }
        if (self::$verbose === TRUE) {
            print("Camera instance constructed" . PHP_EOL);
        }
        return;
    }
    public function __destruct() {
        if (self::$verbose === TRUE)
            print("Camera instance destructed" . PHP_EOL);
        return;
    }
    public function __toString()
    {
        return sprintf(
            "Camera( " . PHP_EOL .
                "+ Origine: " . $this->_pos . PHP_EOL .
                "+ tT:" . PHP_EOL . $this->_tT . PHP_EOL .
                "+ tR:" . PHP_EOL . $this->_tR . PHP_EOL .
                "+ tR->mult( tT ):" . PHP_EOL . $this->_tR2 . PHP_EOL .
                "+ Proj:" . PHP_EOL . $this->_proj . PHP_EOL .
                ")");
    }
    public static function doc()
    {
        if (file_exists("Camera.doc.txt")) {
            return file_get_contents("Camera.doc.txt") . PHP_EOL;
        }
    }

    public function watchVertex(Vertex $vertex)
    {
        $screen = $this->_proj->transformVertex($vertex);
        $screen->_x = $screen->_x / -$screen->_z;
        $screen->_y = $screen->_y / -$screen->_z;
        if (abs($screen->_x) > $this->_width || abs($screen->_y) > $this->_height)
            return (new Vertex(array('x' => 0, 'y' => 0, 'z' => 0)));
        $screen->_x = ($screen->_x + $this->_width / 2) / $this->_width;
        $screen->_y = ($screen->_y + $this->_height / 2) / $this->_height;
        return (new Vertex(array(
            'x' => floor($screen->_x * $this->_width),
            'y' => floor((1 - $screen->_y) * $this->height)
        )));
    }
}
?>