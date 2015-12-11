import npyscreen
from connection import Connection

class QueryResultsForm(npyscreen.ActionForm):
    """
    Class that displays results from a query
    """
    def activate(self):
        """
        Need to override activate here in order to do checking of the Connection
        ** NOTE ** : you must call before/edit/after editing on your own if you override activate
        :return:
        """
        if self.value is None:
            npyscreen.notify_confirm('Error: No query provided')
            self.parentApp.switchForm('MAIN')
        if Connection.Instance().getconnection() is None:
            npyscreen.notify_confirm('Error: No connection present')
            self.parentApp.switchForm('LOGIN')
        self.beforeEditing()
        self.edit()

    def beforeEditing(self):
        """
        Update the results lists
        :return:
        """
        self.updateresults()

    def updateresults(self):
        """
        Actual data gathering of results
        :return:
        """
        conn = Connection.Instance().getconnection()
        cursor = conn.cursor()
        cursor.execute(self.value)
        self.data = cursor.fetchall()
        self.cleaneddata = self.cleanUpListForOutput(self.data)
        self.w_results.values = self.cleaneddata
        self.w_results.update()

    def create(self):
        """
        Creation of the widgets being used
        :return:
        """
        self.value = None
        self.w_results = self.add(npyscreen.MultiLineAction, name='Results')


    def on_ok(self):
        """
        If OK is used in form, do this action
        :return:
        """
        self.parentApp.switchForm('MAIN')

    def on_cancel(self):
        """
        If Cancel is used in form, do this action
        :return:
        """
        self.on_ok()

    def cleanUpListForOutput(self, data):
        """
        Cleans up the values from a query into a pretty list
        :param data: raw PSQL query data
        :return: a cleaned up list in terms of PSQL syntax
        """
        newlist = []
        for i in data:
            newlist.append(str(i).translate(None, '(),\''))
        return newlist

