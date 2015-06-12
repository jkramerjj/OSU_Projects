<?php
ini_set('session.save_path', './sessions');
session_start();
require_once 'db_connection.php';
if (isset($_SESSION['username'])) {
  	$username = $_SESSION['username'];  
	
	// This is used to veriy that the user has logged in already and stop others from trying to use this name. 
	$log_in_counter = 200;
	$stmt = $mysqli->prepare("UPDATE users2 SET log_in_counter='$log_in_counter' WHERE username='$username' ");
    $stmt->execute();
/*	if($log_in_counter == 200){
	    echo "<script type=text/javascript src=transfer_back.js></script>";
		echo "IN HERE!!<br>";
	}
	$log_in_counter--;
	echo "logincounter == $log_in_counter<br>";*/
	} else {
	echo "<link rel='stylesheet' type='text/css' href='assets/styles.css'>";
    echo ("<h2 class='back_up'>** Error encountered -- Rerouting back to HomePage</h2>");
    echo "<script type=text/javascript src=transfer_back.js></script>";
    echo "<script >myFunction(); alertFunc()</script>";
    die();
}
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
<title>Skyrim Character Database</title>
</head>
<body>
<div class="master">
  <header>
  <img src="assets/imgs/skyrim_logo.jpg" width="1680" height="228" alt=""/> 
  </header>
  <div class="navbar">
    <ul>
      <li class ="nav-content" > <a href="index.php">Home</a> </li>
      <li class ="nav-content"> <a href="register.php">Register</a> </li>
      <li class ="nav-content"> <a href="index.php?logout=true">LogOut</a></li>      
    </ul>
  </div>
  <div class="main_1">
  <?php echo "<h1 class='color_change'>Welcome <span class='cap_first'>$username</span> to the Skyrim Database<h1>"; ?>
  <br>
<h3 class="color_change2">Add a new Chacter to the Database</h3>

<?php

if (isset($_POST['add_character'])) {
    //echo "MADE IT HERE!!!";
    $enter_if = true; // This is used as a sentinal to check if data was inputted correctly
    $name     = $_POST['name'];
    $race     = $_POST['race'];
    $sex      = $_POST['sex'];
    $age      = $_POST['age'];
    $weapon   = $_POST['weapon'];
    
    /*echo "signed in dude = $username<br>";
    echo "name= $name<br>";
    echo "race= $race<br>";
    echo "sex = $sex<br>";
    echo "age = $age<br>";
    echo "weapon = $weapon<br>";
    */    
    
    if (empty($name)) {
        $enter_if = false;
        echo "Please enter a Character Name";
    } else if (empty($race)) {
        $enter_if = false;
        echo "Please enter a Race Name";
    } else if (empty($sex)) {
        $enter_if = false;
        echo "Please enter a Sex";
    } else if (empty($age)) {
        $enter_if = false;
        echo "Please enter an Age";
    } else if (empty($weapon)) {
        $enter_if = false;
        echo "Please enter a Weapon";
    } else if (!is_numeric($age)) {
        $enter_if = false;
        echo "Please enter a number for Age";
    } else if (is_numeric($sex)) {
        $enter_if = false;
        echo "An integer is not a valid sex";
    }        
    else if ($enter_if == true) {
        $stmt = $mysqli->prepare("INSERT INTO users_skyrim2(username, char_name, race, sex, age, weapon) VALUES ('$username', '$name', '$race', '$sex', '$age', '$weapon')");
        $stmt->execute();
    }
	/*
	echo ("<script type=text/javascript src=transfer_back.js></script>");
	echo ("<script>trsnf_land_page2()</script>");*/
}
?>

<!--Form to enter in chacater data-->
<form action='db_landing_page.php' method='post'>
    <table>
        <tr>
            <td>
              <label for='name'>Character Name</label>
            </td>
            <td>
              <input type='text' name='name'>
            </td>
        </tr>
        <tr>
            <td>
                <label for='race'>Race</label>
            </td>
            <td>
                <input type='text' name='race'>
            </td>
        </tr>
        <tr>
            <td>
                <label for='sex'>Sex</label>
            </td>
            <td>
                <input type='text' name='sex'>
            </td>
        </tr>
        <tr>
            <td>
                <label for='age'>Age</label>
            </td>
            <td>
              <input type='text' name='age'>
            </td>
        </tr>
        <tr>
            <td>
                <label for='weapon'>Weapon</label>
            </td>
            <td>
                <input type='text' name='weapon'>
            </td>
        </tr>
    </table>

  <input type='submit' name='add_character' value='Add to Databse' class='button'>
