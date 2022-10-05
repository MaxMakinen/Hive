<?PHP
class Targaryen {
    public function getBurned() {
        if ($this->resistsFire() == TRUE)
            return "emerges naked but unharmed";
        else
            return "burns alive";
    }
    public function resistsFire() {
		return FALSE;
	}
}
?>