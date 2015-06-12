<?php
ini_set('session.save_path', './sessions');
session_start(); 
include('db_connection.php');

// Used to fetch the user entered usersname and password 
if(!isset($_SESSION['username'])) {	
	$userName = $_POST['username']; 
	$userName = strtolower($userName);
	$password = md5(md5($_POST["password"])); // Double md5, because... why not! 	
	
	$qry = $mysqli->prepare("SELECT username, password FROM users2");
	$qry->execute();
	$qry->bind_result($userNameHolder, $passwordHolder); 
	while($qry->fetch()) {
		if ($userNameHolder == $userName && $passwordHolder == $password){
			$_SESSION['username'] = $userNameHolder;
			$_SESSION['password'] = $passwordHolder;
		}					
	}		
}

?>
