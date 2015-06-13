<?php
	ini_set('session.save_path', './sessions');
	session_start();
	
	require 'db_connection.php'; 
	$username =  $_SESSION['username'] ;
	$password = $_SESSION['password'] ; 
	$fname =  $_SESSION['fname'] ;
	$lname = $_SESSION['lname'] ;	
	
	$notFound = true;
	echo "<link rel='stylesheet' type='text/css' href='assets/styles.css'>";
	//echo "username == $username\n";
// Designed to catch duplicate usernames  and to transfer correct loggins to the db landingpage
if(isset($_SESSION['username'])) 
{	
	$userName = $_SESSION['username'];
	$password = $_SESSION['password']; 

	
	$qryy = $mysqli->prepare("SELECT username, password, log_in_counter FROM users2");
	$qryy->execute();
	$qryy->bind_result($userNameHolder, $passwordHolder, $log_in_counter);
	while($qryy->fetch()) 
	{
		//echo "UserNameHolder = $userNameHolder <br> username = $username<br>";
		if ($userNameHolder == $userName && $log_in_counter == 200)
		{			
			echo ("<script type=text/javascript src=transfer_back.js></script>");
			echo ("<script> username_taken()</script>");
			exit();
		}	
	}			
}

if ($notFound)
{
	echo ("<script type=text/javascript src=transfer_back.js></script>");
	echo ("<script> trsnf_land_page()</script>");
	exit();
}

	
?>