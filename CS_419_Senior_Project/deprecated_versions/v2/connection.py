from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses


class Connection:
    def __init__(self, **kwargs):
        self.connection = None
        self.database = None
        self.password = None
        self.user = None
        self.host = None
        self.port = None

        # do dynamic variable assigning
        for key, value in kwargs.iteritems():
            setattr(self, key, value)

    def connectToDB(self):


        self.connection = psycopg2.connect(database="josephkramer", user="josephkramer",
                             host="127.0.0.1", port="5432")
        # conn = psycopg2.connect(database="chinook", user="ubuntu", password="cs419", \
        #                         host="127.0.0.1", port="5432")

        # conn = psycopg2.connect(database="chinook", user="ubuntu", password="cs419", \
        #                         host="127.0.0.1", port="5432")


        #self.connection = psycopg2.connect(database=self.database, user=self.user, password=self.password, host=self.host, port=self.port)
        # self.connection = psycopg2.connect(database="chinook", user="kevin", password="chinook")
        #                         host="127.0.0.1", port="5432")


        # dbName = getKeyboardInput(stdscr, "Enter database name")
        # dbUserName = getKeyboardInput(stdscr, "Enter user name")
        # dbPassword = getKeyboardInput(stdscr, "Enter password")
        # dbHost = getKeyboardInput(stdscr, "Enter the host: i.e. 127.0.0.1")
        # dbPortNumber = getKeyboardInput(stdscr, "Enter port number: i.e. 5432")

        # 	try:
        # 		# conn = psycopg2.connect(database=dbName, user= dbUserName,
        # 		#                 password=dbPassword, host=dbHost, port=dbPortNumber)

        # 		#conn = psycopg2.connect(database="chinook", user="kevin", password="chinook")

        # 	except UnboundLocalError:
        # 		stdscr.addstr(5, 2,"UnboundLocalError --> Please verify your terminals internet connection. ")
        # 		stdscr.addstr(6, 2,"Press any key... ")
        # 		stdscr.getch()
        # 		return None
        # 	except psycopg2.OperationalError:
        # 		stdscr.addstr(5, 2,"OperationalError --> Please verify host address is all integers. ")
        # 		stdscr.addstr(6, 2,"Press any key... ")
        # 		stdscr.getch()
        # 		return None
        # 	except NameError:
        # 		stdscr.addstr(5, 2,"Name Error --> Please verify proper ASCII keyboard is used")
        # 		stdscr.addstr(6, 2,"Press any key... ")
        # 		stdscr.getch()
        # 		return None
        # 	except ValueError:
        # 		stdscr.addstr(5, 2,"Value Error --> Please use integers for port numbers. ")
        # 		stdscr.addstr(6, 2,"Press any key... ")
        # 		stdscr.getch()
        # 		return None
        #
        #
        # x = "PAUSE"

    def closeConnection(self):
        self.connection.close()
        self.connection = None
