#!/usr/bin/env python

import npyscreen
from mainform import MainForm
from loginform import LoginForm
from queryresultsform import QueryResultsForm

class Psqlapp(npyscreen.NPSAppManaged):
    """
    Using npyscreen's recommended approach for handling a more complex application
    """
    def onStart(self):
        """
        Does form registration
        :return:
        """
        self.addForm('MAIN', MainForm)
        self.addForm('LOGIN', LoginForm)
        self.addForm('QUERYRESULTS', QueryResultsForm)


if __name__ == '__main__':
    APP = Psqlapp()
    APP.run()
