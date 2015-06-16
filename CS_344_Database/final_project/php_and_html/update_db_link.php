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

<!--FROM THIS POINT ON IT'S ALL ABOUT UPDATING. -->

<h2>Use these features to change database information:</h2>

<h3>Update Kingdom Name</h3>
<form action='update_kingdom.php' method='post'>
    <table>
    	<tr>
        	<th>Select Name</th>
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
        <tr>
            <th>
                <label for='new_name'>New Kingdom Name</label>
            </th>
            <td>
                <input type='text' name='new_name'>
                <br>
            </td>
        </tr> 
    </table>
    <input type='submit' name='update_kingdom' value='Update Database' class='button'>
</form>

<br>

<h3>Update Weather</h3>
<form action='update_weather.php' method='post'>
    <table>
    	<tr>
        	<th>Select Name</th>
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
        <tr>
            <th>
                <label for='new_name'>New Weather Name</label>
            </th>
            <td>
                <input type='text' name='new_name'>
                <br>
            </td>
        </tr> 
    </table>
    <input type='submit' name='update_weather' value='Update Database' class='button'>
</form>

<br>

<h3>Update Race Name</h3>
<form action='update_race_name.php' method='post'>
    <table>
    	<tr>
        	<th>Select Name</th>
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
        <tr>
            <th>
                <label for='new_name'>New Race Name</label>
            </th>
            <td>
                <input type='text' name='new_name'>
                <br>
            </td>
        </tr> 
    </table>

    <input type='submit' name='update_race_name' value='Update Database' class='button'>
</form>

<br>

<h3>Update Faction Name</h3>
<form action='update_faction_name.php' method='post'>
    <table>
    	<tr>
        	<th>Select Name</th>
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
        <tr>
            <th>
                <label for='new_name'>New Faction Name</label>
            </th>
            <td>
                <input type='text' name='new_name'>
                <br>
            </td>
		</tr> 
    </table>

    <input type='submit' name='update_faction_name' value='Update Database' class='button'>
</form>

<br>


<h3>Update Weapon Used</h3>
<p>Type in the exact First & Last Name, then you can update the weapon used.</p>
<form action='update_weapon_used.php' method='post'>
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
                <label for='new_weapon_name'>New Weapon Name</label>
            </th>
            <td>
                <input type='text' name='new_weapon_name'>
                <br>
            </td>
       	</tr> 
    </table>
    <input type='submit' name='update_weapon_used_name' value='Update Database' class='button'>
</form>



</body>
</html>