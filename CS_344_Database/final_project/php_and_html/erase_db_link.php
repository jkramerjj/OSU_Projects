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
    
  <h2>Erase Data From Database</h2>
  
  
  <h3>Erase a Kingdom</h3>

<form action='erase_kingdom_name.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='kingdom_name'>Kingdom Name</label>
            </th>
            <td>
                <input type='text' name='kingdom_name'>
                <br>
            </td>
        </tr>
    </table>
    <input type='submit' name='erase_kingdom_name' value='Erase Kingdom' class='button'>
</form>
<p>Kingdom List:</p>
<table>
    <tr>
        <td>
           <?php 
				$result = $mysqli->query("SELECT sk.id AS id, sk.name AS name, sk.population AS population, sw.typical_weather AS typical_weather  
										FROM sky_kingdom sk INNER JOIN sky_weather sw ON sw.id=sk.sky_weatherID");
				echo "<table><th>ID</th><th>Name</th><th>Population</th><th>Typical Weather</th>"; 
				while($row = mysqli_fetch_array($result))
				{
					echo "<tr><td>" . $row['id'] . "</td><td>" . $row['name'] . "</td><td>" . $row['population'] . "</td><td>"  .
					$row['typical_weather']   ; 
					echo "<br />";
				}
				echo "</table>";
			?>
        </td>
    </tr>
</table>
<br><br>
  <h3>Erase a Race</h3>

<form action='erase_race_name.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='race_name'>Race Name</label>
            </th>
            <td>
                <input type='text' name='race_name'>
                <br>
            </td>
        </tr>
    </table>
    <input type='submit' name='erase_race_name' value='Erase Race' class='button'>
</form>

<p>Race List:</p>
<table>
	<td> 
		<?php 
			$result = $mysqli->query("SELECT * FROM sky_race");
			echo "<table><th>ID</th><th>Name</th><th>Sepcial Ability</th>"; 
			while($row = mysqli_fetch_array($result))
			{
				echo "<tr><td>" . $row['id'] . "</td><td>" . $row['name'] . "</td><td>" . $row['special_ability'] ;
			}
			echo "</table>";
    	?>
    </td>
</table>

<br><br>
  <h3>Wipe Database Clean</h3>
  	<form action='delete_all.php' method='post'>
        <input type='submit' value='** ERASE ENTIRE DATABASE ** ' name='delete_all'>
    </form>

</body>
</html>