</form>

<br><br>
<!--Form to enter in file data-->
<form action="db_landing_page.php" method="post" enctype="multipart/form-data">
	<h3 class="color_change2">Upload your favorite screenshots. 1 Megabyte Limit</h3>
	<input type="hidden" name="MAX_FILE_SIZE" value="2000000">
	<input type="file" name="userfile" size="50" >
	<br>
	<input type='submit' name='userfile' value='Upload File' class='button'>
</form>

<?php
// Source: http://www.bogotobogo.com/php/php13_file_handling.php
// This code will load a file onto the FTP and then I will store the location in the database. 

if (isset($_POST['userfile'])) {
    
    //Check to see if an error code was generated on the upload attempt
    if ($_FILES['userfile']['error'] > 0) {
        echo "<script >myFunction2(); alertFunc2()</script>";
    }
    
    // This will store the location of where the file is located
    $file_to_upload = 'uploads/' . $_FILES['userfile']['name'];
    
    if (is_uploaded_file($_FILES['userfile']['tmp_name'])) {
        if (!move_uploaded_file($_FILES['userfile']['tmp_name'], $file_to_upload)) {
            echo 'Problem: Could not move file to destination directory';
            echo "<script>transfer_land_page()</script>";
        }		
		else
		{
			chmod($file_to_upload, 0755);
		}

    }
    // Used for printing out file name
    $file_to_upload_name = $_FILES['userfile']['name'];
    
    // Check if a file has been uploaded
    if (isset($_FILES['userfile'])) {
        // Make sure the file was sent without errors
        if ($_FILES['userfile']['error'] == 0) {
            $name     = $mysqli->real_escape_string($_FILES['userfile']['name']);
            $mime     = $mysqli->real_escape_string($_FILES['userfile']['type']);
            $location = $file_to_upload;
            $size     = intval($_FILES['userfile']['size']);
            $result   = $mysqli->query("INSERT INTO users_uploads2 (username, name, mime, size, location, created)
                                       VALUES ('$username', '$name', '$mime', '$size', '$location', NOW())");
            
            // Checking if all was successfull
            if (!$result) {
                echo 'Error! Failed to insert the file';
            }
        } else {
            echo 'An error occured while the file was being uploaded. Please Try Again';
        }
        
    } else {
        echo 'The File was not sent!';
    }
}
?>

<h2>Current Files</h2>
<div class="expand">
<?php

$result = $mysqli->query("SELECT id, name, mime, size, location, username, created FROM users_uploads2 
                        WHERE username = '$username'
                        GROUP BY name");

// This will check if there is data in teh database
if ($result) {
    // Used to check if any files are in the database
    if ($result->num_rows == 0) {
        echo '<p>There are no files in the database</p>';
    } else {
        echo "<table width=50%>
                <tr>
                    <td><b>Name</b></td>
                    <td><b>Mime</b></td>
                    <td><b>Size (bytes)</b></td>
                    <td><b>Created</b></td>
                    <td><b>View It</b></td>
                </tr>";
        
        // Used to print the data
        while ($row = $result->fetch_assoc()) {
            echo "<tr>
                    <td>$row[name]</td>
                    <td>$row[mime]</td>
                    <td>$row[size]</td>
                    <td>$row[created]</td>
                    <td><a href='$row[location]' target='_blank'>View File</a></td>
                </tr>";
        }
        echo '</table>';
    }
}
?>
<h2>Current Chacters</h2>

<?php
// Used to display the current char_list of chacters in the databased based off of the user name
$char_list = "";
$stmt = $mysqli->query("SELECT char_name, race, sex, age, weapon FROM users_skyrim2 WHERE username = '$username' ORDER BY char_name  ");
$row_holder = mysqli_num_rows($stmt);
if ($row_holder > 0) {
    echo "<table><tr><td>Chacter Name</td><td>Race</td><td>Sex</td><td>Age</td><td>Weapon</td></tr>";
    while ($row = mysqli_fetch_assoc($stmt)) {
        $char_name = $row['char_name'];
        $race      = $row['race'];
        $sex       = $row['sex'];
        $age       = $row['age'];
        $weapon    = $row['weapon'];
        $char_list .= "<tr><td>" . $char_name . "</td><td>" . $race . "</td><td>" . $sex . "</td><td>" . $age . "</td><td>" . $weapon;
    }
    echo "<div class='char_list'>";
    echo $char_list . '</table></div>';
} else {
    echo "<p>Your Chacter Database is currently empty.</p>";
}
?>

</div>

</div>
</div>
</body>
</html>