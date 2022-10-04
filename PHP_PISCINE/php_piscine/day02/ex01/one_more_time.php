#!/usr/bin/php
<?PHP
$le_months = array(
    "Janvier" => "January", 
    "Février" => "February", 
    "Mars" => "March", 
    "Avril" => "April", 
    "Mai" => "May", 
    "Juin" => "June", 
    "Juillet" => "July", 
    "Août" => "August", 
    "Septembre" => "September", 
    "Octobre" => "October", 
    "Novembre" => "November", 
    "Décembre" => "December");
$le_days = array(
    "Lundi" => "Monday",
    "Mardi" => "Tuesday",
    "Mercredi" => "Wednesday",
    "Jeudi" => "Thursday",
    "Vendredi" => "Friday",
    "Samedi" => "Saturday",
    "Dimanche" => "Sunday");
if ($argc == 2)
{
    $date = explode(" ", ucwords($argv[1]));
    $time = explode(":", $date[4]);
    $day = $le_days[$date[0]];
    $month = $le_months[$date[2]];
    if (count($date) !== 5 || count($time) !== 3 || !$day || !$month)
    {
        echo "Wrong Format\n";
        exit (-1);
    }
    $tim1 = strtotime($date[1]."-".$month."-".$date[3]." ".$date[4]);
    $tim2 = strtotime("1970-01-01 01:00:00");
    echo $tim1 - $tim2, "\n";
}
?>