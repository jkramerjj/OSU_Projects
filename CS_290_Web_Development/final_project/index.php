<?php
	ini_set('session.save_path', './sessions');
	session_start();
	if($_GET['logout'] === "true"){
		session_destroy();		
	}	
?>

<!DOCTYPE html>
<html>
<head>
<title>Home Page - Skyrim Database</title>
<meta charset="utf-8" />
<link rel="stylesheet" type="text/css" href="assets/styles/rests.css">
<link rel="stylesheet" type="text/css" href="assets/styles/styles.css">
<!--The following script tag downloads a font from the Adobe Edge Web Fonts server for use within the web page. We recommend that you do not modify it.-->
<script>var __adobewebfontsappname__="dreamweaver"</script>
<script src="http://use.edgefonts.net/source-code-pro:n2:default.js" type="text/javascript"></script>
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
    <h2 class="back_up">Welcome to the Skyrim Database</h2>
    <p>Here you can log and track information about your character. We know you love your characters, so we have allowed for multiple characters to be stored under your UserName</p>
<p>If your a new user here is a list of some of the things you can do!</p>
    <ul>
     <li>Load your characters name</li>
	<li>Save their race</li>
	<li>Save their sex</li>
	<li>Save their favorite weapon</li>
	<li>And of-course, upload a picture!</li>
    </ul>
    <h2>Why use a create a database account?</h2>
    <p>Essentially it a fantastic way to track your characters. Because the Skyrim world is so expansive, you're bound to make more then a few characters to explore. This database will help you keep track of your characters, plus upload some pictures to remind you of you journey through the Skyrim universe. </p>
    
   
  </div>
</div>
</body>
</html>























