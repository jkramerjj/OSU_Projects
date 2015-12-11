from google.appengine.ext import ndb


class ScientistData(ndb.Model):   
    scientistName = ndb.StringProperty(required=True)
    dateOfBirth = ndb.StringProperty()
    sex = ndb.StringProperty()
    famousDiscovery = ndb.StringProperty()    



class Project(ndb.Model):
    projectName = ndb.StringProperty()
    scientistName = ndb.StringProperty(required=True)
    scientist_key = ndb.KeyProperty(kind=ScientistData)
    longitude = ndb.StringProperty()
    latitude = ndb.StringProperty()
    altitude = ndb.StringProperty()


