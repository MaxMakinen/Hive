<?PHP
include_once('Lannister.class.php');
class Jaime extends Lannister{
    public function sleepWith( $char) {
        if (get_parent_class($char) !== get_parent_class($this)){
            print("Let's do this.".PHP_EOL);
        }
        else if ($char instanceof Cersei)
            print("With pleasure, but only in a tower in Winterfell, then.".PHP_EOL);
        else {
            print("Not even if I'm drunk !".PHP_EOL);
        }
    }
}
?>