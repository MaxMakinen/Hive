<?PHP
CLASS Color {
    PUBLIC $red = 0;
    PUBLIC $green = 0;
    PUBLIC $blue = 0;
    STATIC PUBLIC $verbose = FALSE;

    public function __construct(array $kwargs) {
        if (array_key_exists('rgb', $kwargs))
        {
            $rgb = intval($kwargs['rgb']);
            $this->red = $rgb >> 16 & 255;
            $this->green = $rgb >> 8 & 255;
            $this->blue = $rgb >> 0 & 255;
        }
        else if (isset($kwargs['red']) && isset($kwargs['green']) && isset($kwargs['blue']))
        {
            $this->red = intval($kwargs['red']);
            $this->green = intval($kwargs['green']);
            $this->blue = intval($kwargs['blue']);
        }
        if (self::$verbose === TRUE) {
            printf("Color( red: %3d, green: %3d, blue: %3d ) constructed\n", $this->red, $this->green, $this->blue);
        }
        return;
    }
    public function __destruct() {
        if (self::$verbose === TRUE)
            printf("Color( red: %3d, green: %3d, blue: %3d ) destructed\n", $this->red, $this->green, $this->blue);
        return;
    }
    public function __toString() {
        return sprintf("Color( red: %3d, green: %3d, blue: %3d )", $this->red, $this->green, $this->blue);
    }
    public function add(Color $rhs) {
        return new Color(array(
        'red' => $this->red + $rhs->red, 
        'green' => $this->green + $rhs->green, 
        'blue' => $this->blue + $rhs->blue));
    }
    public function sub(Color $rhs) {
        return new Color(array(
        'red' => $this->red - $rhs->red, 
        'green' => $this->green - $rhs->green, 
        'blue' => $this->blue - $rhs->blue));
    }
    public function mult($f) {
        return new Color(array(
        'red' => $this->red * $f, 
        'green' => $this->green * $f, 
        'blue' => $this->blue * $f));
    }
    public static function doc(){
        if (file_exists("Color.doc.txt")) {
            return file_get_contents("Color.doc.txt") . PHP_EOL;
        }
    }
}

