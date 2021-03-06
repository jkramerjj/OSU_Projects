import npyscreen
from connection import Connection
from mainmenu import MainMenu


class MainForm(npyscreen.FormBaseNew):
    """
    The application's MAIN form. This form is responsible for delegating DB connection first and then delegating
    available actions in our application as selected by the user from a list. FormBaseNew is used to avoid having
    to select any OK or CANCEL type options
    """
    def create(self):
        """
        Creates the MainForm, checks for valid connection before continuing to display
        :return:
        """
        self.how_exited_handers[npyscreen.wgwidget.EXITED_ESCAPE] = self.exit
        self.center_on_display()
        self.name = "Curses PSQL"
        self.actions = [
            {'Tables': self.show_tables},
            {'Artists': self.show_artists},
            {'Logout': self.logout},
            {'Exit': self.exit}
        ]
        # need just the keys for the menu
        self.actionkeys = self.makeactionkeys()
        # hide the widgets at first, they look bad displaying when we're logging in
        self.menu = self.add(MainMenu, w_id='menu', values=self.actionkeys, hidden=True,
                             max_height=len(self.actions) + 1)
        # create some simple on screen help
        self.helper = self.add(npyscreen.TitleFixedText, w_id='helper', name="Help: Select:Enter Move:Up/Down Exit:Esc",
                               hidden=True, rely=self.min_l)

    def activate(self):
        """
        Check if there's an active DB connection, otherwise, show widgets and edit
        :return:
        """
        if Connection.Instance().getconnection() is None:
            self.parentApp.switchForm("LOGIN")
        else:
            for i in self._widgets__:
                i.hidden = False
                i.update()
            self.edit()

    def show_artists(self):
        """
        Dummy action to simply start a new queryresultsform and pass a hardcoded query
        :return:
        """
        self.parentApp.getForm('QUERYRESULTS').value = "select * from \"Artist\";"
        self.parentApp.switchForm('QUERYRESULTS')

    def show_tables(self):
        """
        Dummy action to simply start a new queryresultsform and pass a hardcoded query
        :return:
        """
        self.parentApp.getForm('QUERYRESULTS').value = "select relname from pg_class where relkind='r' and relname !~ '^(pg_|sql_)';"
        self.parentApp.switchForm('QUERYRESULTS')

    def logout(self):
        """
        Close the DB connection, bring user back to login form, hide widgets
        :return:
        """
        Connection.Instance().logout()
        if Connection.Instance().getconnection() is not None:
            for i in self._widgets__:
                i.hidden = True
                i.update()
            self.parentApp.switchForm("LOGIN")
        else:
            npyscreen.notify_confirm("Logout Failure")

    def exit(self):
        """
        Logout and exit
        :return:
        """
        self.parentApp.setNextForm(None)
        Connection.Instance().logout()
        self.editing = False
        self.parentApp.switchFormNow()

    def makeactionkeys(self):
        """
        Flattens the dictionary of actions in order desired (top to bottom in declare) and puts into keys list
        :return: list of keys within the list of dictionaries in order declared
        """
        actionkeys = []
        for i in self.actions:
            for key in i.iterkeys():
                actionkeys.append(key)
        return actionkeys
