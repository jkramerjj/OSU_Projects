var jk = jk || {};
jk.editing = false;

// Used to focus cursor on Scientist Name
jk.attachEventHandlers = function() {
	$("#insert-scientist-modal").on('shown.bs.modal', function() {
		$("input[name=scientistName]").focus();
	});
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
		jk.hideNavBar();
	
	});
	
	//Function used to to ensure date is entered as dd-mm-yyyy
	$('#dob-input').keyup(function(e){
	    if(e.keyCode != '8'){
	        if (e.target.value.length == 2) e.target.value = e.target.value + "-";
	        if (e.target.value.length == 5) e.target.value = e.target.value + "-";
	    }
	})
	
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
	// Logic is used to compare if checkmarks and radios are used and if they are
	// to make that in the form
	// Also removes extra spaces in the form fields ** No idea why that was happening ** 
	$(".edit-science-data").click( function () {
		$("#insert-scientist-modal .modal-title").html("Edit This Scientist Data");
		$("#insert-scientist-modal button[type=submit]").html("Edit Data");
		
		// Variables used to hold their HTML counterpart
		scientistName = $(this).find(".scientistName").html();
		dateOfBirth = $(this).find(".dateOfBirth").html();
		entityKey = $(this).find(".entity-key").html();
		sex = $(this).find(".sex").html().replace(/\s/g, '');
		if (sex === "Male"){
			//var t = "male";
			$("#maleRadio").prop("checked", true)
		}
		else {
			$("#femaleRadio").prop("checked", true)
		}
		h_math = $(this).find(".h_math").html().replace(/\s/g, '');
		if(h_math === "True"){
			$("#mathmatics").prop("checked", true)
		}
		
		h_physics = $(this).find(".h_physics").html().replace(/\s/g, '');
		if(h_physics === "True"){
			$("#physics").prop("checked", true)
		}
		h_comsci = $(this).find(".h_comsci").html().replace(/\s/g, '');
		if(h_comsci === "True"){
			$("#computer_science").prop("checked", true)
		}
		h_biology = $(this).find(".h_biology").html().replace(/\s/g, '');
		if(h_biology === "True"){
			$("#biology").prop("checked", true)
		}
		h_other = $(this).find(".h_other").html().replace(/\s/g, '');
		if(h_other === "True"){
			$("#other").prop("checked", true)
		}
		famousDiscovery = $(this).find(".famousDiscovery").html().replace(/\s/g, '');
		
		
		// Adds the existing quote and movie info into the form fields. 
		// regex is used to remove extra space in form fields
		$("#insert-scientist-modal input[name=scientistName]").val(scientistName.trim());
		$("#insert-scientist-modal input[name=dob]").val(dateOfBirth.replace(/\s/g, ''));
		$("#insert-scientist-modal input[name=inlineRadioOptions]").val(sex.replace(/\s/g, ''));
		$("#insert-scientist-modal input[name=famous_discovery]").val(famousDiscovery.replace(/\s/g, ''));
		$("#insert-scientist-modal input[name=entity-key]").val(entityKey).prop("disabled", false);	// does not disable the entity key, so it can be sent to sertver
		
		// Used to reload the page if the user chooses cancel. 
		$("#cancel_click").click( function () {
			window.location.reload()
		});
		
	});
	
	// Used to delete the entity_key from the datastore
	// Entity key is taken from the jinja2 html. 
	$(".delete-scientist-data").click( function () {
		$("#delete-scientist-modal .modal-title").html("Delete This Scientist's Data");
		$("#delete-scientist-modal button[type=submit]").html("Delete Scientist");
		entityKey = $(this).find(".entity-key").html();
		$("#delete-scientist-modal input[name=entity_key]").val(entityKey);
	});
	
	
	
};



// Used to active the jQuery
$(document).ready( function(){
	jk.enableButtons();
	jk.attachEventHandlers();
	
});






























