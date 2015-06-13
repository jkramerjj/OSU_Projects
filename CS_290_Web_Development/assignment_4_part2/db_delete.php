<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

include 'super_secret__file__.php';

// This will delete all data in the database. This is a clean sweep! 
// I chose to use TRUNCATE because it starts the ID counter over at 1. 
if (isset($_POST['video_delete_all'])) {
    $stmt = $mysqli->prepare("TRUNCATE video_tbl");
    $stmt->execute();
}

// This is used to go back to the main page
header('Location: index.php');

?>

