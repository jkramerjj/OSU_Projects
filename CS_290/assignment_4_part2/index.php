<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 'on');
	//Connect to database via super_secret__file__
	include 'super_secret__file__.php';
	
	echo "<!DOCTYPE HTML>";
	echo "<html>";
	echo "<head>";
	echo "<meta charset ='utf-8'>";
	echo "<link rel='stylesheet' type='text/css' href='styles.css'>";
	echo "<title>Video Database -- Enjoy</title>";	
	echo "</head>";
	echo "<body>";		
	
	echo "<h3>Add New Video</h3>";
	echo "<form action='add.php' method='post'>";	
	echo "<table>";
	echo " <tr><th>";
	echo " 	 <label for='name'>Enter video name</label>";
	echo "	 </th><td>";
	echo "	 <input type='text' name='name'> <br>";
	echo "	 </td> </tr><tr><th>";
	echo "	 <label for='category'>Enter video category</label>";
	echo "	 </th><td>";
	echo "	 <input type='text' name='category'><br>";
	echo "	 </td></tr><tr><th>";
	echo "	 <label for='length'>Enter video length.</label>";
	echo "	 </th><td>";
	echo "	 <input type='text' name='length'><br>";
	echo " </td></tr>";
	echo "</table>";
	echo "<input type='submit' name='add_video' value ='Add Video' class=\"button\"'>";
	echo "</form>";
	
	echo "<h3>Database Category Filter</h3>";
	echo "<form action='index.php' method='get'>";
	echo "<select name='selected_category'>";
	
	// This array is used to contain the video categories.
	$video_array = array();

	// This array_push w/ ""Show ALl" is used to display all the videos
	array_push($video_array, "Show ALL");

	// The following quiery will search for only distinct categories, to elminiate duplicates
	// I got this from: 
	// http://stackoverflow.com/questions/7250566/mysql-select-distinct
	// http://www.mysqltutorial.org/mysql-distinct.aspx
	if (!($stmt = $mysqli->prepare('SELECT DISTINCT category FROM video_tbl'))) 
		echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;	
	if (!$stmt->execute()) 
		echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;	
	if (!$stmt->bind_result($video_category)) 
		echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
	
	while ($stmt->fetch()) 
		// This is used to push the newly queried category onto the array for viewing by the user.  
		array_push($video_array, $video_category);
	
	// The handy foreach here will cycle through and dispay each category individualy. 
	foreach ($video_array as $each_category)
		if ($each_category != " " && $each_category != "") 
			echo "<option value='$each_category'>$each_category</option>";
	
	// This if statement process what category the user selected. 
	if (isset($_GET['video_category_array'])) {
		$filter_category = $_GET['selected_category']; 
		if ($filter_category == "Show ALL") 
			$matched_videos = $mysqli->query("SELECT name, category, length, rented FROM video_tbl ORDER BY name");
		else  // This is used if the user selected a category
			$matched_videos = $mysqli->query("SELECT name, category, length, rented FROM video_tbl WHERE category = '$filter_category' ORDER BY name");
	}
	else // This is used to select all the video data.  
		$matched_videos = $mysqli->query("SELECT * FROM video_tbl ORDER BY name");
	
	echo "</select>";
	echo "    <input type='submit' value='Filter Data' name='video_category_array' >";
	echo "</form>";
	echo "<h3>Wipe Database Clean</h3>";
	echo "<form action='db_delete.php' method='post'>";
	echo "	<input type='submit'  value='** ERASE ENTIRE DATABASE ** ' name='video_delete_all'>";
	echo "</form>";
	echo "<h3>All Videos in the Database</h3>";
	echo "<table>";
	echo "  <tr>";
	echo "    <th>Name</th>";
	echo "	  <th>Category</th>";
	echo "	  <th>Length</th>";
	echo "	  <th>Checked IN / OUT</th>";
	echo "	  <th colspan ='4'>Options</th>";
	echo "  </tr> ";
	
	// This is used to display videos form the database.
	foreach ($matched_videos as $video_info) {
		echo "<tr>";    
		echo "  <td>";
		echo 	  $video_info['name'];
		echo "	</td>";
		echo "	<td>";
		echo      $video_info['category'];
		echo "	</td>";
		echo "<td>" . $video_info['length'] . "</td>";
			
		// This will check if the video is checked in or out
		if ($video_info['rented'] != 1)         
			echo "<td> Checked-Out </td>";
		else 
			echo "<td> Checked-In </td>";
		
		echo "  <td>";
		echo "	  <form action='check_in_and_out.php' method='post'>";
		echo ("	    <input name='video_related_id' type ='hidden' value='");
		echo 	    $video_info['id'];
		echo "	    '>";
		echo ("	    <input name='videoRented' type ='hidden' value='");
		echo 	    $video_info['rented'];
		echo "	    '>";
		   
		if ($video_info['rented'] != 1)
			echo '<input type="submit" value ="Check In" name="video_check_in" >';
		else
			echo '<input type="submit" value ="Check Out" name="video_check_out" >';
		 
		echo "  </form>";
		echo "</td>";
		echo "<td>";
		echo "	<form action='delete_single.php' method='post'>";
		echo ("	  <input type ='hidden' name='video_related_id' value='");
		echo 	  $video_info['id'];
		echo "	  '>";
		echo (" 	  <input type='submit' name='delete_single_video' value ='Delete'>");
		echo "   </form> ";
		echo "</td>";
		echo "</tr>";
	}
	
	echo "</table>";	
	echo "</body>";
	echo "</html>";
?>
	
















