// JavaScript Document
// Code Source: https://developer.mozilla.org/en-US/docs/AJAX/Getting_Started

//Global
var objectHolder; 

// These functions will process the users submitted registration. 
// It will send the data to the process_register.php
function register() { 

	objectHolder = requestObject(); 
	var userName = document.getElementById("username").value;  
	var password = document.getElementById("password").value;
	var fname = document.getElementById("fname").value;	
	var lname = document.getElementById("lname").value;	
	if (userName == "" || password == "") {
		document.getElementById("error").innerHTML = "*** Both a Username & a Password are required! ***";
	}
	else {
		var data = "submit=true" + "&username=" + userName + "&password=" + password + "&fname=" + fname + "&lname=" + lname;  
		objectHolder.open("POST", "process_register.php", true);
		objectHolder.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		objectHolder.send(data);		
		objectHolder.onreadystatechange = function() { 
			if(objectHolder.readyState === 4) {
				if (objectHolder.status === 200) 
					 window.location.href = "process_register2.php";//"db_landing_page.php";					
				else 
					document.getElementById("error").innerHTML = "There was a problem with the registration request."; 				  
			};
		} 
	}
}

// These functions will process the users submitted registration. 
// It will send the data to the process_register.php
function logIn() { 
	//clear any existing error messages
	document.getElementById("loginError").innerHTML = "";
	objectHolder = requestObject(); 
	var userName = document.getElementById("username").value;  
	var password = document.getElementById("password").value; 
	if (userName == "" || password == "") {
		document.getElementById("loginError").innerHTML = "*** Both a Username & a Password are required! ***";
	}
	else {
		var data = "username=" + userName + "&" + "password=" + password;  
		objectHolder.open("POST", "process_login.php", true);
		objectHolder.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		objectHolder.send(data);		
		objectHolder.onreadystatechange = function() { 
			if(objectHolder.readyState === 4) {
				if (objectHolder.status === 200) 
					 window.location.href = "process_login2.php";//"db_landing_page.php";
				else 
					document.getElementById("loginError").innerHTML = "There was a problem with the login request."; 
			}  
		}; 
	} 
}

// Used to create an object for http requeset
function requestObject() {
	var requestHolder;
		
	if(window.ActiveXObject) {
		try {
			requestHolder = new ActiveXObject("Microsoft.XMLHTTP");
		}
		catch(e) {
			requestHolder = false;
		}			
	} 
	else {
		try {
			requestHolder = new XMLHttpRequest(); 
		} catch(e) {
			requestHolder = false; 
		}
	}
	if(requestHolder)
		return requestHolder; 
	else {
		console.log("Could not connect");
	}
}



