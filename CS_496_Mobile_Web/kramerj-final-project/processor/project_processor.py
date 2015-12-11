import json
import logging
import os
from google.appengine.api import users
from google.appengine.ext import ndb
import jinja2
from models import Project
from models import ScientistData
import webapp2
import models



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
class EditProject(webapp2.RequestHandler):
    def post(self):
        #The GAE APP is built around POST and then python to handle the logic
        possible_issue = "none"
        qry = Project.query(Project.projectName == str(self.request.get("projectName").lstrip()))
        dup_projects = qry.fetch()

        if dup_projects != []:
            messageBack(self, 406, "Error: Cannot have duplicate Project names assigned to same Scientist")
            template = jinja_env.get_template("templates/duplicate_project.html")
            self.response.write(template.render())

        elif self.request.get("scientistName").lstrip() != "":
             ## IF this gets called the user turned off jQuery
            messageBack(self, 406, "Error: Please use jQuery. A name edits are not allowed")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())

        elif self.request.get("projectName").lstrip() == "":
            messageBack(self, 406, "Error: Project name was blank")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())

        else:
            project_key = ndb.Key(urlsafe=self.request.get("entity-key").strip())
            project_data = project_key.get()
            project_data.projectName = self.request.get("projectName").lstrip()
            project_data.put()
            messageBack(self, 200, "Edit was successful")
            self.redirect(self.request.referrer)

    ## API SPECIFIC PUT CODE ###
    def put(self):
        if self.request.get("scientistName").lstrip() != "":
            ## IF this gets called the user turned off jQuery
            messageBack(self, 406, "Error: Please use jQuery. A name edits are not allowed")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())

        elif self.request.get("projectName").lstrip() == "":
            messageBack(self, 406, "Error: Project name was blank")
            template = jinja_env.get_template("templates/name_issue.html")
            self.response.write(template.render())

        else:
            project_key = ndb.Key(urlsafe=self.request.get("entity-key").strip())
            project_data = project_key.get()
            project_data.projectName = self.request.get("projectName").lstrip()
            project_data.put()
            messageBack(self, 200, "Edited successfully")



# Adds data via getting data sent over by the user. It will get their GOOGLE account.
# plus other model data and then check to make sure it fits the model guidlines, such as
# no blank projects names can be entered. It will then add the entry or return an error
class AddProject(webapp2.RequestHandler):
    ## API SPECIFIC POST CODE ###
    #The GAE APP is built around POST and then python to handle the logic
    def post(self):
        user = users.get_current_user()
        logging.getLogger().setLevel(logging.DEBUG)
        possible_issue = "none"

        # Used to check for empty string
        scientistName  = self.request.get("science_key").strip()
        projectName = self.request.get("project_name").strip()
        longitudeName = self.request.get("longitude_name").strip()
        latitudeName = self.request.get("latitude_name").strip()
        altitudeName = self.request.get("altitude_name").strip()

        ## queries the datastore to check and see if the user entered project already exists
        qry = Project.query(Project.projectName == str(projectName))

        dup_projects = qry.fetch()
        if dup_projects != []:
            if scientistName == dup_projects[0].scientistName:
                possible_issue = "duplicate"
            pass
        if projectName == "":
            possible_issue = "name"
        elif longitudeName == "" or latitudeName == "" or altitudeName == "":
            possible_issue = "gps"

        qry2 = ScientistData.query(ScientistData.scientistName == str(scientistName))
        name_exist = qry2.fetch()
        if name_exist == []:
            possible_issue = "no scientists"
            

        # Logic here checks for any errors which would be a 1, if it is a 0,
        # then proceed with entering data into datastore
        if possible_issue == "none":
            new_project = Project(parent = get_parent_key(user),
                                        projectName = projectName,
                                        scientistName = scientistName,
                                        longitude = longitudeName,
                                        latitude = latitudeName,
                                        altitude = altitudeName
                                  )
            new_project.put()
            messageBack(self, 200, "Add was successful")
            self.redirect(self.request.referrer)

        # If here there was an error, it will load the error html
        elif possible_issue == "duplicate":
            template = jinja_env.get_template("templates/duplicate_project.html")
            self.response.write(template.render())
        elif possible_issue == "name":
            template = jinja_env.get_template("templates/project_name_issue.html")
            self.response.write(template.render())
        elif possible_issue == "gps":
            template = jinja_env.get_template("templates/gps_issue.html")
            self.response.write(template.render())
        elif possible_issue == "no scientists":
            template = jinja_env.get_template("templates/no_scientists.html")
            self.response.write(template.render())
        else:
            template = jinja_env.get_template("templates/error_message.html")
            self.response.write(template.render())


# Simply deletes the data from the project model via the entity_key
# First gets project data via a key, then stores the scientist name in a string,
# then deletes the scientist entry and then deletes all references of that name in the
# project model.
class DeleteProject(webapp2.RequestHandler):
    #The GAE APP is built around POST and then python to handle the logic
    def post(self):
        project_key = ndb.Key(urlsafe=self.request.get("entity_key").strip())
        try:
            project_key.delete()
            messageBack(self, 200, "Delete was successful")
        except ValueError:
            messageBack(self, 406, "Error: Delete was Un-Successful")
            template = jinja_env.get_template("templates/delete_issue.html")
            self.response.write(template.render())

        self.redirect(self.request.referrer)

    ## API SPECIFIC DELETE CODE ###
    def delete(self):
        project_key = ndb.Key(urlsafe=self.request.get("entity_key").strip())
        try:
            project_key.delete()
            messageBack(self, 200, "Delete was successful")
        except ValueError:
            messageBack(self, 406, "Error: Delete was Un-Successful")



# This code is only used for developers that would like to connect to my API.
# The GAE App that runs this code would not use this particular section of code, because
# the App is built with Jinja2 to display info
class GetProjectByName(webapp2.RequestHandler):
    ## API SPECIFIC GET CODE ###
    def options(self):
        self.response.headers['Access-Control-Allow-Origin'] = '*'
        self.response.headers['Access-Control-Allow-Headers'] = 'Origin, X-Requested-With, Content-Type, Accept'
        self.response.headers['Access-Control-Allow-Methods'] = 'POST, GET, PUT, DELETE'
    def get(self):
        possible_issue = "none"
        self.response.headers.add_header('Access-Control-Allow-Origin', '*')
        projectName = self.request.get('project_name').lstrip()
        if projectName == "":
            possible_issue = "name"

        if possible_issue == "none":
            qry = models.Project.query(models.Project.projectName == projectName).fetch()
            logging.error("qry == " + str(qry))
            if qry == [] or qry == None:
                messageBack(self, 406, "Get Un-Successfull: Project Name = " + str(projectName))
            else:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()

                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))

        elif possible_issue == "name":
            messageBack(self, 406, "Invalid Request: Project Name was not entered correctly")



















