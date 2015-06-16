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

if (isset($_POST['update_weapon_used_name'])) {
    $enter_if   = true; // This is used as a sentinal to check if data was inputted correctly
    $last_name  = $_POST['last_name'];
    $first_name = $_POST['first_name'];
    
    $new_weapon_name = $_POST['new_weapon_name'];

    // This if statement code is for adding to the database. It uses the sentianl enter_if to decide if it should enter or not. 
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("UPDATE sky_people SET weapon='$new_weapon_name' WHERE first_name='$first_name' AND last_name = '$last_name' "))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;   
        }
    }
    header('Location: update_db_link.php');   
}

?>