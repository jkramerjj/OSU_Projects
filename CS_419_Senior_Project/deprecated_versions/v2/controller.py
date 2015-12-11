from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses


class Controller:


    def __init__(self, size, screen, terminal_row_length, terminal_column_length):
        self.size = None
        self.screen = 0
        self.terminal_row_length = 0
        self.terminal_column_length = 0


    def main(self):
        self.screen = self.createWindow()

        pause = self.screen.getch()
        curses.wrapper(self.main)

    def createWindow(self):
        self.screen = curses.initscr()



    def cleanUpListForOutput(self):
        pass


    def getScreenSize(self):
        self.terminal_row_length, self.terminal_column_length = self.screen.getmaxyx()
        return self.terminal_row_length, self.terminal_column_length


    def makeQuery(self):
        pass


    def establishConnection(self):
        pass










































