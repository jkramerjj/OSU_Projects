from windows import Windows
from taskbar import TaskBar


class TaskBarWindow(Windows):
    """
    Represents the StructureWindow action required for gathering a database manipulation string
    :class: LoginWindow
    :parent: Windows
    """

    def __init__(self, parent, **kwargs):
        """
        Allows variable length setting of any class attrs
        :param kwargs: arguments for class, in form of attr=value, attr2=value2, etc.
        :return:
        """

        Windows.__init__(self, **kwargs)

        self.parent = parent

        for key, value in kwargs.iteritems():
            setattr(self, key, value)



        self.taskBarItems = ['1:Structure', '2:PSQL', '3:Search', '0:Export']
        #self.helpitems = [{'Move': 'Up/Dn'}, {'Select': 'Enter'}, {'Esc': 'Cancel'}]
        self.taskbar = TaskBar(self.parent, self.taskBarItems)
        self.taskbar.setup()


    def gettask(self):
        """
        executes the form as required to bring back the database connection string
        :return: dict of lowercase menuitems as keys, with form filled values
        """
        self.refresh()
        return self.taskbar.run()


    def refresh(self):
        """
        Refreshes in proper order
        :retur
        """
        self.taskbar.refresh()








































