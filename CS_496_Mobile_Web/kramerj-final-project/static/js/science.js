var jk = jk || {};
jk.editing = false;
jk.longitudeString = "string";
// Used to focus cursor on Scientist Name
jk.attachEventHandlers = function() {
	$("#insert-scientist-modal").on('shown.bs.modal', function() {
		$("input[name=scientistName]").focus();
	});
    $("#insert-project-modal").on('shown.bs.modal', function() {
		$("input[name=project_name]").focus();
	});
};


jk.hidNav = function() {
	$navbar = $(".collapse.navbar-collapse");
	if($navbar.hasClass("in")) {
		$navbar.collapse('hide');
	}
};


// Used to display the hidden edit action via HTML and CSS
jk.enableButtons = function () {
	$("#toggle-edit").click( function() {
		if (jk.editing === true) {
			jk.editing = false;
			$(".edit-actions").addClass("hidden");
			$(this).html("Edit");
		}
		else {
			jk.editing = true;
			$(".edit-actions").removeClass("hidden");
			$(this).html("Done");
		}
		jk.hidNav();
	
	});
	
	//Function used to to ensure date is entered as dd-mm-yyyy
	$('#dob-input').keyup(function(e){
	    if(e.keyCode != '8'){
	        if (e.target.value.length == 2) e.target.value = e.target.value + "-";
	        if (e.target.value.length == 5) e.target.value = e.target.value + "-";
	    }
	});
	
	// Used to adjust the modal title and submit button
	// Used to make sure form dats is blank
	// Disables entity-key so there are no duplicates of the same key
	$("#add-scientist").click( function() {
	
		$("#insert-scientist-modal .modal-title").html("Add a Scientist");
		$("#insert-scientist-modal button[type=submit]").html("Add Scientist");
		
		// Used to wipe out values when the users adds
		$("#insert-scientist-modal input[name=scientistName]").val("");
		$("#insert-scientist-modal input[name=dob]").val("");
		$("#insert-scientist-modal input[name=famous_discovery]").val("");
		
		
		$("#insert-scientist-modal input[name=entity-key]").val("").prop("disabled", true);	 //disables the property of the entity key. Meaning if submited it will 
	});

  // Used to gather form data and place into vars
	// Also removes extra spaces in the form fields ** No idea why that was happening **
	$(".edit-project-data").click( function () {
		$("#edit-project-modal .modal-title").html("Edit This Project Data");
		$("#edit-project-modal button[type=submit]").html("Edit Data");


        $(document).ready(function(){
            //alert("Text: " + $("#long_results").html());
            //alert("Text: " + $("#long_results").text());
            //alert("Text: " + $("#long_results").val());
            longitudeName = $("#long_results").html();
            latitudeName = $("#lat_results").html();
            altitudeName = $("#alt_results").html();


            //longitudeName = $(this).find("#long_results").html();
            //longitudeName = $(this).find("#long_results").text();
            //longitudeName = $(this).find("#long_results").val();
        });

		// Variables used to hold their HTML counterpart
		scientistName = $(this).find(".scientistName").html();
		projectName = $(this).find(".projectName").html();
		entityKey = $(this).find(".entity-key").html();

		// Adds the existing data info into the form fields.
		// regex is used to remove extra space in form fields
		$("#edit-project-modal input[name=scientistName]").val(scientistName.trim());
        $("#edit-project-modal input[name=scientistName]").prop('disabled',true);
		$("#edit-project-modal input[name=projectName]").val(projectName.replace(/\s/g, ''));

        $("#edit-project-modal input[name=longitude_name]").val(longitudeName)
            .prop('disabled',true);
        $("#edit-project-modal input[name=latitude_name]").val(latitudeName)
            .prop('disabled',true);
        $("#edit-project-modal input[name=altitude_name]").val(altitudeName)
            .prop('disabled',true);
		$("#edit-project-modal input[name=entity-key]").val(entityKey).prop("disabled", false);	// does not disable the entity key, so it can be sent to sertver

		// Used to reload the page if the user chooses cancel.
		$("#cancel_click").click( function () {
			window.location.reload()
		});
        jk.hidNav();

	});


    // Used to adjust the modal title and submit button
	// Used to make sure form dats is blank
	// Disables entity-key so there are no duplicates of the same key
	$("#add-project").click( function() {

		$("#insert-project-modal .modal-title").html("Add a Project");
		$("#insert-project-modal button[type=submit]").html("Add Project");

            //longitudeName = "holder";

       //$(".table-wrapper")
        $(document).ready(function(){
            //alert("Text: " + $("#long_results").html());
            //alert("Text: " + $("#long_results").text());
            //alert("Text: " + $("#long_results").val());
            longitudeName = $("#long_results").html();
            latitudeName = $("#lat_results").html();
            altitudeName = $("#alt_results").html();


            //longitudeName = $(this).find("#long_results").html();
            //longitudeName = $(this).find("#long_results").text();
            //longitudeName = $(this).find("#long_results").val();
        });

        if(longitudeName === "" && latitudeName === "" && altitudeName === ""){
            longitudeName = "N/A";
            latitudeName = "N/A";
            altitudeName = "N/A";
        }
        else{
            longitudeName.substr(0,6);
        }
		// Used to wipe out values when the users adds
		$("#insert-project-modal input[name=project_name]").val("");

        $("#insert-project-modal input[name=longitude_name]").val(longitudeName)
            .prop('disabled',true);
        $("#insert-project-modal input[name=latitude_name]").val(latitudeName)
            .prop('disabled',true);
        $("#insert-project-modal input[name=altitude_name]").val(altitudeName)
            .prop('disabled',true);

        $("#insert-project-modal input[name=entity-key]").val("").prop("disabled", true);	 //disables the property of the entity key. Meaning if submited it will
        jk.hidNav();
	});

    $("#submit_click2").click( function(){
        $("#insert-project-modal input[name=longitude_name]").val(longitudeName)
            .prop('disabled',false);
        $("#insert-project-modal input[name=latitude_name]").val(latitudeName)
            .prop('disabled',false);
        $("#insert-project-modal input[name=altitude_name]").val(altitudeName)
            .prop('disabled',false);
        jk.hidNav();

    });


    $("#get-GPS").click( function() {
        var onSuccess = function(position) {
          //  alert('Latitude: '          + position.coords.latitude          + '\n' +
          //'Longitude: '         + position.coords.longitude         + '\n' +
          //'Altitude: '          + position.coords.altitude          + '\n' +
          //'Accuracy: '          + position.coords.accuracy          + '\n' +
          //'Altitude Accuracy: ' + position.coords.altitudeAccuracy  + '\n' +
          //'Heading: '           + position.coords.heading           + '\n' +
          //'Speed: '             + position.coords.speed             + '\n' +
          //'Timestamp: '         + position.timestamp                + '\n');

            //jk.longitudeString = (position.coords.longitude).toString().substr(0,10);
            //jk.longitudeString= jk.longitudeString.toString();
            //jk.longitudeString = jk.longitudeString.substr(0,10);


            $("#long_results").text((position.coords.longitude).toString().substr(0,10));
            $("#lat_results").text((position.coords.latitude).toString().substr(0,9));
            if(position.coords.altitude === null){
                $("#alt_results").text("N/A");
            }
            else
                $("#alt_results").text((position.coords.altitude).toString().substr(0,9));
};
            // onError Callback receives a PositionError object
            //
            function onError(error) {
                alert('code: '    + error.code    + '\n' +
                      'message: ' + error.message + '\n');
            }

            navigator.geolocation.getCurrentPosition(onSuccess, onError);
        jk.hidNav();
    });
	

	
	// Used to gather form data and place into vars
	// Also removes extra spaces in the form fields ** No idea why that was happening ** 
	$(".edit-science-data").click( function () {
		$("#edit-scientist-modal .modal-title").html("Edit This Scientist Data");
		$("#edit-scientist-modal button[type=submit]").html("Edit Data");
		
		// Variables used to hold their HTML counterpart
		scientistName = $(this).find(".scientistName").html();
		dateOfBirth = $(this).find(".dateOfBirth").html();
		entityKey = $(this).find(".entity-key").html();
		sex = $(this).find(".sex").html().replace(/\s/g, '');
		if (sex === "Male"){
			//var t = "male";
			$("#maleRadio1").prop("checked", true)
		}
		else {
			$("#femaleRadio1").prop("checked", true)
		}

		famousDiscovery = $(this).find(".famousDiscovery").html().replace(/\s/g, '');
		
		
		// Adds the existing datainfo into the form fields.
		// regex is used to remove extra space in form fields
		$("#edit-scientist-modal input[name=scientistName]").val(scientistName.trim());
		$("#edit-scientist-modal input[name=dob]").val(dateOfBirth.replace(/\s/g, ''));
		$("#edit-scientist-modal input[name=inlineRadioOptions]").val(sex.replace(/\s/g, ''));
		$("#edit-scientist-modal input[name=famous_discovery]").val(famousDiscovery.replace(/\s/g, ''));
		$("#edit-scientist-modal input[name=entity-key]").val(entityKey).prop("disabled", false);	// does not disable the entity key, so it can be sent to sertver
		
		// Used to reload the page if the user chooses cancel. 
		$("#cancel_click").click( function () {
			window.location.reload()
		});
		jk.hidNav();
	});
	
	// Used to delete the scientist entity_key from the datastore
	// Entity key is taken from the jinja2 html. 
	$(".delete-scientist-data").click( function () {
		$("#delete-scientist-modal .modal-title").html("Delete This Scientist's Data");
		$("#delete-scientist-modal button[type=submit]").html("Delete Scientist");
		entityKey = $(this).find(".entity-key").html();
		//entityKey = entityKey.replace(/\s/g, '');
		$("#delete-scientist-modal input[name=entity_key]").val(entityKey);
        jk.hidNav();
	});

	// Used to delete the project entity_key from the datastore
	// Entity key is taken from the jinja2 html.
	$(".delete-project-data").click( function () {
		$("#delete-project-modal .modal-title").html("Delete This Project Data");
		$("#delete-project-modal button[type=submit]").html("Delete Project");
		entityKey = $(this).find(".entity-key").html();
		//entityKey = entityKey.replace(/\s/g, '');
		$("#delete-project-modal input[name=entity_key]").val(entityKey);
        jk.hidNav();
	});









    //
    //$("#xyz").click(function() {
    //
    //	/* var data = {
		//		first_name:"test",
		//		last_name: "test",
		//		employee_username: "test",
		//		department: "test",
		//	} */
    //
    //    $.ajax({
    //        type: "POST",
    //        url: "http://kramerj-final-project.appspot.com/insertscientist",
    //        //contentType: "application/json; charset=utf-8",
    //        data: data = {
    //
		//		scientistName:"POST TEST",
		//		dob:"01-01-2009",
		//		inlineRadioOptions:"Male",
		//		famous_discovery:"BASKETBALL"
    //
    //				//first_name:$('#firstName').val(),
    //				//last_name: $('#lastName').val(),
    //				//employee_username: $('#employee_username').val(),
    //				//department: $('#department').val(),
    //			},
    //        success: function(data) {
    //            alert("AJAX done");
    //        }
    //    });
    //
    //});


};



// Used to active the jQuery
$(document).ready( function(){
	jk.enableButtons();
	jk.attachEventHandlers();
	
});






























