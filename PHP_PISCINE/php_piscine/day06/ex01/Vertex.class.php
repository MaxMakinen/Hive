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
            printf( "Vertex(  x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) constructed\n", $this->_x, $this->_y, $this->_y, $this->_w, $this->_color->__toString() );
        }
        return;
    }
    public function __destruct() {
        if (self::$verbose === TRUE)
            printf("Vertex(  x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) destructed\n", $this->_x, $this->_y, $this->_y, $this->_w, $this->_color->__toString() );
        return;
    }
    public function __toString(  ) {
        $str = sprintf( "Vertex(  x: %.2f, y: %.2f, z:%.2f, w:%.2f", $this->_x, $this->_y, $this->_y, $this->_w );
        if ( self::$verbose === TRUE )
            $str = $str.", ".$this->_color->__toString();
        return $str." )";

    }
    public static function doc(  ){
        if ( file_exists( "Vertex.doc.txt" ) ) {
            return file_get_contents( "Vertex.doc.txt" ) . PHP_EOL;
        }
    }
}
?>