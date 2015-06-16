 <?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

$host      = "oniddb.cws.oregonstate.edu";
$user_name = "kramerj-db";
$pw        = "tG3rQiqxNJpYSZmf";

$mysqli = new mysqli($host, $user_name, $pw, $user_name);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL Database: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
//else
//echo "CONENCTED!";
?>
<!doctype html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Skyrim - Database</title>
</head>

<body>
    <h1>Skyrim Database!</h1>
    <p>This database is designed to track:</p>
    <ul>
        <li>The People of Skyrim</li>
        <li>The Races of Skyrim</li>
        <li>The Kingdoms of Skyrim</li>
        <li>The Weather of Skyrim</li>
        <li>The Factions of Skyrim</li>
    </ul>
    <br>
    <nav> Navigation Bar
        <ul>
       		<li><a href="index.php">Home</a></li>
          	<li><a href="enter_db_info_link.php">Enter DataBase Info</a></li>
          	<li><a href="update_db_link.php">Update DataBase Info</a></li>
          	<li><a href="search_db_link.php">Search DataBase Info</a></li>
          	<li><a href="erase_db_link.php">Erase DataBase Info</a></li>
    	</ul>
    
    </nav>

<br> 
    <h2>Enter Database Info Here:</h2>


<!--FROM THIS POINT ON IT'S ALL ABOUT ADDING. -->

<?php

