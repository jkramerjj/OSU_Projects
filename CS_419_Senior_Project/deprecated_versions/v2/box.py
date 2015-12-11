from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses
import uuid


class Box(object):
    def __init__(self, parent, **kwargs):
        """
        Creates a box from variable number of args
        :param kwargs:
        :return:
        """
        # set default vars
        self.name = uuid.uuid4()
        self.border = None
        self.height = 10
        self.width = 10
        self.begin_y = 0
        self.begin_x = 0
        self.box = None
        self.parent = parent

        # allow for setting variable vars, will overwrite above if provided
        for key, value in kwargs.iteritems():
            setattr(self, key, value)
        # create the box
        self.box = parent.derwin(self.height, self.width, self.begin_y, self.begin_x)
        if self.border is not None:
            self.setBorder(self.border)
        if self.addstr:
            self.box.addstr(self.addstr['y'], self.addstr['x'], self.addstr['val'])
        self.box.refresh()

    def refresh(self):
        self.setBorder(self.border)
        self.box.refresh()

    def clear(self):
        self.box.clear()

    def setBorder(self, border):
        if border is not None:
            if isinstance(self.border, list):
                self.box.border(*self.border)
            else:
                self.box.border(self.border)

    def setStr(self, y, x, val):
        self.box.addstr(y, x, val)

    def getmaxyx(self):
        return self.box.getmaxyx()

    def keypad(self, val):
        self.box.keypad(val)
