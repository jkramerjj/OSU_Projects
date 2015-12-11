import datetime
import json, logging
import os
from google.appengine.api import users
from google.appengine.ext import ndb
import jinja2
from models import ScientistData
import models
import webapp2


jinja_env = jinja2.Environment(
  loader=jinja2.FileSystemLoader(os.path.dirname(__file__)),
  autoescape=True)

# Used to get current logged in Users data
user = users.get_current_user()
def get_parent_key(user):
  return ndb.Key("Entity", user.email().lower())

# used to send a message back to an API connection
def messageBack(self, err, msg):
    self.response.status = err
    self.response.write(msg)
    return


# This function will validate incoming data to make sure to matches the models
# guideline. It will then update the database via the entity key. It will also return
# any errors and a message to the user if needed.
class EditScientist(webapp2.RedirectHandler):
    def post(self):
        #  the user seeks to edit a datastore entry
        #The GAE APP is built around POST and then python to handle the logic
        possible_issue = "none"
        try:
            datetime.datetime.strptime(self.request.get("dob").replace(" ", ""),'%d-%m-%Y')

        except ValueError:
            possible_issue = "dob"

        if self.request.get("scientistName").lstrip() == "":
            possible_issue = "name"

        if self.request.get("inlineRadioOptions").replace(" ", "").lower() != "male" and \
                       self.request.get("inlineRadioOptions").replace(" ", "").lower() != "female":
            possible_issue = "sex"


        if possible_issue == "none":
            science_key = ndb.Key(urlsafe=self.request.get("entity-key").strip())
            science_data = science_key.get()

            # Logic used to remove spaces before entering into datastore
            oldName = science_data.scientistName
            science_data.scientistName = self.request.get("scientistName").lstrip()
            science_data.dateOfBirth = self.request.get("dob").replace(" ", "")
            science_data.sex = self.request.get("inlineRadioOptions").replace(" ", "").lower()
            science_data.famousDiscovery = self.request.get("famous_discovery").replace(" ", "")

            qry = models.Project.query(models.Project.scientistName == oldName).fetch()

            if qry != None or qry != []:
                i=0
                # Cycles through and change all queries that match the scientist name
                # in the performance table.
                while i <= len(qry) - 1:
                    if qry[i].scientistName == oldName:
                        qry[i].scientistName = science_data.scientistName
                        qry[i].put()
                    i+=1

            science_data.put()
            messageBack(self, 200, "Edit was successful")
            self.redirect(self.request.referrer)


        elif possible_issue == "name":
            messageBack(self, 406, "Error: No name was entered")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())

        elif possible_issue == "dob":
            messageBack(self, 406, "Error: No DOB was entered")
            template = jinja_env.get_template("templates/dob_issue.html")
            self.response.write(template.render())

        elif possible_issue == "sex":
            messageBack(self, 406, "Error: No Sex was entered")
            template = jinja_env.get_template("templates/sex_issues.html")
            self.response.write(template.render())

        else:
            messageBack(self, 406, "Error: A general error was found")
            template = jinja_env.get_template("templates/error_message.html")
            self.response.write(template.render())


    ## API SPECIFIC PUT CODE ###
    def put(self):
        #  the user seeks to edit a datastore entry
        possible_issue = "none"
        try:
            datetime.datetime.strptime(self.request.get("dob").replace(" ", ""),'%d-%m-%Y')

        except ValueError:
            possible_issue = "dob"

        if self.request.get("scientistName").lstrip() == "":
            possible_issue = "name"

        if self.request.get("inlineRadioOptions").replace(" ", "").lower() != "male" and \
                       self.request.get("inlineRadioOptions").replace(" ", "").lower() != "female":
            possible_issue = "sex"


        if possible_issue == "none":
            science_key = ndb.Key(urlsafe=self.request.get("entity-key").strip())
            science_data = science_key.get()

            # Logic used to remove spaces before entering into datastore
            oldName = science_data.scientistName
            science_data.scientistName = self.request.get("scientistName").lstrip()
            science_data.dateOfBirth = self.request.get("dob").replace(" ", "")
            science_data.sex = self.request.get("inlineRadioOptions").replace(" ", "").lower()
            science_data.famousDiscovery = self.request.get("famous_discovery").replace(" ", "")

            qry = models.Project.query(models.Project.scientistName == oldName).fetch()

            if qry != None or qry != []:
                i=0
                # Cycles through and change all queries that match the scientist name
                # in the performance table.
                while i <= len(qry) - 1:
                    if qry[i].scientistName == oldName:
                        qry[i].scientistName = science_data.scientistName
                        qry[i].put()
                    i+=1

            science_data.put()
            messageBack(self, 200, "Edit was successful")


        elif possible_issue == "name":
            messageBack(self, 406, "Error: No name was entered")

        elif possible_issue == "dob":
            messageBack(self, 406, "Error: No DOB was entered")

        elif possible_issue == "sex":
            messageBack(self, 406, "Error: No Sex was entered")

        else:
            messageBack(self, 406, "Error: A general error was found")



