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
   
<br><br>
 
<h2>Sky_People</h2>
	<?php 
		$result = $mysqli->query("SELECT * FROM sky_people");
		echo "<table> <th>ID</th><th>Name</th><th>Kingdom</th><th>Weapon</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['id'] . "</td><td>" . $row['first_name'] . "</td><td>" . $row['last_name'] . "</td><td>"  .
			$row['weapon']   ; 
			echo "<br />";
		}
		echo "</table>";
	?>

<br><br>
<h2>Sky_Kingdom</h2>
	<?php 
		$result = $mysqli->query("SELECT sk.id as id, sk.name as name, sk.population as population, sw.typical_weather as typical_weather  FROM sky_kingdom sk INNER JOIN sky_weather sw ON sw.id=sk.sky_weatherID");
		echo "<table><th>ID</th><th>Name</th><th>Population</th><th>Typical Weather</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['id'] . "</td><td>" . $row['name'] . "</td><td>" . $row['population'] . "</td><td>"  .
			$row['typical_weather']   ; 
			echo "<br />";
		}
		echo "</table>";
    ?>
  
<br><br>

<h2>Sky_Weather</h2>
	<?php 
		$result = $mysqli->query("SELECT * FROM sky_weather");
		echo "<table><th>ID</th><th>Typical Weather</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['id'] .  "</td><td>"  . $row['typical_weather']   ; 
			echo "<br />";
		}
		echo "</table>";
    ?>
  
<br><br>


 <h2>Sky_Race</h2>
	<?php 
		$result = $mysqli->query("SELECT * FROM sky_race");
		echo "<table><th>ID</th><th>Name</th><th>Sepcial Ability</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['id'] . "</td><td>" . $row['name'] . "</td><td>" . $row['special_ability'] ;
		}
		echo "</table>";
    ?>

<br><br>

 <h2>Sky_Faction</h2>
	<?php 
		$result = $mysqli->query("SELECT * FROM sky_faction");
		echo "<table><th>ID</th><th>Name</th><th>Mission</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['id'] . "</td><td>" . $row['name'] . "</td><td>" . $row['mission'] ;
		}
		echo "</table>";
    ?>

<br><br>

<h2>Sky_Faction_Category</h2>
    <p><strong>People can have more thatn one Faction and Intersting Note</strong></p>
    <?php 
		$result = $mysqli->query("SELECT sp.first_name AS fname, sp.last_name AS lname, sf.name AS name, sfk.interesting_note AS note FROM sky_faction_category sfk
								INNER JOIN sky_people sp ON sp.id=sfk.sky_peopleID
								INNER JOIN sky_faction sf ON sf.id=sfk.sky_factionID");
		echo "<table><th>First Name</th><th>Last Name </th><th>Faction</th><th> </th><th>Intresting Note</th>"; 
		while($row = mysqli_fetch_array($result))
		{
			echo "<tr><td>" . $row['fname'] . "</td><td>" . $row['lname'] . "</td><td>" . $row['name'] . "</td> <td>" . "</td><td>" . $row['note'] ;
		}
		echo "</table>";
    ?>

</body>
</html>