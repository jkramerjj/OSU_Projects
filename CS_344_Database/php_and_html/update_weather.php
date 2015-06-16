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

if (isset($_POST['update_weather'])) {
    $enter_if = true; // This is used as a sentinal to check if data was inputted correctly
    $new_name = $_POST['new_name'];
    $id       = $_POST['sky_weatherID'];
    
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("UPDATE sky_weather SET typical_weather='$new_name' WHERE id='$id' "))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;    
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
   
    header('Location: update_db_link.php');   
}

?>