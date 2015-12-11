from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses
from windows import Windows


class DisplayProcess(object):
    def __init__(self):
        self.max_row = None
        self.max_col = None
        self.row_num = None
        self.pages = None
        self.postition = None
        self.page = None
        self.retval = None

        self.highlightText = curses.color_pair(1)
        self.normalText = curses.A_NORMAL

        self.highlighted_text_string = None
        self.highlighted_text_position = None


    ###############################################
    # Function: Used to print the initial list data to the scren
    # Inputs:   stdscr, box, list, row_num, max_row, position, displayHeader
    # Returns   i -> The for loop counter.
    ###############################################
    def displayInitialList(self, stdscr, box, list, displayHeader):
        max_row, max_col = stdscr.getmaxyx()
        self.max_row = max_row
        self.max_col = max_col
        self.max_row -= 4
        self.max_col -= 4
        self.row_num = len(list)
        self.pages = int(ceil(self.row_num / self.max_row))
        self.position = 1
        self.page = 1
        self.i = None

        # Used to display the initial list (query) results
        for i in range(1, self.max_row + 1):
            box.addstr(1, 1, displayHeader, self.normalText)
            if self.row_num == 0:
                box.addstr(2 + 1, 1, "Results returned empty", self.highlightText)
            else:
                if (i == self.position):
                    global highlighted_text_string
                    highlighted_text_string = str(list[i - 1]).translate(None, '()')
                    box.addstr(i + 1, 2, str(list[i - 1]).translate(None, '()'), self.highlightText)
                else:
                    box.addstr(i + 1, 2, str(list[i - 1]).translate(None, '()'), self.normalText)
                if i == self.row_num:
                    break
        self.i = i






    ###############################################
    # Function: Used to display the arrow movement, copy the highlighted text into a global var -->highlighted_text_string
    # Inputs:   stdscr, list, max_row, page, box, position, displayHeader, row_num
    # Returns:  i
    # Notes:    This could be used a header when displaying query results.
    ###############################################
    def displayListAfterArrowSelection(self, box, stdscr, list, displayHeader):
        for i in range(1 + ( self.max_row * ( self.page - 1 ) ), self.max_row + 1 + ( self.max_row * ( self.page - 1 ) )):
            box.addstr(2, 2, displayHeader, self.normalText)
            if self.row_num == 0:
                box.addstr(2, 2, "There aren't strings", self.highlightText)
            else:
                if ( i + ( self.max_row * ( self.page - 1 ) ) == self.position + ( self.max_row * ( self.page - 1 ) ) ):
                    # #global highlighted_text_position
                    self.highlighted_text_position = (i + ( self.max_row * ( self.page - 1 )))
                    # #global highlighted_text_string
                    self.highlighted_text_string = str(list[i - 1]).translate(None, '()')
                    #self.retval = str(list[i - 1]).translate(None, '()')
                    box.addstr((i + 2) - ( self.max_row * ( self.page - 1 ) ), 3, str(list[i - 1]).translate(None, '()'),
                               self.highlightText)
                else:
                    box.addstr((i + 2) - ( self.max_row * ( self.page - 1 ) ), 3, str(list[i - 1]).translate(None, '()'),
                               self.normalText)
                if i == self.row_num:
                    break
        self.i = i





    ###############################################
    # Function: Used to process up,down,left,right from the user
    # Inputs:   stdscr, x, page, position, pages, row_num, max_row, i
    # Returns:  x, position, page
    ###############################################
    def processKeyboardArrowInputs(self, stdscr, x,):
        if x == curses.KEY_DOWN:
            if self.page == 1:
                if self.position < self.i:
                    self.position = self.position + 1
                else:
                    if self.pages > 1:
                        self.page = self.page + 1
                        self.position = 1 + ( self.max_row * ( self.page - 1 ) )
            elif self.page == self.pages:
                if self.position < self.row_num:
                    self.position = self.position + 1
            else:
                if self.position < self.max_row + ( self.max_row * ( self.page - 1 ) ):
                    self.position = self.position + 1
                else:
                    self.page = self.page + 1
                    self.position = 1 + ( self.max_row * ( self.page - 1 ) )
        if x == curses.KEY_UP:
            if self.page == 1:
                if self.position > 1:
                    self.position = self.position - 1
            else:
                if self.position > ( 1 + ( self.max_row * ( self.page - 1 ) ) ):
                    self.position = self.position - 1
                else:
                    self.page = self.page - 1
                    self.position = self.max_row + ( self.max_row * ( self.page - 1 ) )
        if x == curses.KEY_LEFT:
            if self.page > 1:
                self.page = self.page - 1
                self.position = 1 + ( self.max_row * ( self.page - 1 ) )

        if x == curses.KEY_RIGHT:
            if self.page < self.pages:
                self.page = self.page + 1
                self.position = ( 1 + ( self.max_row * ( self.page - 1 ) ) )




