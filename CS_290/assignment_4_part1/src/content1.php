<?php

error_reporting(E_ALL);
ini_set('display_errors', 'On');

$display_link_to_content2 = true;  // If set to false then the user did not enter anything and the normal display won't run

session_start();
if (!isset($_POST['username']) && !isset($_SESSION['visits'])) {
    // Found out about header at http://php.net/manual/en/function.header.php
    header('Location: login.php?error=true');
}
if (!($_GET['okk'] === "true")) {
    // I put this here to move the logic along. If I had the calling ahref use content1.pgp?okk=true, then I got a bunch of
    // errors. But if I set the if statement to lookf for !true, then it works.. So the junkvar is just that
    // only to move the logic along
    $junkvar = 0;
} else {
    // Checks if the user entered in any data. 
    if (session_status() == PHP_SESSION_ACTIVE) {
        if ($_POST['username'] == NULL || $_POST['username'] == ' ') {
            $display_link_to_content2 = false;
            session_destroy();
            echo " A username must be entered. Click <a href='login.php?error=true'>here</a>";
            echo " to return to the login sceen. ";            
        }
    }    
}

// display_link_to_content2 is used to verify if the user actually enentred something. 
if ($display_link_to_content2) {    
	// Enters this if statement if it's the users first time logged in
    if (!isset($_SESSION['visits'])) {
        $_SESSION['visits'] = 0;
        $username = $_POST['username'];
        $_SESSION['username'] = $username;
        //echo "made it to first if<br/>";      
        echo "Welcome, " . $_POST['username'] . " You have visited " . $_SESSION["visits"] . " times.";
        $_SESSION['visits']++;
        echo " Click <a href='login.php?log_out=true'>here</a> to logout";
        echo "<br/>";
        echo "<br/>";
        echo " Please enjoy content2 and click <a href='content2.php?'>here</a>";
	} 
	// Enter the else statement if its there >1 time being here
	else {
        //echo "made it to 2nd if<br/>";        
        echo "Welcome, " . $_SESSION['username'] . " You have visited " . $_SESSION["visits"] . " times.";
        $_SESSION['visits']++;
        echo " Click <a href='login.php?log_out=true'>here</a> to logout";        
        echo "<br/>";
        echo "<br/>";
        echo " Please enjoy content2 and click <a href='content2.php'>here</a>";
    }   
}
?>

