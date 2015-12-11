import os, jinja2
from google.appengine.ext import ndb
from models import ScientistData, Project
import webapp2


from google.appengine.api import users

jinja_env = jinja2.Environment(
  loader=jinja2.FileSystemLoader(os.path.dirname(__file__)),
  autoescape=True)

#Generic key to server as the parent.


user = users.get_current_user()
def get_parent_key(user):
  return ndb.Key("Entity", user.email().lower())
#PARENT_KEY = ndb.Key("Entity", user.email().lower())



class ScientistPage(webapp2.RequestHandler):
    def get(self):
        user = users.get_current_user()
        science_query = ScientistData.query(ancestor=get_parent_key(user)).order(ScientistData.scientistName)
        project_query = Project.query(ancestor=get_parent_key(user)).order(Project.scientistName)

        #list = zip(project_query, science_query)

        template = jinja_env.get_template("templates/science.html")
        self.response.write(template.render({"science_query": science_query,
                                             "project_query": project_query,
                                             'user_email': user.email(),
                                             'logout_url': users.create_logout_url("/")
                                             }))