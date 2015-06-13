<?php
error_reporting(E_ALL);
ini_set('display_errors', 'on');
include 'super_secret__file__.php';
echo "<link rel='stylesheet' type='text/css' href='styles.css'>";
echo "<link rel='stylesheet' type='text/css' href='styles2.css'>";
if (isset($_POST['add_video'])) {
   	$enter_if         = true; // This is used as a sentinal to check if data was inputted correctly
    $video_name       = $_POST['name'];
    $video_category   = $_POST['category'];
    $video_length     = $_POST['length'];
    $video_checked_in = 1;    
    
    if (empty($video_category) && empty($video_length) && !empty($video_name))
        $enter_if = true;
    else {
        if (empty($video_name)) {
            echo "<p>Remember: A video name is always required.</p>";
            $enter_if = false;
        }
        //if (empty($video_category)) {
          //  echo "Remember: A video category is always required.<br>";
            //$enter_if = false;
       // }
        if ($video_length < 0) {
            echo "<p>Remember: It is impossible to watch something a negative amount of time.</p>";
            $enter_if = false;
        }
        if (empty($video_length)) {
            echo "<p>Remeber: The video needs a length</p>";
            $enter_if = false;
        } else if (!is_numeric($video_length)) {
            echo "<p>Remember: Use numbers to enter video length</p>";
            $enter_if = false;
        }
    }
    
    // This if statement code is for adding to the database. It uses the sentianl enter_if to decide if it should enter or not. 
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO video_tbl(name, category, length, rented)  VALUES ('$video_name', '$video_category', '$video_length', '$video_checked_in')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
            // Used to go back to the main page
			header('Location: index.php');
			die();
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
			// Used to go back to the main page
			header('Location: index.php');
			die();
		}        
    } else {
        //This is used only to re-display the forms incase some mistype
		//echo "<h4> YOU ARE IN DEDICATED RE-ENTER PAGE</h4>";
        echo "<form action='add.php' method='post'>";
        echo "<table><tr><th>";
        echo "    <label for'name'>Enter video name</label>";
        echo "    </th><td>";
        echo "    <input type='text' name='name'> <br>";
        echo "    </td> </tr><tr><th>";
        echo "    <label for'category'>Enter video category</label>";
        echo "    </th><td>";
        echo "    <input type='text' name='category'><br>";
        echo "    </td></tr><tr><th>";
        echo "    <label for'length'>Enter video length.</label>";
        echo "    </th><td>";
        echo "    <input type='text' name='length'><br>";
        echo "    </td></tr></table>";
        echo " <input type='submit' name='add_video' value ='Add Video'>";
        echo "</form>";
    }
}

// Used to go back to the main page
if ($enter_if == true) {
  //  header('Location: index.php');
  include('index.php');
	die();
}

?>