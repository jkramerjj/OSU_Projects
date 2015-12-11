from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses
from windows import Windows


class MasterWindow(Windows):
    def __init__(self, **kwargs):
        """
        Allows variable length setting of any class attrs
        :param kwargs: arguments for class, in form of attr=value, attr2=value2, etc.
        :return:
        """
        # call super class init first
        Windows.__init__(self, **kwargs)
        # do dynamic variable assigning
        for key, value in kwargs.iteritems():
            setattr(self, key, value)
        self.createMasterWindow()

    def createMasterWindow(self):
        """
        Creates the master window instance using curses.initscr()
        :return:
        """
        self.stdscr = curses.initscr()
        curses.start_color()
        # curses.init_color(1,1,1,1)
        self.highlighttext = curses.color_pair(1)
        self.normaltext = curses.A_NORMAL
        curses.cbreak()
        curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_CYAN)
        curses.curs_set(0)
        self.stdscr.keypad(1)
        self.stdscr.clear()
        self.stdscr.border(0)
