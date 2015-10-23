from google.appengine.ext import ndb
from itertools import repeat


class ScientistData(ndb.Model):
   
    scientistName = ndb.StringProperty(required=True)
    dateOfBirth = ndb.StringProperty()
    sex = ndb.StringProperty()
    comsci_checked = ndb.StringProperty()
    math_checked = ndb.StringProperty()
    biology_checked = ndb.StringProperty()
    physics_checked = ndb.StringProperty()
    other_checked = ndb.StringProperty()
    famousDiscovery = ndb.StringProperty()
    
    last_touch_date_time = ndb.DateTimeProperty(auto_now=True)
    