from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses
from box import Box


class Windows(object):
    # class member variables we would always expect to have
    norm = curses.A_NORMAL
    bold = curses.A_BOLD
    dim = curses.A_DIM
    colorlist = (("red", curses.COLOR_RED),
                 ("green", curses.COLOR_GREEN),
                 ("yellow", curses.COLOR_YELLOW),
                 ("blue", curses.COLOR_BLUE),
                 ("cyan", curses.COLOR_CYAN),
                 ("magenta", curses.COLOR_MAGENTA),
                 ("black", curses.COLOR_BLACK),
                 ("white", curses.COLOR_WHITE))

    def __init__(self, **kwargs):
        """
        Allows variable length setting of any class attrs
        :param kwargs: arguments for class, in form of attr=value, attr2=value2, etc.
        :return:
        """
        # set default vars
        self.stdscr = None
        self.highlighttext = None
        self.normaltext = None
        self.boxes = {}

        # allow for setting variable vars, will overwrite above if provided
        for key, value in kwargs.iteritems():
            setattr(self, key, value)

    def createnewbox(self, parent, name, height, width, begin_y, begin_x, border=None, addstr=None):
        """
        Creates a derwin 'Box' and adds by name to this window's box dictionary
        :param parent: parent window, box is created as derwin
        :param name: name to associate with the box
        :param height: height of the box, relative to parent
        :param width: width of the box, relative to parent
        :param begin_y: start y relative to parent
        :param begin_x: start x relative to parent
        :param border: border option
        :param addstr: add str option
        :return:
        """
        boxdict = {'name': name, 'height': height,
                   'width': width, 'begin_y': begin_y,
                   'begin_x': begin_x, 'border': border,
                   'addstr': addstr}


        box = Box(parent, **boxdict)
        self.boxes[box.name] = box

    def clear(self):
        """
        Clears the stdscr
        :return:
        """
        if self.stdscr:
            self.stdscr.clear()

    def border(self, size):
        if self.stdscr:
            self.stdscr.border(size)

    def changeColor(self, stdscr):
        # curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_GREEN)
        # stdscr.bkgd('',curses.color_pair(1))
        # stdscr.attrset(2)
        # stdscr.attron(curses.COLOR_GREEN)
        # stdscr.bkgdset('c',  curses.COLOR_GREEN)
        pass
        # curses.wbkgd(stdscr, '', curses.color_pair(1))
        # stdscr.attron(curses.color_pair())

    def refresh(self):
        """
        refresh this window in the proper order
        :return:
        """
        if self.stdscr:
            self.stdscr.refresh()
