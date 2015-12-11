import curses
from curses import textpad
from curses import ascii


class Form(object):
    """
    Represents an input widget that requires textual input from the user in what looks like an HTML 'form' type input
    :class: Form
    """
    def __init__(self, parent, menuitems, helpitems, **kwargs):
        # set required
        self.parent = parent
        self.menuitems = menuitems
        self.helpitems = helpitems
        # set optional defaults
        self.vertoffset = 2
        self.horzoffset = 3
        self.textboxwidth = 25
        self.margin = 2
        self.highlight = 1
        curses.init_pair(self.highlight, curses.COLOR_WHITE, curses.COLOR_CYAN)  # TODO: these need to be global
        # set dynamic variables
        for key, value in kwargs.iteritems():
            setattr(self, key, value)
        # set internals
        self.menu = None
        self.entries = []
        self.curEntry = 0

        self.cols = 0
        self.lines = 0
        self.lastcmd = curses.KEY_ENTER

    def setup(self):
        """
        Performs setup of the menu's entries, determined by the menuitems list.
        First create a derwin of the parent that can hold everything = menu
        For each entry:
            Create an 'entryParent' derwin: this holds the whole entry
                Create an 'entryTextWin' derwin: this hold just the Textbox portion
                Create an 'entryTextBox' associated with the entryTextWin
        :return:
        """
        # TODO: this class probably needs to do some sanity checking for whether these contents can actually fit
        # create a window large enough to hold the menu items, as newwin
        helpstring = ""
        for i in self.helpitems:
            for key, value in i.iteritems():
                helpstring += '{}:{} '.format(key, value)
        maxhelp = len(helpstring)
        maxmenu = len(max(self.menuitems, key=len)) + self.horzoffset
        maxinput = maxmenu + self.textboxwidth
        maxtext = max(maxhelp, maxinput)
        margin = (self.margin * 2)
        self.lines = (len(self.menuitems) * self.vertoffset + margin)
        self.cols = maxtext + margin
        # window gets centered by default. TODO: make this an option
        parentH, parentW = self.parent.getmaxyx()
        y = int((parentH - self.lines) / 2)
        x = int((parentW - self.cols) / 2)
        self.menu = curses.newwin(self.lines, self.cols, y, x) #curses.newwin(nlines, ncols, begin_y, begin_x)

        # for each menu item, make a subwindow at the row location that can hold the whole width
        start = self.margin
        self.entries = []
        for idx, item in enumerate(self.menuitems):
            # create the subwin, 1 line, window size minus margins on both sides, start at vertoffset & x margin
            self.entries.append({'entryParent': self.menu.derwin(1, self.cols - margin, start, self.margin)})
            entry = self.entries[idx]
            # add the entry's text
            entry['entryParent'].addstr(item)
            # for each entry, add another derwin for the text box
            entry['entryTextWin'] = entry['entryParent'].derwin(1, self.textboxwidth, 0, maxmenu) #derwin(nlines, ncols, begin_y, begin_x)
            # put a textBox in each of the entryTextWins, keep a reference to it again
            entry['entryTextBox'] = curses.textpad.Textbox(entry['entryTextWin'])
            # bump the row counter
            start += self.vertoffset

        # place the help text
        self.menu.addstr(self.lines - self.margin, int((self.cols - maxhelp) / 2), helpstring)

    def refresh(self):
        """
        Performs the refresh of the form in the proper order. Sets TextBoxes to look like textboxes
        :return:
        """
        # refresh from bottom to top
        self.menu.box()
        self.menu.refresh()
        for i in self.entries[:-1]:
            i['entryTextWin'].bkgd(curses.A_STANDOUT)
            i['entryTextWin'].refresh()
            i['entryParent'].refresh()

    def run(self, cur=0):
        """
        Attempts to prompt user with entries for filling out necessary components of the form
        :param cur: Which entry index to begin with, default with the first
        :return: formstring with all non-empty fields available as Dict using menuitems, otherwise None
        """
        # don't show input
        curses.noecho()
        # enable curses keypad processing
        self.menu.keypad(1)
        # set the current focus index
        self.curEntry = cur
        # run an event loop looking for Up/Dn, Enter, or Esc
        while self.lastcmd != curses.KEY_CANCEL:
            # position highlight on current menu item, make bold
            entry = self.entries[self.curEntry]
            entry['entryParent'].bkgd(curses.A_BOLD)
            self.refresh()
            # go right into edit mode if this isn't the accept menu item
            if self.curEntry != len(self.entries) - 1:
                # allow editing to occur. Seems edit triggers a refresh here automatically
                curses.curs_set(1)
                entry['entryTextWin'].bkgd(curses.color_pair(self.highlight))
                entry['entryTextWin'].keypad(1)
                entry['contents'] = entry['entryTextBox'].edit(self.validator).strip()
                curses.curs_set(0)
                if self.lastcmd == curses.KEY_UP:
                    self.moveup()
                elif self.lastcmd == curses.KEY_DOWN:
                    self.movedown()
                elif self.lastcmd == curses.KEY_ENTER:
                    # jump to next entry as if KEY_DOWN
                    self.movedown()

            # if it is the accept menu item, don't do editing, just highlight and react. Have to handle separately
            else:
                while (1):
                    # have to invoke a getch here because the editing cases above depend on editing having happened
                    arg = self.menu.getch()
                    if arg == curses.KEY_UP:
                        self.lastcmd = curses.KEY_UP
                        self.moveup()
                        break
                    elif arg == curses.KEY_DOWN:
                        self.lastcmd = curses.KEY_DOWN
                        self.movedown()
                        break
                    elif arg == curses.KEY_ENTER or arg == ord('\n'):
                        # form the connection string from input fields
                        formstring = {}
                        for idx, item in enumerate(self.entries[:-1]):
                            if item.get('contents', None):
                                formstring[self.menuitems[idx].lower()] = item['contents']
                                return formstring
                            # nothing was gathered case
                            if len(formstring.items()) == 0:
                                # TODO: handle this error
                                continue
                    elif arg == ascii.ESC:
                        self.lastcmd = curses.KEY_CANCEL
                        break

        # something probably goes wrong before we ever reach here, but in case
        return None

    def movedown(self):
        """
        Modifies internal curEntry value to move "down" by 1 index, does looping & updates previous entry bkgd
        :return:
        """
        # reset the current row's highlight
        entry = self.entries[self.curEntry]
        entry['entryParent'].bkgd(curses.A_NORMAL)
        # move the cursor to the next entry
        if self.curEntry == len(self.entries) - 1:
            self.curEntry = 0
        else:
            self.curEntry += 1

    def moveup(self):
        """
        Modifies internal curEntry value to move "up" by 1 index, does looping & updates previous entry bkgd
        :return:
        """
        # reset the current row's highlight
        entry = self.entries[self.curEntry]
        entry['entryParent'].bkgd(curses.A_NORMAL)
        # move the cursor to a previous entry
        if self.curEntry == 0:
            self.curEntry = len(self.entries) - 1
        else:
            self.curEntry -= 1

    def validator(self, key):
        """
        Serves as the means to accept input from the user that they are done with their textbox entry by accepting
        key input of KEY_ENTER/KEY_DOWN/UP/ESC from the Textbox.edit() function an reinterpreting this as Ctrl+G
        which performs the command for saving and exiting editing
        :param key: input from edit box
        :return: key modified as Ctrl+G if it hits any of these cases
        """
        if key == curses.KEY_DOWN:
            key = ascii.ascii(7)
            self.lastcmd = curses.KEY_DOWN
        elif key == curses.KEY_UP:
            key = ascii.ascii(7)
            self.lastcmd = curses.KEY_UP
        elif key == curses.KEY_ENTER or key == ord('\n'):
            key = ascii.ascii(7)
            self.lastcmd = curses.KEY_ENTER
        elif key == ascii.ESC:
            key = ascii.ascii(7)
            self.lastcmd = curses.KEY_CANCEL
        return key
