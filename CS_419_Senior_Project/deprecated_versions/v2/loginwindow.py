from windows import Windows
from form import Form


class LoginWindow(Windows):
    """
    Represents the LoginWindow action required for gathering a database connection string
    :class: LoginWindow
    :parent: Windows
    """
    def __init__(self, parent, **kwargs):
        """
        Allows variable length setting of any class attrs
        :param kwargs: arguments for class, in form of attr=value, attr2=value2, etc.
        :return:
        """
        # call super class init first
        Windows.__init__(self, **kwargs)

        # set required
        self.parent = parent
        # set dynamic variables
        for key, value in kwargs.iteritems():
            setattr(self, key, value)
        # set internals
        self.menuitems = ['Database', 'User', 'Password', 'Host', 'Port', 'Accept']
        self.helpitems = [{'Move': 'Up/Dn'}, {'Select': 'Enter'}, {'Esc': 'Cancel'}]
        self.form = Form(self.parent, self.menuitems, self.helpitems)
        self.form.setup()

    def getlogin(self):
        """
        executes the form as required to bring back the database connection string
        :return: dict of lowercase menuitems as keys, with form filled values
        """
        self.refresh()
        return self.form.run()

    def refresh(self):
        """
        Refreshes in proper order
        :return:
        """
        self.form.refresh()
