import json
import logging

from google.appengine.ext import ndb
from models import Employee, Performance
import models
import webapp2


def messageBack(self, err, msg):
    self.response.status = err
    self.response.write(msg)
    return

PARENT_KEY = ndb.Key(models.Performance, "performance_root")

logging.getLogger().setLevel(logging.DEBUG)

class AddPerformance(webapp2.RequestHandler):
    def post(self):
        personal_score = self.request.get('personal_score')
        department_rating = self.request.get('department_rating')
        job = self.request.get('job')
        employee_username = self.request.get("employee_username")
        #messageBack(self, 406, "emp ==" + str(employee_username))
        #logging.error("emp == " + str(qry))
        qry = models.Employee.query(models.Employee.employee_username == employee_username).get()
        logging.error("qry == " + str(qry))
        if qry == None or qry == []:
           messageBack(self, 406, "Invalid Request: employee_username \"" + str(employee_username) + "\" does not exists")
           #messageBack(self, 406, "qry == " + str(qry))
        elif personal_score == None or personal_score == '':
            messageBack(self, 406, "Invalid Request: personal_score is required")
        elif department_rating == None or department_rating == '':
            messageBack(self, 406, "Invalid Request: department_rating is required")                 
        elif employee_username == None or employee_username == '':
            messageBack(self, 406, "Invalid Request: employee_username is required")
        elif job == None or job == '':
            messageBack(self, 406, "Invalid Request: job is required")
        elif employee_username and personal_score and job:
            new_performance = Performance(parent=PARENT_KEY,
                                          personal_score = int(personal_score),
                                          department_rating = int(department_rating),
                                          job = job,
                                          employee_username = employee_username)
            performance_key = new_performance.put()
            new_performance.id = performance_key.id()
            performance_key = new_performance.put()
            messageBack(self, 200, "Success: ID # = " + str(performance_key.id())) 

        else:
            messageBack(self, 406, "Invalid Request: A problem occurred while adding performance")     
            
            
            
class DeletePerformanceAll(webapp2.RequestHandler):
    def delete(self):
        username = self.request.get('employee_username')
        #Used to validate username was sent over
        if username == None or username == '':
            messageBack(self, 406, "Invalid Request: employee_username required")
        elif username:
            qry = models.Performance.query(models.Performance.employee_username == username).get()
            qry = models.Performance.query(models.Performance.employee_username == username).fetch()
            
            #Used to validate a successful query
            if qry == None or qry == []:
                messageBack(self, 406, "Invalid Request: employee_username \"" + str(username) + "\" does not exists")
            
            else:
                i=0            
                # Cycles through and deletes all queries that match the employee_username
                while i <= len(qry) - 1:     
                    qry[i].key.delete()    
                    i+=1
                
                messageBack(self, 200, "Success: All " +str(username) + " employee_username's deleted")
                    #qry = models.Performance.query(models.Performance.employee_username == username).fetch()
                    #logging.error("qry length == " + str(len(qry)))
                    #logging.error("qry after == " + str(qry))        



  
           
class DeletePerformanceByID(webapp2.RequestHandler):
    def delete(self):
        if self.request.get('id') != '':
            id = self.request.get('id')
            logging.error("ID  == " + str(id))
            
            if id.isdigit():
            
                if id != None or id != '':
                    qry = models.Performance.query(models.Performance.id == int(id)).get()
                    if qry == None or qry == '':
                        messageBack(self, 406, "Invalid Request: ID# = " + str(id) + " does not exist")
                        return
                    logging.error("personal score qry  == " + str(qry))
                    test = qry.key.delete()
                    logging.error("test  == " + str(test))
                    messageBack(self, 200, "Success: ID# = " + str(id) + " was deleted")
            else:
                messageBack(self, 406, "Invalid Request: id is incorrect.")
                
        else:
            messageBack(self, 406, "Invalid Request: id is required")
        
  



class GetPerformanceAllEmployerUsername(webapp2.RequestHandler):
    def get(self):
        employee_username = self.request.get("employee_username")
        #sjob = self.request.get("job")
        
        if employee_username:
            qry = models.Performance.query(models.Performance.employee_username == employee_username).fetch()
            if qry:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()
                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))
            else:
                messageBack(self, 406, "Invalid Request: employer_username = " + str(employee_username) + " does not exist")
        else:
            messageBack(self, 406, "Invalid Request: employer_username = " + str(employee_username) + " was not entered")
                
        
        
class GetPerformanceByID(webapp2.RequestHandler):
    def get(self):
        id = self.request.get("id")
        
        if id.isdigit():
            qry = models.Performance.query(models.Performance.id == int(id)).fetch()
            if qry:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()
                    
                logging.error("Type of holder == " + str(type(holder)))
                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))
            else:
                messageBack(self, 406, "Invalid Request: ID# = " + str(id) + " does not exist")
        else:
            messageBack(self, 406, "Invalid Request: ID# = " + str(id) + " does not exist")
                        
 
        
class ReplacePerformanceDataByID(webapp2.RequestHandler):
    def put(self):
        personal_score = self.request.get("personal_score")
        department_rating = self.request.get("department_rating")
        job = self.request.get("job")
        #employee_username = self.request.get("employee_username")
        id = self.request.get('id')
        logging.error("id  == " + str(id))

        if id.isdigit():
            qry = models.Performance.query(models.Performance.id == int(id)).get()
            logging.error("qry  == " + str(qry))
            if qry: #department_rating and personal_score and job:
                qry.personal_score = int(personal_score)
                qry.department_rating = int(department_rating)
                qry.job = job
                qry.put()
                messageBack(self, 200, "Success: all data changed")
        
        
            else:
                messageBack(self, 406, "Invalid Request: Invalid ID entered")
        
        else:
            messageBack(self, 406, "Invalid Request: ID = " + str(id) + " does not exist") 
        
        
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    