if (isset($_POST['add_kingdom'])) {
    $enter_if        = true; // This is used as a sentinal to check if data was inputted correctly
    $name            = $_POST['name'];
    $population      = $_POST['population'];
    $typical_weather = $_POST['sky_weatherID'];
	
    
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_kingdom(name, population, sky_weatherID) VALUES ('$name', '$population', '$typical_weather')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>

<h3>Add a new Kingdom to the World</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='name'>Kingdom Name</label>
            </th>
            <td>
                <input type='text' name='name'>
                <br>
            </td>
        </tr>
        <tr>
            <th>
                <label for='population'>Population</label>
            </th>
            <td>
                <input type='integer' name='population'>
                <br>
            </td>
        </tr>
        <tr>
                <th> Select the Kingdom</th>
                <td>
					<?php
                    if (!($stmt = $mysqli->prepare("SELECT id, typical_weather FROM sky_weather"))) {
                        echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
                    }
                    
                    if (!$stmt->execute()) {
                        echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    if (!$stmt->bind_result($id, $weather)) {
                        echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    echo "<select name= 'sky_weatherID'> ";
                    while ($stmt->fetch()) {
                        echo '<option value=" ' . $id . ' "> ' . $weather . '</option>\n';
                        // echo '<option value="', $data['id'],'">', $data['name'],'</option>';
                    }
                    echo "</select>";
                    ?>
   				</td>
    		</tr>
    </table>

    <input type='submit' name='add_kingdom' value='Add to Databse' class='button'>
</form>

<br>


<?php

if (isset($_POST['add_weather'])) {
    $enter_if        = true; // This is used as a sentinal to check if data was inputted correctly
    $name            = $_POST['name'];
      
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_weather(typical_weather) VALUES ('$name')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error; 
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>
<h3>Add new weather to the world</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='name'>Weather Description</label>
            </th>
            <td>
                <input type='text' name='name'>
                <br>
            </td>
        </tr>
    </table>

    <input type='submit' name='add_weather' value='Add to Databse' class='button'>
</form>

<?php

if (isset($_POST['add_race'])) {
    $enter_if        = true; // This is used as a sentinal to check if data was inputted correctly
    $name            = $_POST['name'];
    $special_ability = $_POST['special_ability'];
   
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_race(name, special_ability) VALUES ('$name', '$special_ability')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error; 
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>
<br>
<h3>Add a new Race to the World</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='name'>Race Name</label>
            </th>
            <td>
                <input type='text' name='name'>
                <br>
            </td>
        </tr>
        <tr>
            <th>
                <label for='special_ability'>Special Ability</label>
            </th>
            <td>
                <input type='text' name='special_ability'>
                <br>
            </td>
        </tr>

    </table>

    <input type='submit' name='add_race' value='Add to Databse' class='button'>
</form>

<br>

<?php

if (isset($_POST['add_faction'])) {
    $enter_if = true; // This is used as a sentinal to check if data was inputted correctly
    $name     = $_POST['name'];
    $mission  = $_POST['mission'];

    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_faction(name, mission) VALUES ('$name', '$mission')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;     
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>

<h3>Add a new Faction to the World</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='name'>Faction Name</label>
            </th>
            <td>
                <input type='text' name='name'>
                <br>
            </td>
        </tr>
        <tr>
            <th>
                <label for='mission'>Factions Mission</label>
            </th>
            <td>
                <input type='text' name='mission'>
                <br>
            </td>
        </tr>
    </table>
    <input type='submit' name='add_faction' value='Add to Databse' class='button'>
</form>

<br>

<?php

if (isset($_POST['add_person'])) {
    $enter_if      = true; // This is used as a sentinal to check if data was inputted correctly
    $first_name    = $_POST['first_name'];
    $last_name     = $_POST['last_name'];
    $weapon        = $_POST['weapon'];
    $sky_kingdomID = $_POST['sky_kingdomID'];
    $sky_raceID    = $_POST['sky_raceID'];
    
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('$first_name', '$last_name', '$weapon', '$sky_kingdomID ', '$sky_raceID')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;  
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>

<h3>Add Person Data to the Skyrim World</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='first_name'>First Name</label>
            </th>
            <td>
                <input type='text' name='first_name'>
                <br>
            </td>
        </tr>
        <tr>
            <th>
                <label for='last_name'>Last Name</label>
            </th>
            <td>
                <input type='text' name='last_name'>
                <br>
            </td>
        </tr>
        <tr>
            <th>
                <label for='weapon'>Weapon Used</label>
            </th>
            <td>
                <input type='text' name='weapon'>
                <br>
            </td>
        </tr>
        <tr>

            <tr>
                <th> Select the Kingdom</th>
                <td>
					<?php
                    if (!($stmt = $mysqli->prepare("SELECT id, name FROM sky_kingdom"))) {
                        echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
                    }
                    
                    if (!$stmt->execute()) {
                        echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    if (!$stmt->bind_result($id, $name)) {
                        echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    echo "<select name= 'sky_kingdomID'> ";
                    while ($stmt->fetch()) {
                        echo '<option value=" ' . $id . ' "> ' . $name . '</option>\n';
                        // echo '<option value="', $data['id'],'">', $data['name'],'</option>';
                    }
                    echo "</select>";
                    ?>
   				</td>
    		</tr>
    		<th> Select the Race</th> 
    			<td> 
					<?php
                    if (!($stmt = $mysqli->prepare("SELECT id, name FROM sky_race"))) {
                        echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
                    }
                    
                    if (!$stmt->execute()) {
                        echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    if (!$stmt->bind_result($id, $name)) {
                        echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    echo "<select name= 'sky_raceID'> ";
                    while ($stmt->fetch()) {
                        echo '<option value=" ' . $id . ' "> ' . $name . '</option>\n';
                        // echo '<option value="', $data['id'],'">', $data['name'],'</option>';
                    }
                    echo "</select>";                
                    ?>
    			</td>
    		</tr>
  	</table>
  <input type='submit' name='add_person' value ='Add to Databse' class='button'>
</form>

<br>

<?php

if (isset($_POST['add_sky_faction_category'])) {
    $enter_if         = true; // This is used as a sentinal to check if data was inputted correctly
    $sky_peopleID     = $_POST['sky_peopleID'];
    $sky_factionID    = $_POST['sky_factionID'];
    $interesting_note = $_POST['interesting_note'];
 
    if ($enter_if == true) {
        if (!($stmt = $mysqli->prepare("INSERT INTO sky_faction_category(sky_peopleID, sky_factionID, interesting_note) VALUES ('$sky_peopleID',  '$sky_factionID', '$interesting_note')"))) {
            echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;  
        }
        if (!$stmt->execute()) {
            echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;     
        }
    }
	echo "<script type=text/javascript src=reload.js></script>";
    echo "<script> reloadIt() </script>";
}
?>
<h3>Add an Interesting Note about the Faction Categories</h3>
<form action='enter_db_info_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='interesting_note'>Note of Interest</label>
            </th>
            <td>
                <input type='text' name='interesting_note'>
                <br>
            </td>
        </tr>
        <tr>
            <tr>
                <th> Skyrim People</th>
                <td>
					<?php
                    if (!($stmt = $mysqli->prepare("SELECT id, first_name, last_name FROM sky_people"))) {
                        echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
                    }
                    
                    if (!$stmt->execute()) {
                        echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    if (!$stmt->bind_result($id, $first_name, $last_name)) {
                        echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    echo "<select name= 'sky_peopleID'> ";
                    while ($stmt->fetch()) {
                        echo '<option value=" ' . $id . ' "> ' . $first_name . ' ' . $last_name . '</option>\n';
                        // echo '<option value="', $data['id'],'">', $data['name'],'</option>';
                    }
                    echo "</select>";                    
                    ?>
                </td>
            </tr>
            <th> Faction Name</th> 
            	<td>     
					<?php
                    if (!($stmt = $mysqli->prepare("SELECT id, name FROM sky_faction"))) {
                        echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
                    }
                    
                    if (!$stmt->execute()) {
                        echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    if (!$stmt->bind_result($id, $name)) {
                        echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
                    }
                    echo "<select name= 'sky_factionID'> ";
                    while ($stmt->fetch()) {
                        echo '<option value=" ' . $id . ' "> ' . $name . '</option>\n';
                        // echo '<option value="', $data['id'],'">', $data['name'],'</option>';
                    }
                    echo "</select>";
                    ?>
    		</td>
    	</tr>
	</table>
  <input type='submit' name='add_sky_faction_category' value ='Add to Databse' class='button'>
</form>
</body>
</html>