import json
import logging

import models
from google.appengine.ext import ndb
import webapp2
import jinja2


class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write('Hello world! AsGN 3')
