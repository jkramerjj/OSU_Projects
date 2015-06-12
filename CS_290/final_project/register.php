<?php
	ini_set('session.save_path', './sessions');
	session_start();
	//error_reporting(E_ALL);
	//ini_set('display_errors', 'On');
	//
	
	if($_GET['logout'] === "true"){
			session_destroy();
		}
	require_once 'db_connection.php'; 
?>

<!doctype html>
<html>
<head>
<meta charset="UTF-8">
<link rel="stylesheet" type="text/css" href="assets/styles/rests.css">
<link rel="stylesheet" type="text/css" href="assets/styles/styles.css">
<!--The following script tag downloads a font from the Adobe Edge Web Fonts server for use within the web page. We recommend that you do not modify it.-->
<script>var __adobewebfontsappname__="dreamweaver"</script>
<script src="http://use.edgefonts.net/source-code-pro:n2:default.js" type="text/javascript"></script>
<script type="text/javascript" src="assets/js/verify_register.js"></script>
<title>Skyrim - Register Page</title>
</head>
<body>

<div class="master">
  <header>
  <img src="assets/imgs/skyrim_logo.jpg" width="1680" height="228" alt=""/>
    <h1>Skyrim Database -- From Characters to Images</h1>
    <h3>By: Joseph Kramer</h3>
    <h3>CS290 -- Final Porject</h3>
  </header>
  <div class="navbar">
    <ul>
      <li class ="nav-content" > <a href="index.php">Home</a> </li>
      <li class ="nav-content"> <a href="register.php">Register</a> </li>
      <li class ="nav-content"> <a href="login.php">Login</a></li>      
    </ul>
  </div>
  <div class="main_1"> 

<h2>User Register</h2>

<form action="" method="post">	
	<table>
	 <tr><th>
	 	 <label for='name'>Username:</label>
		 </th><td>
		 <input type="text" name="username" id="username"> <br>
		 </td> </tr><tr><th>
		 <label for='category'>Password:</label>
		 </th><td>
		 <input type="password" name="password" id="password"><br>
		 </td></tr><tr><th>
		 <label for='length'>First Name:</label>
		 </th><td>
		 <input type="text" name="fname" id="fname"><br>
	 	 </td></tr><tr><th>
		 <label for='length'>Last Name:</label>
		 </th><td>
		 <input type="text" name="lname" id="lname"><br>
	 </td></tr>
	</table>
	<button onclick="javascript:register();return false" id="submit" class="button">Register</button>
	</form>
<p id="error"></p>
</body>
</html>
