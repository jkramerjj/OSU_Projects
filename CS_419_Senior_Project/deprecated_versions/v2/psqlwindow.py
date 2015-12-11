import curses
from curses import textpad
from curses import ascii
from windows import Windows


class PsqlWindow(Windows):
    """
    Represents the PsqlWindow action of an open-ended PSQL query
    :class: PsqlWindow
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
        self.menuitems = ['Edit', 'Submit']
        self.actionitems = [self.edit, self.submit]
        self.fmap = {}
        for idx, item in enumerate(self.actionitems):
            self.fmap[idx] = item
        self.helpitems = [{'Move': 'Up/Dn'}, {'Select': 'Enter'}, {'Esc': 'Back'}]
        self.description = "Run PSQL query/queries on database"
        self.parentH, self.parentW = self.parent.getmaxyx()
        self.parentpsqlMargin = 2
        self.padwinLines = 10
        self.padwinCols = 6
        self.padwinY = 4
        self.curIdx = 0
        self.parentpsql = None
        self.psqlpadwin = None
        self.psqlpad = None
        self.lastcmd = None
        self.menuitemwins = []
        self.createPsqlPad()
        self.query = None

    def createPsqlPad(self):
        self.parentpsql = curses.newwin(self.parentH-self.parentpsqlMargin, self.parentW-self.parentpsqlMargin, 1, 1)
        self.psqlpadwin = self.parentpsql.derwin(self.padwinLines, self.parentW-self.padwinCols, self.padwinY, self.parentpsqlMargin)
        self.psqlpad = curses.textpad.Textbox(self.psqlpadwin)
        # create the menu items
        parentH, parentW = self.parentpsql.getmaxyx()
        startcol = int((parentW - sum((len(s) for s in self.menuitems)))/2) - int((self.padwinCols + 2) / 2)
        for item in self.menuitems:
            win = self.parentpsql.derwin(2, len(item)+ 2, parentH - 6, startcol)
            win.addstr(0,0, item)
            self.menuitemwins.append(win)
            startcol += len(item) + self.padwinCols + 2
        # add the help text
        helpstring = ""
        for i in self.helpitems:
            for key, value in i.iteritems():
                helpstring += '{}:{} '.format(key, value)
        self.parentpsql.addstr(parentH - 2, int((parentW - len(helpstring))/2), helpstring)


    def run(self):
        self.refresh()
        arg = -1
        while arg != 27:
            arg = self.menuselect()
            if arg == 1: # ugly case for Submit
                return self.query
            if arg == 27:
                break
            else:
                self.fmap[arg]()
        return None

    def submit(self):
        pass

    def edit(self):
        self.psqlpadwin.refresh()
        curses.curs_set(1)
        self.query = self.psqlpad.edit(self.validator).strip()
        curses.curs_set(0)

    def menuselect(self):
        arg = 0
        # don't show input
        curses.noecho()
        # enable curses keypad processing
        self.parentpsql.keypad(1)
        # place the selected item on first Menu item
        while arg != 27:
            self.menuitemwins[self.curIdx].bkgd(curses.A_BOLD)
            self.menuitemwins[self.curIdx].refresh()
            arg = self.parentpsql.getch()

            if arg == curses.KEY_RIGHT:
                self.menuitemwins[self.curIdx].bkgd(curses.A_NORMAL)
                self.menuitemwins[self.curIdx].refresh()
                if self.curIdx == len(self.menuitemwins) - 1:
                    self.curIdx = 0
                else:
                    self.curIdx += 1
            if arg == curses.KEY_LEFT:
                self.menuitemwins[self.curIdx].bkgd(curses.A_NORMAL)
                self.menuitemwins[self.curIdx].refresh()
                if self.curIdx == 0:
                    self.curIdx = len(self.menuitemwins) - 1
                else:
                    self.curIdx -= 1
            if arg == ord('\n'):
                return self.curIdx
        return arg



    def refresh(self):
        self.parentpsql.box()
        self.populateTitle()
        for item in self.menuitemwins:
            item.refresh()
        self.parentpsql.refresh()
        self.psqlpadwin.bkgd(curses.A_STANDOUT)
        self.psqlpadwin.refresh()

    def validator(self, key):
        if key == ascii.ESC:
            key = ascii.ascii(7)
        return key


    def populateTitle(self):
        self.parentpsql.addstr(self.parentpsqlMargin + 1, self.parentpsqlMargin, self.description)
