<?php

error_reporting(E_ALL);
ini_set('display_errors', 'On');
session_start();

// Srouce: I used http://php.net/manual/en/book.json.php
if($_POST != NULL) {
    $json_object = json_encode($_POST);
	//echo "MADE IT!!";
    echo ("{Type:[POST]parameters: $json_object");
} 
 
 // This is here incase the info is sent in as GET (Which I know it's not, because of the HTML I wrote, but just incase the 
 // PHP file is used somewhere else. 
 if($_GET != NULL) {
    $json_object = json_encode($_POST);
       echo ("{Type:[GET]parameters: $json_object");
   } 
 
?>
