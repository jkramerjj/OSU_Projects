from google.appengine.ext import ndb

class Employee(ndb.Model):
    id = ndb.IntegerProperty()
    first_name = ndb.StringProperty()
    last_name = ndb.StringProperty()
    employee_username = ndb.StringProperty()
    department = ndb.StringProperty()

    
    
class Performance(ndb.Model):
    personal_score = ndb.IntegerProperty()
    department_rating = ndb.IntegerProperty()
    job = ndb.StringProperty()
    #employee_key = ndb.KeyProperty(kind=Employee)
    employee_username = ndb.StringProperty() ## used to hold emp user name
    id = ndb.IntegerProperty()
    
    
    
