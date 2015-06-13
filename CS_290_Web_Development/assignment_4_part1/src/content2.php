<?php
session_start();
error_reporting(E_ALL);
ini_set('display_errors', 'On');

// Used to validate if a "username" has been entered. 
if (!isset($_SESSION['visits'])) {
    //echo "made it to first if<br/>";
    header('Location: login.php?error=true');
}

echo "WELCOME TO CONTENT 2!!!! THERE IS NOTHING HAPPENING HERE EXCEPT FOR TEXT YELLING AT YOU!!!! ";
echo "<br><br>";
echo "Click <a href='content1.php?okk=false'>here</a> If you'd like to leave this mean place and go back to content1.php";

?>