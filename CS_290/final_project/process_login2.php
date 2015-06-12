<?php
ini_set('session.save_path', './sessions');
session_start(); 
include('db_connection.php');
echo "<link rel='stylesheet' type='text/css' href='assets/styles.css'>";

// Designed to catch no password or username issues and to transfer correct loggins to the db landingpage
if(isset($_SESSION['username'])) 
{
	$userName = $_SESSION['username'];
	$userName = strtolower($userName);
	$password = $_SESSION['password'];
	
	$qry = $mysqli->prepare("SELECT username, password FROM users2");
	$qry->execute();
	$qry->bind_result($userNameHolder, $passwordHolder); 
	while($qry->fetch()) 
	{
		if ($userNameHolder == $userName && $passwordHolder == $password)
		{				
			echo ("<script type=text/javascript src=transfer_back.js></script>");
			echo ("<script> trsnf_land_page()</script>");
			exit();
		}	
	}			
}
else 
{	
	echo ("<script type=text/javascript src=transfer_back.js></script>");
	echo ("<script>badUserPW()</script>");						
}
?>
