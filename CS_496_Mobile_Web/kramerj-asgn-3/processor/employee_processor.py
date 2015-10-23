import json
import logging

from google.appengine.ext import ndb
from models import Employee, Performance
import models
import processor
import webapp2


def messageBack(self, err, msg):
    self.response.status = err
    self.response.write(msg)
    return
           

PARENT_KEY = ndb.Key(models.Employee, "employee_root")
logging.getLogger().setLevel(logging.DEBUG)

class AddEmployee(webapp2.RequestHandler):
    def post(self):
        #logging.error("testtttt == ")
        first_name = self.request.get('first_name')
        last_name = self.request.get('last_name')
        employee_username = self.request.get('employee_username')
        department = self.request.get('department')
        # logging.error("ERROR == " + str(first_name))
        
        #addNewEmp(first_name, last_name, employee_username, department)
        
        qry = models.Employee.query(models.Employee.employee_username == employee_username).get()
        logging.error("qry == " + str(qry))
        if qry != None:
            messageBack(self, 406, "Invalid Request: employee_username \"" + str(employee_username) + "\" already exists")
        
        #Used to add the employee data to the datastore
        elif first_name and last_name and employee_username and department:
            new_employee = Employee(parent=PARENT_KEY,
                                    first_name=first_name,
                                    last_name=last_name,
                                    employee_username=employee_username,
                                    department=department)
            
            employee_key = new_employee.put() 
            #messageBack(self, 200, "Success: ID # = " + str(employee_key.id()) + "\n")    
            new_employee.id = employee_key.id()
            employee_key = new_employee.put()
            messageBack(self, 200, "Success: ID # = " + str(employee_key.id())) 

        elif first_name == None or first_name == '':
            messageBack(self, 406, "Invalid Request: first_name is required")            
        elif last_name == None or last_name == '':
            messageBack(self, 406, "Invalid Request: last_name is required")
        elif employee_username == None or employee_username =='':
            messageBack(self, 406, "Invalid Request: employee_username is required")
        elif department == None or department == '':
            messageBack(self, 406, "Invalid Request: department is required")
        else:
            messageBack(self, 406, "Invalid Request: A problem occured while adding employee")



# Concept here is: IF the user is deleting the employee they are deleting all
# the data the goes withe the employee. Hence the Performance table is also 
# removed of all data retaining to passed in  ID
class DeleteEmployeeByID(webapp2.RedirectHandler):
    def delete(self):
        id = self.request.get('id')
        if id.isdigit():         
            qry = models.Employee.query(models.Employee.id == int(id)).get()
            if qry != None:   
                employee_username = qry.employee_username     
                #logging.error("Username == " + str(username))
                test = qry.key.delete()
                #logging.error("test == " + str(test))
                
                qry = models.Performance.query(models.Performance.employee_username == employee_username).get()
                qry = models.Performance.query(models.Performance.employee_username == employee_username).fetch()
                
                #Used to validate a successful query
                if qry != None or qry != []:
                    i=0            
                    # Cycles through and deletes all queries that match the employee_username 
                    # in the performance table. 
                    while i <= len(qry) - 1:     
                        qry[i].key.delete()    
                        i+=1
                # Used to delete all performances that reference this employess username
                #isDeleted = deleteAllPerformance(username)
                if test == None:
                    messageBack(self, 200, "Delete Successfull: ID  = " + str(id))
            else:
                messageBack(self, 406, "Delete Un-Successfull: ID  = " + str(id))
        else:
            messageBack(self, 406, "Delete Un-Successfull: ID  = " + str(id))
        

# Concept here is: IF the user is deleting the employee they are deleting all
# the data the goes withe the employee. Hence the Performance table is also 
# removed of all data retaining to passed in  employee_username
class DeleteEmployeeByEmployeeUsername(webapp2.RequestHandler):
    def delete(self):
        employee_username = self.request.get('employee_username')
        qry = models.Employee.query(models.Employee.employee_username == employee_username).get()
        logging.error("qry == " + str(qry))
        if qry != None:        
            logging.error("Username == " + str(employee_username))
            test = qry.key.delete()
            logging.error("test == " + str(test))
            
            qry = models.Performance.query(models.Performance.employee_username == employee_username).get()
            qry = models.Performance.query(models.Performance.employee_username == employee_username).fetch()
            
            #Used to validate a successful query
            if qry != None or qry != []:
                i=0            
                # Cycles through and deletes all queries that match the employee_username 
                # in the performance table. 
                while i <= len(qry) - 1:     
                    qry[i].key.delete()    
                    i+=1
            # Used to delete all performances that reference this employess username
            #isDeleted = deleteAllPerformance(username)
            if test == None:
                messageBack(self, 200, "Delete Successfull: employee_username = " + str(employee_username))
        else:
            messageBack(self, 406, "Delete Un-Successfull: employee_username  = " + str(employee_username))
        


class GetEmployeeByID(webapp2.RequestHandler):
    def get(self):
        id = self.request.get('id')        
        if id.isdigit():
            qry = models.Employee.query(models.Employee.id == int(id)).fetch()
            logging.error("qry == " + str(qry))
            if qry == [] or qry == None:        
                messageBack(self, 406, "Get Un-Successfull: id # = " + str(id))               
            else:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()
                    
                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))

        else:
            messageBack(self, 406, "Invalid Request: id " + str(id) + " was not entered")


class GetEmployeeByEmploeeUsername(webapp2.RequestHandler):
    def get(self):
        employee_username = self.request.get('employee_username')
        qry = models.Employee.query(models.Employee.employee_username == employee_username).fetch()
        logging.error("qry == " + str(qry))
        if employee_username:
            if qry == [] or qry == None:        
                messageBack(self, 406, "Delete Un-Successfull: employee_username = " + str(employee_username))               
            else:
                holder={}
                for index, row in enumerate(qry):
                    holder[index] = row.to_dict()
                    
                self.response.status = 200
                self.response.write(json.dumps(holder, sort_keys=True, indent=4))

        else:
            messageBack(self, 406, "Invalid Request: employee_username " + str(employee_username) + " was not entered")




class ReplaceEmployeeDataByUsername(webapp2.RequestHandler):
    def put(self):
        employee_username = self.request.get('employee_username')
        first_name = self.request.get("first_name")
        last_name = self.request.get("last_name")
        department = self.request.get("department")
        
        if employee_username:
            qry = models.Employee.query(models.Employee.employee_username == employee_username).get()
            if qry:
                qry.first_name = first_name
                qry.last_name = last_name
                qry.department = department
                qry.put()
                messageBack(self, 200, "Success: all data changed")
                
            else:
                messageBack(self, 406, "Invalid Request: Issue retrieving data") 
        else:
            messageBack(self, 406, "Invalid Request: employee_username = " + str(employee_username) + " was not entered correctly") 



class ReplaceEmployeeDataByID(webapp2.RequestHandler):
    def put(self):
        id = self.request.get('id')
        first_name = self.request.get("first_name")
        last_name = self.request.get("last_name")
        department = self.request.get("department")
        
        if id.isdigit():
            qry = models.Employee.query(models.Employee.id == int(id)).get()
            if qry:
                qry.first_name = first_name
                qry.last_name = last_name
                qry.department = department
                qry.put()
                messageBack(self, 200, "Success: all data changed")
                
            else:
                messageBack(self, 406, "Invalid Request: Issue retrieving data") 
        else:
            messageBack(self, 406, "Invalid Request: id = " + str(id) + " was not entered correctly") 









        
        
        