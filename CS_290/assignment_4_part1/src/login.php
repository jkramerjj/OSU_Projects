<?php
	session_start();
	// This code is here incase someone tries to enter a page with logging in first or if the user logged out
	// it will destroy the current session either way. 
	if($_GET['error'] === "true" || $_GET['log_out'] === "true"){
		session_destroy();
	}
?>

<!DOCTYPE html>
<html>
<head>
<title>Assignment 4 login.php</title>
</head>
<body>
<form action="content1.php?okk=true" method="POST">
  <label>Enter User Name</label>
  <input type="text" name="username">
  <br>
  <input type="submit" name="login" value="Login">
</form>
</body>
</html>