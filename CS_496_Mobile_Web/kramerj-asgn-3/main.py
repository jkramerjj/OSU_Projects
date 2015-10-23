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
import logging
import os

import jinja2
from processor import employee_processor
from processor import main_page_processor
from processor import performance_processor
import processor
import webapp2



class MainHandler(webapp2.RequestHandler):
    def get(self):
        self.response.write('ASGN 3!!!')


app = webapp2.WSGIApplication([
    ('/', MainHandler),
    ('/employee/add', processor.employee_processor.AddEmployee),
    ('/employee/delete_by_id', processor.employee_processor.DeleteEmployeeByID),
    ('/employee/delete_by_employee_username', processor.employee_processor.DeleteEmployeeByEmployeeUsername),
    ('/employee/get_by_id', processor.employee_processor.GetEmployeeByID),
    ('/employee/get_by_employee_username', processor.employee_processor.GetEmployeeByEmploeeUsername),
    ('/employee/replace_data_by_employee_username', processor.employee_processor.ReplaceEmployeeDataByUsername),
    ('/employee/replace_data_by_id', processor.employee_processor.ReplaceEmployeeDataByID),
    
    ('/performance/add', processor.performance_processor.AddPerformance),
    ('/performance/delete_all_by_employer_username', processor.performance_processor.DeletePerformanceAll),
    ('/performance/delete_by_id', processor.performance_processor.DeletePerformanceByID),
    ('/performance/get_all_employee_username', processor.performance_processor.GetPerformanceAllEmployerUsername),
    ('/performance/get_by_id', processor.performance_processor.GetPerformanceByID),
    ('/performance/replace_data_by_id', processor.performance_processor.ReplacePerformanceDataByID)
    
], debug=True)


























