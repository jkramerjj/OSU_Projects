<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

$host = "oniddb.cws.oregonstate.edu";
$uesr_name = "kramerj-db";
$pw = "tG3rQiqxNJpYSZmf";

$mysqli = new mysqli($host, $uesr_name, $pw, $uesr_name);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL Database: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

?>