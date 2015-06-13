// JavaScript Document

function myFunction() {
	var msg = "<h2 class='back_up'>Transfering back to home page in 6 seconds Click <a href=index.php?logout=true>here</a> if you don't want to wait.<h2>";
    document.write(msg);
	myVar = setInterval(alertFunc, 3000);
}

function alertFunc() {
	var waiting = setInterval(transfer, 3000);
}


function username_taken() {
	var msg = "<div class='master'> <div class='main_1'><h2 class='back_up'>The username is already taken, please try again. Transfering back to register page in 6 seconds, Click <a href=register.php?logout=true>here</a> if you don't want to wait.<h2></div></div>";
    document.write(msg);
	myVar = setInterval(waitFunc, 3000);
}

function waitFunc() {
	var waiting = setInterval(transfer_register, 3000);
}

function transfer_register() {
	
    window.location.href = "register.php?logout=true";
}


function badUserPW() {
	var msg = "<div class='master'> <div class='main_1'><h2 class='back_up'>INNCORRECT USERNAME OR PASSWORD Transfering back to log in page in 6 seconds Click <a href=index.php?logout=true>here</a> if you don't want to wait.<h2></div></div>";
    document.write(msg);
	myVar = setInterval(nextFunc, 3000);
}

function nextFunc() {
	var waiting = setInterval(transfer_login, 3000);
}

function trsnf_land_page() {	
    window.location.href = "db_landing_page.php";
}

function trsnf_land_page2() {	
	waitFunc();
	waitFunc();
    window.location.href = "db_landing_page.php";
}

function transfer_login() {	
    window.location.href = "login.php?logout=true";
}
