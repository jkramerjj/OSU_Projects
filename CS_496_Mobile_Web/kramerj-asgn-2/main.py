#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# References: http://www.rosebotics.org/web-appengine/unit?unit=2

import os, jinja2, logging, datetime
from google.appengine.ext import ndb
from models import ScientistData
import webapp2



jinja_env = jinja2.Environment(
  loader=jinja2.FileSystemLoader(os.path.dirname(__file__)),
  autoescape=True)

#Generic key to server as the parent. 
PARENT_KEY = ndb.Key("Entity", "scientist_root")


class ScientistPage(webapp2.RequestHandler):
    def get(self):
        science_query = ScientistData.query(ancestor=PARENT_KEY).order(-ScientistData.last_touch_date_time)
        template = jinja_env.get_template("templates/science.html")
        self.response.write(template.render({"science_query": science_query
                                             }))
def checktheboxes(checkMe):
    if checkMe != "True":
        checkMe = "False"
    return checkMe


# This is a lot going on here, I could not get seperate functions to work, so all the code
# is one giant list until I can figure our functions in webapp2
class InsertScientist(webapp2.RedirectHandler):      
    def post(self):
        possible_issue = "none"
        if self.request.get("entity-key"):
            science_key = ndb.Key(urlsafe=self.request.get("entity-key"))
            science_data = science_key.get()
       
            # Logic used to remove spaces before entering into datastore    
            science_data.scientistName = self.request.get("scientistName").lstrip()
            science_data.dateOfBirth = self.request.get("dob").replace(" ", "")
            science_data.sex = self.request.get("inlineRadioOptions").replace(" ", "")
            
            logging.error("ERROR == " + str(science_data.sex))
            
             # Checks to make sure if a checkbox is not marked to lable it as False     
            science_data.comsci_checked = checktheboxes(self.request.get("comsci_checked").replace(" ", ""))
            science_data.math_checked = checktheboxes(self.request.get("math_checked").replace(" ", ""))            
            science_data.biology_checked = checktheboxes(self.request.get("biology_checked").replace(" ", ""))   
            science_data.physics_checked = checktheboxes(self.request.get("physics_checked").replace(" ", ""))
            science_data.other_checked = checktheboxes(self.request.get("other_checked").replace(" ", "")) 
            # End checkbox logic
            
            science_data.famousDiscovery = self.request.get("famous_discovery").replace(" ", "")
            
            if science_data.scientistName =="":
                possible_issue = "name"
                
            dateOfBirth = self.request.get("dob")
            try:
                datetime.datetime.strptime(dateOfBirth,'%d-%m-%Y')
               
            except ValueError:
                possible_issue = "dob"
                #template = jinja_env.get_template("templates/dob_issue.html")
                #self.response.write(template.render()) 

            if science_data.sex != "Male" and science_data.sex != "Female":
                possible_issue = "sex"
                
            if (science_data.other_checked == "False" and science_data.comsci_checked == "False" and 
                science_data.math_checked == "False" and science_data.biology_checked == "False" 
                and science_data.physics_checked == "False"):
                possible_issue = "specialities"
            
            if possible_issue == "none":
                science_data.put()
                self.redirect(self.request.referrer)
            elif possible_issue == "duplicate":
                template = jinja_env.get_template("templates/duplicate_user.html")
                self.response.write(template.render())
            else:
                template = jinja_env.get_template("templates/error_message.html")
                self.response.write(template.render())
                  
        # This else is used to enter in data for the first time
        else:
            logging.getLogger().setLevel(logging.DEBUG)
            possible_issue = "none"
            
            # Used to check for empty string
            scientistName = self.request.get("scientistName")
            if str(scientistName) != str(""):
                possible_issue = 'none'
            else:
                possible_issue = "name"
  
             # Used to check if DOB is in a DD-MM-YYYY format
            dateOfBirth = self.request.get("dob")
            try:
                datetime.datetime.strptime(dateOfBirth,'%d-%m-%Y')
               
            except ValueError:
                possible_issue = "dob"
                #template = jinja_env.get_template("templates/dob_issue.html")
                #self.response.write(template.render()) 

                
            # Checks to make sure a radio is selected
            sex = self.request.get("inlineRadioOptions")
            if sex != "Male" and sex != "Female":
                possible_issue = "sex"
                
            # Checks to make sure if a checkbox is not marked to lable it as False 
            comsci_checked = checktheboxes(self.request.get("comsci_checked"))        
            math_checked = checktheboxes(self.request.get("math_checked"))
            biology_checked = checktheboxes(self.request.get("biology_checked"))
            physics_checked = checktheboxes(self.request.get("physics_checked"))
            other_checked = checktheboxes(self.request.get("other_checked"))
            
             # Checks to make sure make sure at least one check box was marked 
            if (other_checked == "False" and comsci_checked == "False" and math_checked == "False" 
                and biology_checked == "False" and physics_checked == "False"):
                possible_issue = "specialities"
                    
            famousDiscovery = self.request.get("famous_discovery")
        
            ## quries the datastore to check and see if the user entered scientist already exists
            qry = ScientistData.query(ScientistData.scientistName == str(scientistName),
                                      ScientistData.dateOfBirth == str(dateOfBirth),
                                      ScientistData.sex == str(sex),
                                      ScientistData.biology_checked  == str(biology_checked),
                                      ScientistData.comsci_checked == str(comsci_checked),
                                      ScientistData.math_checked == str(math_checked),
                                      ScientistData.physics_checked == str(physics_checked),
                                      ScientistData.other_checked == str(other_checked),
                                      ScientistData.famousDiscovery == str(famousDiscovery)
                                      )
            
            people = qry.fetch(100)
            if people != []:
                possible_issue = "duplicate"
                
            # Logic here checks for any errors which would be a 1, if it is a 0,
            # then proceed with entering data into datastore
            if possible_issue == "none":
                new_scientist = ScientistData(parent = PARENT_KEY,
                                           scientistName = scientistName,
                                           dateOfBirth = dateOfBirth,
                                           sex = sex,
                                           math_checked = math_checked,
                                           comsci_checked = comsci_checked,
                                           biology_checked = biology_checked,
                                           physics_checked = physics_checked,
                                           other_checked = other_checked,
                                           famousDiscovery = famousDiscovery)
                new_scientist.put()
                self.redirect(self.request.referrer)
            
            # If here there was an error, it will load the error html
            elif possible_issue == "duplicate":
                template = jinja_env.get_template("templates/duplicate_user.html")
                self.response.write(template.render())
            else:
                template = jinja_env.get_template("templates/error_message.html")
                self.response.write(template.render())


# Simply deletes the data from the datastore via the entity_key
class DeleteScientist(webapp2.RedirectHandler):
    def post(self):
        science_key = ndb.Key(urlsafe=self.request.get("entity_key"))
        science_key.delete()
        self.redirect(self.request.referrer)



# Runs the framework of the app
app = webapp2.WSGIApplication([
    ('/', ScientistPage),
    ('/insertscientist', InsertScientist),
    ('/deletescientist', DeleteScientist)
], debug=True)






























