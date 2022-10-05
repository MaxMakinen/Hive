<?PHP
class UnholyFactory{

    public $recruits = [];
    public $template = [];

    public function absorb($soldier)
    {
        if (get_parent_class($soldier) === 'Fighter')
        {
            
            if (in_array($soldier, $this->recruits))
                print("(Factory already absorbed a fighter of type ".$soldier->type.")".PHP_EOL);
            else
            {
                $this->recruits[] = $soldier;
                $this->template[] = $soldier->type;
                print("(Factory absorbed a fighter of type ".$soldier->type.")".PHP_EOL);
            }
        }
        else
            print("(Factory can't absorb this, it's not a fighter)".PHP_EOL);
    }
    public function fabricate($soldier)
    {
        $key = array_search($soldier, $this->template);
        if ($key !== FALSE)
        {
            print("(Factory fabricates a fighter of type ".$soldier.")".PHP_EOL);
            return $this->recruits[$key];
        }
        else
            print("(Factory hasn't absorbed any fighter of type ".$soldier.")".PHP_EOL);
    }

}
?>