<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

$host      = "oniddb.cws.oregonstate.edu";
$uesr_name = "kramerj-db";
$pw        = "tG3rQiqxNJpYSZmf";

$mysqli = new mysqli($host, $uesr_name, $pw, $uesr_name);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL Database: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

// This will delete all data in the database. This is a clean sweep! 
// I chose to use TRUNCATE because it starts the ID counter over at 1. 

if (isset($_POST['delete_all'])) {
	    
    $stmt = $mysqli->prepare("TRUNCATE sky_faction_category");
    $stmt->execute();
    $stmt = $mysqli->prepare("TRUNCATE sky_people");
    $stmt->execute();
    $stmt = $mysqli->prepare("TRUNCATE sky_faction");
    $stmt->execute();
    $stmt = $mysqli->prepare("TRUNCATE sky_race");
    $stmt->execute();
    $stmt = $mysqli->prepare("TRUNCATE sky_kingdom");
    $stmt->execute();
	$stmt = $mysqli->prepare("TRUNCATE sky_weather");
    $stmt->execute();
    
    header('Location: erase_db_link.php');   
}

?>