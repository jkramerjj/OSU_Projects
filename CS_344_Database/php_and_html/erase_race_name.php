<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

$host      = "oniddb.cws.oregonstate.edu";
$uesr_name = "kramerj-db";
$pw        = "tG3rQiqxNJpYSZmf";

$done="done";

$mysqli = new mysqli($host, $uesr_name, $pw, $uesr_name);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL Database: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

if (isset($_POST['erase_race_name'])) {
    $enter_if = true; // This is used as a sentinal to check if data was inputted correctly
    $erase_name = $_POST['race_name'];
 
    
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("DELETE FROM sky_race WHERE name='$erase_name' "))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;    
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
   
    header("Location: erase_db_link.php"); 
}

?>