# Adds data via getting data sent over by the user. It will get their GOOGLE account.
# plus other model data and then check to make sure it fits the model guidlines, such as
# no blank projects names can be entered. It will then add the entry or return an error
class AddScientist(webapp2.RedirectHandler):
    ## API SPECIFIC POST CODE ###
    #The GAE APP is built around POST and then python to handle the logic
    def post(self):
        possible_issue = "none"

        # This  is used to enter in new scientist data for the first time
        user = users.get_current_user()

        # Used to check for empty string
        scientistName = self.request.get("scientistName").strip()
        if str(scientistName) == str(""):
            possible_issue = "name"

         # Used to check if DOB is in a DD-MM-YYYY format
        dateOfBirth = self.request.get("dob")
        try:
            datetime.datetime.strptime(dateOfBirth,'%d-%m-%Y')

        except ValueError:
            possible_issue = "dob"


        # Checks to make sure a radio is selected
        sex = self.request.get("inlineRadioOptions").lower()
        if sex != "male" and sex != "female":
            possible_issue = "sex"


        famousDiscovery = self.request.get("famous_discovery")

        ## queries the datastore to check and see if the user entered scientist already exists
        qry = ScientistData.query(ScientistData.scientistName == str(scientistName),
                                  ScientistData.dateOfBirth == str(dateOfBirth),
                                  ScientistData.sex == str(sex),
                                  ScientistData.famousDiscovery == str(famousDiscovery)
                                  )

        people = qry.fetch()
        if people != []:
            possible_issue = "duplicate"

        # Logic here will enter data into datastore and checks for any errors
        if possible_issue == "none":
            new_scientist = ScientistData(parent = get_parent_key(user),
                                       scientistName = scientistName,
                                       dateOfBirth = dateOfBirth,
                                       sex = sex,
                                       famousDiscovery = famousDiscovery.strip())
            new_scientist.put()
            messageBack(self, 200, "Add was successful")
            self.redirect(self.request.referrer)

        # If here there was an error, it will load the error html
        elif possible_issue == "duplicate":
            messageBack(self, 406, "Error: A duplicate name already exists")
            template = jinja_env.get_template("templates/duplicate_user.html")
            self.response.write(template.render())
        elif possible_issue == "dob":
            messageBack(self, 406, "Error: No DOB was entered")
            template = jinja_env.get_template("templates/dob_issue.html")
            self.response.write(template.render())
        elif possible_issue == "name":
            messageBack(self, 406, "Error: No Name was entered")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())
        elif possible_issue == "sex":
            messageBack(self, 406, "Error: No Sex was entered")
            template = jinja_env.get_template("templates/sex_issue.html")
            self.response.write(template.render())
        else:
            template = jinja_env.get_template("templates/error_message.html")
            self.response.write(template.render())

                
                
                
                
                
# Simply deletes the data from the scientist model via the entity_key
# First gets scientist data via a key, then stores the scientist name in a string,
# then deletes the scientist entry and then deletes all references of that name in the
# project model.
class DeleteScientist(webapp2.RedirectHandler):
    #The GAE APP is built around POST and then python to handle the logic
    def post(self):
        successful = False
        science_key = ndb.Key(urlsafe=self.request.get("entity_key").strip())
        science_data = science_key.get()
        scientist_name = science_data.scientistName
        science_key.delete()

        qry = models.Project.query(models.Project.scientistName == scientist_name).fetch()
        if qry != None or qry != []:
            i=0
            successful = True
            # Cycles through and deletes all queries that match the employee_username
            # in the performance table.
            while i <= len(qry) - 1:
                qry[i].key.delete()
                i+=1

        if not successful:
            messageBack(self, 406, "Error: Delete was Un-Successful")
            template = jinja_env.get_template("templates/delete_issue.html")
            self.response.write(template.render())
        else:
            messageBack(self, 200, "Delete was successful")
            self.redirect(self.request.referrer)



    ## API SPECIFIC DELETE CODE ###
    def delete(self):
        successful = False
        science_key = ndb.Key(urlsafe=self.request.get("entity_key").strip())
        science_data = science_key.get()
        scientist_name = science_data.scientistName
        science_key.delete()

        qry = models.Project.query(models.Project.scientistName == scientist_name).fetch()
        if qry != None or qry != []:
            i=0
            successful = True
            # Cycles through and deletes all queries that match the employee_username
            # in the performance table.
            while i <= len(qry) - 1:
                qry[i].key.delete()
                i+=1

        if not successful:
            messageBack(self, 406, "Error: Delete was Un-Successful")
        else:
            messageBack(self, 200, "Delete was successful")






# This code is only used for developers that would like to connect to my API.
# The GAE App that runs this code would not use this particular section of code, because
# the App is built with Jinja2 to display info
class GetScientistByName(webapp2.RequestHandler):
    ## API SPECIFIC GET CODE ###
    def options(self):
        self.response.headers['Access-Control-Allow-Origin'] = '*'
        self.response.headers['Access-Control-Allow-Headers'] = 'Origin, X-Requested-With, Content-Type, Accept'
        self.response.headers['Access-Control-Allow-Methods'] = 'POST, GET, PUT, DELETE'
    def get(self):
        possible_issue = "none"
        self.response.headers.add_header('Access-Control-Allow-Origin', '*')
        scientistName = self.request.get("scientistName").strip()
        if scientistName == "":
            possible_issue = "name"

        if possible_issue == "none":
            qry = models.Project.query(models.Project.projectName == scientistName).fetch()
            logging.error("qry == " + str(qry))
            if qry == [] or qry == None:
                messageBack(self, 406, "Get Un-Successfull: Scientist Name = " + str(scientistName))
            else:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()

                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))

        elif possible_issue == "name":
            messageBack(self, 406, "Invalid Request: Scientist Name was not entered correctly")