<?PHP

use BaconQrCode\Renderer\Module\EdgeIterator\Edge;

require_once 'Color.class.php';
require_once 'Camera.class.php';
require_once 'Vertex.class.php';
require_once 'Vector.class.php';
require_once 'Matrix.class.php';

class Render{

    private $_width;
    private $_height;
    private $_name;
    const VERTEX = 'vertex';
    const EDGE = 'edge';
    const RASTERIZE = 'raster';
    public static $verbose = FALSE;  
    public function __construct( array $kwargs)
    {
        if (isset($kwargs['width']) && isset($kwargs['height']) && isset($kwargs['filename'])){
            $this->_width = $kwargs['width'];
            $this->_height = $kwargs['height'];
            $this->_name = $kwargs['filename'];
        }
        if (self::$verbose === TRUE) {
            print("Render instance constructed" . PHP_EOL);
        }
        return;
    }
    public function __destruct()
    {
        if (self::$verbose === TRUE) {
            print("Render instance destructed" . PHP_EOL);
        }
    }
    public static function doc()
	{
		if (file_exists("Render.doc.txt")) {
			return file_get_contents("Render.doc.txt") . PHP_EOL;
		}
	}
}
?>