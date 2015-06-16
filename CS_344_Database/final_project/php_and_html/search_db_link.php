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

<h2> Searching The Database </h2>
<h4>Please note: All results are displayed bellow the search button.</h4>
<br>
<h3>Search for a Persons Weapon of Choice</h3>


<form action='search_db_link.php' method='post'>
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
    </table>
    <input type='submit' name='weapon_search' value='Search' class='button'>
    <input type='submit' name='weapon_search' value='Clear' class='button'>
</form>
<?php

if (isset($_POST['weapon_search'])) {
    $enter_if     = true; // This is used as a sentinal to check if data was inputted correctly
    $fname = $_POST['first_name'];
	$lname = $_POST['last_name'];
    
    if ($fname != NULL) {
        
        $resultSet = $mysqli->query("SELECT weapon FROM sky_people
									WHERE first_name = '$fname' AND last_name='$lname' "); 
        
       if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $wname = $rows['weapon'];
                echo "<p>Weapon: $wname</p>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search for races that DO live in a Kingdom</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='kingdom_name'>Enter Kingdom Name</label>
            </th>
            <td>
                <input type='text' name='kingdom_name'>
                <br>
            </td>
    </table>
    <input type='submit' name='in_kingdom_search' value='Search' class='button'>
    <input type='submit' name='in_kingdom_search_clear' value='Clear' class='button'>
</form>
<?php

if (isset($_POST['in_kingdom_search'])) {
    $enter_if     = true; // This is used as a sentinal to check if data was inputted correctly
    $kingdom_name = $_POST['kingdom_name'];
    
    if ($kingdom_name != NULL) {
        
        $resultSet = $mysqli->query("SELECT skr.name FROM sky_race skr
									INNER JOIN sky_people skp ON skp.sky_raceID=skr.id
									INNER JOIN sky_kingdom skk ON skk.id = skp.sky_kingdomID
									WHERE skk.name = '$kingdom_name'
									GROUP BY skr.name "); 
        
       if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $rname = $rows['name'];
                echo "<p>Name: $rname</p>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search for races that DO NOT live in a Kingdom</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='kingdom_name'>Enter Kingdom Name</label>
            </th>
            <td>
                <input type='text' name='kingdom_name'>
                <br>
            </td>
    </table>

    <input type='submit' name='not_in_kingdom_search' value='Search' class='button'>
    <input type='submit' name='not_in_kingdom_search_clear' value='Clear' class='button'>
</form>

<?php

if (isset($_POST['not_in_kingdom_search'])) {
    $enter_if     = true; // This is used as a sentinal to check if data was inputted correctly
    $kingdom_name = $_POST['kingdom_name'];
    if ($kingdom_name != NULL) {

        $resultSet = $mysqli->query("SELECT skr.name FROM sky_race skr
									INNER JOIN sky_people skp ON skp.sky_raceID=skr.id
									INNER JOIN sky_kingdom skk ON skk.id = skp.sky_kingdomID
									WHERE skk.name <> '$kingdom_name' 
									GROUP BY skr.name"); 
        
        if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $rname = $rows['name'];
                //$lname = $rows['last_name'];
                echo "<p>Name: $rname</p>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search for people who ARE a particular race</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='race_name'>Enter Race Name</label>
            </th>
            <td>
                <input type='text' name='race_name'>
                <br>
            </td>
    </table>

    <input type='submit' name='a_race_search' value='Search' class='button'>
    <input type='submit' name='a_race_clear' value='Clear' class='button'>
</form>

<?php

if (isset($_POST['a_race_search'])) {
    $enter_if  = true; // This is used as a sentinal to check if data was inputted correctly
    $race_name = $_POST['race_name'];
    
    if ($race_name != NULL) {
        
        $resultSet = $mysqli->query("SELECT sky_people.first_name, sky_people.last_name FROM sky_people
									INNER JOIN sky_race ON sky_race.id=sky_people.sky_raceID 
									WHERE sky_race.name = '$race_name'
									GROUP BY sky_people.first_name ");
											
        if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $fname = $rows['first_name'];
                $lname = $rows['last_name'];
                echo "<p>Name: $fname $lname</p>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search for people who are NOT a particular race</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='race_name'>Enter Race Name</label>
            </th>
            <td>
                <input type='text' name='race_name'>
                <br>
            </td>
    </table>

    <input type='submit' name='not_a_race_search' value='Search' class='button'>
    <input type='submit' name='not_a_race_clear' value='Clear' class='button'>
</form>

<?php
if (isset($_POST['not_a_race_search'])) {
    $race_name = $_POST['race_name'];
    
    if ($race_name != NULL) {
        
        $resultSet = $mysqli->query("SELECT sky_people.first_name, sky_people.last_name FROM sky_people
									INNER JOIN sky_race ON sky_race.id=sky_people.sky_raceID 
									WHERE sky_race.name <> '$race_name'
									GROUP BY sky_people.first_name ");
        if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $fname = $rows['first_name'];
                $lname = $rows['last_name'];
                echo "<p>Name: $fname $lname</p>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search People to find their Faction</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='first_name'>Enter First Name</label>
            </th>
            <td>
                <input type='text' name='first_name'>
                <br>
            </td>
            <tr>
                <th>
                    <label for='last_name'>Enter Last Name</label>
                </th>
                <td>
                    <input type='text' name='last_name'>
                    <br>
                </td>
    </table>

    <input type='submit' name='faction_Search' value='Search' class='button'>
    <input type='submit' name='faction_Search' value='Clear' class='button'>
</form>


<?php
if (isset($_POST['faction_Search'])) {
    $first_name = $_POST['first_name'];
    $last_name  = $_POST['last_name'];
    
    if ($first_name != NULL) {
        $resultSet = $mysqli->query("SELECT sky_people.first_name as 'First Name', sky_people.last_name as 'Last Name', sky_faction.name as 'Faction Name'  FROM sky_people
									INNER JOIN sky_faction_category sfc ON sfc.sky_peopleID=sky_people.id
									INNER JOIN sky_faction on sky_faction.id=sfc.sky_factionID
									WHERE sky_people.first_name='$first_name' AND sky_people.last_name = '$last_name'
									ORDER BY sky_faction.name ");
	
        if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $fname        = $rows['First Name'];
                $lname        = $rows['Last Name'];
                $faction_name = $rows['Faction Name'];
                echo "<p>First Name: $fname </p>";
                echo "<p>Last Name: $lname</p>";
                echo "<p>Faction Name: $faction_name</p><br>";
            }
        } else
            echo "no results";
    }
}
?>
<br>
<br>
<h3>Search Kingdoms from an Equal to or Greater Than Population</h3>

<form action='search_db_link.php' method='post'>
    <table>
        <tr>
            <th>
                <label for='population'>Enter Population Amount</label>
            </th>
            <td>
                <input type='number' name='population'>
                <br>
            </td>
    </table>

    <input type='submit' name='population_search' value='Search' class='button'>
    <input type='submit' name='population_search' value='Clear' class='button'>
</form>

<?php

if (isset($_POST['population_search'])) {
    $population_number = $_POST['population'];
    
    if ($population_number != NULL) {  
        $resultSet = $mysqli->query("SELECT name, population FROM sky_kingdom WHERE population >= '$population_number' ");
        if ($resultSet->num_rows != 0) {
            while ($rows = $resultSet->fetch_assoc()) {
                $kname = $rows['name'];
                $pop   = $rows['population'];
                echo "<p>Kingdom Name: $kname  <br>Population: $pop </p>"; 
            }
        } else
            echo "no results";
    }
}
?>

</body>
</html>