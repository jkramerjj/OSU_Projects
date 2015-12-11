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



import webapp2
from processor import scientist_processor
from processor import project_processor
from processor import run_app
import processor


# Runs the framework of the app
app = webapp2.WSGIApplication([
    ('/', processor.run_app.ScientistPage),
    ('/add_scientist', processor.scientist_processor.AddScientist),
    ('/edit_scientist', processor.scientist_processor.EditScientist),
    ('/delete_scientist', processor.scientist_processor.DeleteScientist),
    ('/get_scientist_by_name', processor.scientist_processor.GetScientistByName),

    ('/add_project', processor.project_processor.AddProject),
    ('/edit_project', processor.project_processor.EditProject),
    ('/delete_project', processor.project_processor.DeleteProject),
    ('/get_project_by_name', processor.project_processor.GetProjectByName)

], debug=False)






























