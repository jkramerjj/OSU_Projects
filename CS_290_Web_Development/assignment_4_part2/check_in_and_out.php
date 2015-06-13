<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

include 'super_secret__file__.php';
$id_holder;

// This is used to change the status of a video TO --> CHECKED IN
	if (isset($_POST['video_check_in'])) {
		$id_holder = $_POST['video_related_id'];
		if (!($stmt = $mysqli->prepare("UPDATE video_tbl SET rented = 1 WHERE id = '$id_holder'"))) 
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		if (!$stmt->execute()) 
			echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
	}
		
	// This is used to change the status of a video TO --> CHECKED OUT
	if (isset($_POST['video_check_out'])) {
		$id_holder = $_POST['video_related_id'];
		//echo "the checked ot id == $id";
		if (!($stmt = $mysqli->prepare("UPDATE video_tbl SET rented = 0 WHERE id = '$id_holder'"))) 
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		if (!$stmt->execute()) 
			echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;        
	}
	
// Used to go back to the main page
header('Location: index.php');

?>

