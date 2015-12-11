from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses


class Windows:
    def __init__(self):
        self.stdscr = None #may not need this...
        self.hightlightText = None
        self.normalText = None
        #self.box = None
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


    def createMasterWindow(self, stdscr):
        self.stdscr = curses.initscr()
        curses.start_color()
        #curses.init_color(1,1,1,1)
        self.hightlightText = curses.color_pair(1)
        self.normalText = curses.A_NORMAL
        curses.cbreak()
        curses.start_color()
        self.stdscr.keypad(1)
        curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_CYAN)
        self.stdscr.border(0)
        curses.curs_set(0)


    def createNewBox(self, stdscr):
        box = curses.newwin(3, 85, 1, 1)
        box.border(0)
        box.addstr(1,70, "1 70" )
        box.refresh()


    def createNewBox2(self, stdscr):
        box = curses.newwin(6, 35, 4, 4)
        box.border(0)
        box.addstr(4,30, "4 30" )
        box.refresh()

    def clear(self, stdscr):
        self.stdscr.clear()

    def boarder(self, stdscr, size):
        self.stdscr.border(size)

    def changeColor(self, stdscr):
        #curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_GREEN)
        #stdscr.bkgd('',curses.color_pair(1))
        #stdscr.attrset(2)
        #stdscr.attron(curses.COLOR_GREEN)
        #stdscr.bkgdset('c',  curses.COLOR_GREEN)
        pass
        #curses.wbkgd(stdscr, '', curses.color_pair(1))
       # stdscr.attron(curses.color_pair())



































