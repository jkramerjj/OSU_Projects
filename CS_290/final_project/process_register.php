<?php
	ini_set('session.save_path', './sessions');
	session_start();
	//error_reporting(E_ALL);
	//ini_set('display_errors', 'On');
	require 'db_connection.php'; 
	$username =  $_POST["username"] ;
	$username = strtolower($username);
	$password = md5(md5($_POST["password"])); // Double md5, because... why not! 
	$fname =  $_POST["fname"] ;
	$lname = $_POST["lname"] ;	
	
	$log_in_counter = 0;
	$sql = $mysqli->prepare("INSERT INTO users2(username, password, fname, lname, log_in_counter) VALUES('$username','$password','$fname','$lname', '$log_in_counter')");
	$sql->execute();
	$_SESSION['username'] = $username;	
	$_SESSION['password'] = $password;
	$_SESSION['fname'] = $fname;
	$_SESSION['lname'] = $lname;

	
?>
