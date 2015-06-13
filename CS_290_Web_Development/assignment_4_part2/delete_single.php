<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

include 'super_secret__file__.php';
$id_holder;

// This will delete a single video from the database. This is for when the user clicks
// the single delete button. 
if (isset($_POST['delete_single_video'])) {
    $id_holder = $_POST['video_related_id'];
    if (!($stmt = $mysqli->prepare("DELETE FROM video_tbl WHERE id = '$id_holder'"))) 
        echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
    if (!$stmt->execute()) 
        echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
}

// This is used to go back to the main page
header('Location: index.php');

?>




