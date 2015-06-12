<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');


$min_multiplicand = $_REQUEST['min-multiplicand'];
$max_multiplicand = $_REQUEST['max-multiplicand'];
$min_multiplier   = $_REQUEST['min-multiplier'];
$max_multiplier   = $_REQUEST['max-multiplier'];
$all_clear        = false;


// Logic to look value entered, if it is a number, and if the min is less than max
if ((isset($_REQUEST['min-multiplicand'])) && (empty($_REQUEST['min-multiplicand']))) {
    ECHO "<p>Missing parameter $min_multiplicand</p>";
    $all_clear = false;
} else if (!is_numeric($min_multiplicand)) {
    echo ("<p>1st $min_multiplicand must be an interger</p>");
    $all_clear = false;
} else if (!($min_multiplicand <= $max_multiplicand)) {
    echo ("<p>Minimum multilicand $min_multiplicand larger than maximum.</p>");
    $all_clear = false;
} else {
    $all_clear = true;
}

// Logic to look value entered and if it is a number
if ((isset($_REQUEST['max-multiplicand'])) && (empty($_REQUEST['min-multiplicand']))) {
    ECHO "<p>Missing parameter $max_multiplicand</p>";
    $all_clear = false;
} else if (!is_numeric($max_multiplicand)) {
    echo ("<p>2nd $max_multiplicand must be an interger</p>");
    $all_clear = false;
} else {
    $all_clear = true;
}

// Logic to look value entered and if it is a number
if ((isset($_REQUEST['min-multiplier'])) && (empty($_REQUEST['min-multiplicand']))) {
    echo ("<p>Missing parameter $min_multiplier</p>");
    $all_clear = false;
} else if (!is_numeric($min_multiplier)) {
    echo ("<p>3rd $min_multiplier must be an interger</p>");
    $all_clear = false;
} else if (!($min_multiplier <= $max_multiplier)) {
    echo ("<p>Minimum multiplier $min_multiplier larger than maximum.</p>");
    $all_clear = false;
} else {
    $all_clear = true;
}

// Logic to look value entered and if it is a number
if ((isset($_REQUEST['max-multiplier'])) && (empty($_REQUEST['min-multiplicand']))) {
    ECHO "<p>Missing parameter $max_multiplier</p>";
    $all_clear = false;
} else if (!is_numeric($max_multiplier)) {
    echo ("<p>4th $max_multiplier must be an interger</p>");
    $all_clear = false;
} else {
    $all_clear = true;
}

// if all_clear is true then there were no issues and it's ok to calculate
if ($all_clear = true) {
    $heigth = $max_multiplier - $min_multiplier + 1;
    $width  = $max_multiplicand - $min_multiplicand + 1;
    
	echo "<table border><thead><tr><th>";
    
    for ($i = 0; $i < $heigth; $i++) {
        $row_header = $min_multiplier + $i;
        echo "<th>$row_header</th>";
    }
    echo "</tr></thead>";
    for ($j = 0; $j < $width; $j++) {
        $col_header = $min_multiplicand + $j;
        echo "<th>$col_header</th>";
		
        for ($k = 0; $k < $heigth; $k++) {
            $answer = ($min_multiplier + $k) * $col_header;
            echo "<td>$answer</td>";            
        }
        echo "</th></tr></thead>";
    }
    echo "</table>";    
}


?>
