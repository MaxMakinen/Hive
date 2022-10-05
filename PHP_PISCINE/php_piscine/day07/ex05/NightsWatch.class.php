<?PHP

class Nightswatch{
    public $recuits = [];
    public function recruit($char){
            $this->recruits[] = $char;
    }
    public function fight(){
        foreach($this->recruits as $soldier){
            if (method_exists($soldier, 'fight'))
             $soldier->fight();
        }
    }
}
?>