#!/usr/bin/env python

# conn = psycopg2.connect(database="chinook", user="ubuntu",
# password="cs419", host="127.0.0.1", port="5432")

from __future__ import division
from math import *
from curses import wrapper
from os import system
import sys, psycopg2, locale, curses



#GLOBALS
highlightText = None
normalText = None
conn = None
highlighted_text_string = None
highlighted_text_position = None
displayHeaderWithEscapeOption = "Escape [ESC] to exit. Press Up, Down, Left, Right to move."
displayHeaderWithEnterOption = "Escape [ESC] to exit. Enter [ENTER] to select.  Up, Down, Left, Right to move."


###############################################
# Function: To administer the highlevel operations
#           of the program.
###############################################
def main(stdscr):
    global highlightText
    global normalText
    stdscr = curses.initscr()
    highlightText = curses.color_pair(1)
    normalText = curses.A_NORMAL
    curses.cbreak()
    curses.start_color()
    stdscr.keypad(1)
    curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_CYAN)
    stdscr.border(0)
    curses.curs_set(0)
    global conn
    arg = 0
    while arg != ord('q'):
        colcount = 5
        #max_row = getScreenSize(stdscr)
        stdscr.clear()
        stdscr.border(0)
        stdscr.addstr(2, 2, "Please select from menu...")
        if conn is None:
            stdscr.addstr(4, 4, "1 - Log in to Database")
        else:
            stdscr.addstr(1, 2, "Connection: %s" % conn.dsn)
            stdscr.addstr(colcount, 4, "1 - Log out of Database")
            colcount += 1
            stdscr.addstr(colcount, 4, "2 - Write Query")
            colcount += 1
            stdscr.addstr(colcount, 4, "3 - Display Tables")
            colcount += 1
            stdscr.addstr(colcount, 4, "4 - Display Table Column Headers")
            colcount += 1
            stdscr.addstr(colcount, 4, "5 - Select a Table to Query All")
            colcount += 1
            stdscr.addstr(colcount, 4, "6 - Find Table to Query")
            colcount += 1
        stdscr.addstr(colcount, 4, "q - quit")
        stdscr.refresh()
        arg = stdscr.getch()

        if arg == ord('1'):
            if conn is None:
                curses.endwin()
                curses.echo()
                conn = connectDB(stdscr)
                curses.noecho()
            else:
                conn.close()
                conn = None
        elif conn is None:
            pass
        elif arg == ord('2'):
            query = getUserCreatedQuery(stdscr)
            results = searchDBUserQuery(stdscr, conn, query)
            if results != None:
                displayResultsInNewWindow(stdscr, cleanUpListForOutput(results), displayHeaderWithEscapeOption)
            else:
                arg =0
        elif arg == ord('3'):
            results = getTableList(stdscr, conn)
            displayResultsInNewWindow(stdscr, cleanUpListForOutput(results), displayHeaderWithEscapeOption)
        elif arg == ord('4'):
            results = getTableColumnNames(stdscr, conn)
            displayResultsInNewWindow(stdscr, cleanUpListForOutput(results), displayHeaderWithEscapeOption)
        elif arg == ord('5'):
            tables = getTableList(stdscr, conn)
            table = getSelectionFromList(stdscr, cleanUpListForOutput(tables), displayHeaderWithEnterOption)
            #handle the quit case from user selection
            if table == '':
                arg = 0
            else:
                results = searchDB(stdscr, conn, table)
                displayResultsInNewWindow(stdscr, results, displayHeaderWithEscapeOption)
        elif arg == ord('6'):
            chooseTableToSearch(stdscr, conn)





###############################################
# Function: Used to facility the process of allowing a user to select a
#           desired table, then column, and then disaply that information
#           Also the ability write a specific query for the table
#           Also the ability to search for one peice of data when a
#           table and column are selected.
#
# Inputs:   stdscr, conn
# Returns:
###############################################
def chooseTableToSearch(stdscr, conn):
    results = getTableList(stdscr, conn)
    table = getSelectionFromList(stdscr, cleanUpListForOutput(results), displayHeaderWithEscapeOption)


    max_row, max_col = getScreenSize(stdscr)
    max_row -= 4
    max_col -= 4
    box = curses.newwin(max_row + 2, max_col, 1, 1)
    box.box()

    #curses.echo()
    input_prompt = "You choose the table : "
    box.addstr(2,2, input_prompt)
    box.addstr(2,len(input_prompt) + 2, str(table), curses.A_STANDOUT )
    box.addstr(4,2, "Display table contents? Press[D]" )
    box.addstr(5,2, "Search table? Press[S]" )

    box.refresh()
    x = stdscr.getch()

    # IF Statement used to display user selected table content.
    if x == ord('d') or x == ord('D'):
        data = searchDB(stdscr, conn, table)
        displayResultsInNewWindow(stdscr, data, displayHeaderWithEscapeOption)

    # IF Statment used to search the Database. It will allow the user to
    # the ability to choose a column from a list of columns or
    # write their own quer for the table.
    elif x == ord('s') or x == ord('S'):
        newBox = curses.newwin(max_row + 2, max_col, 1, 1)
        newBox.box()
        input_prompt = "Now inside the table: "

        newBox.addstr(2,2, input_prompt, )
        newBox.addstr(2,len(input_prompt) + 2, str(table), curses.A_STANDOUT )
        newBox.addstr(4,2, "Choose a column? Press[C]" )
        newBox.addstr(5,2, "Write your own query? Press[W]" )
        newBox.refresh()
        x = stdscr.getch()

        # If Statement when the user decides to choose a column
        if x == ord('c') or x == ord('C'):
            data = getTableColumnNamesTableIncluded(stdscr, conn, table)
            displayResultsInNewWindow(stdscr, cleanUpListForOutput(data), displayHeaderWithEnterOption)
            if highlighted_text_string != None:
                columnName = highlighted_text_string
                newBoxx = curses.newwin(max_row + 2, max_col, 1, 1)
                newBoxx.box()
                input_prompt = "Now inside the table: "
                newBoxx.addstr(2,2, input_prompt)
                newBoxx.addstr(2,len(input_prompt) + 2, str(table), curses.A_STANDOUT )
                input_prompt = "Now inside the column: "
                newBoxx.addstr(3,2, input_prompt)
                newBoxx.addstr(3,len(input_prompt) + 2, columnName, curses.A_STANDOUT )

                newBoxx.addstr(5,2, "Display column data? Press[D]" )
                newBoxx.addstr(6,2, "Search column data? Press[S]" )
                stdscr.refresh()
                newBoxx.refresh()
                z = stdscr.getch()

                # If Statement when the user chooses to display all the data in their
                # chosen column.
                if z == 100 or z == 68: #THIS IS d and D
                    data = queryDBWithTableAndColumn(stdscr, conn, table, columnName)
                    displayResultsInNewWindow(stdscr, cleanUpListForOutput(data), displayHeaderWithEscapeOption)

                # If Statement when the user chooses to search for a specific piece of data
                # in the choose table and column.
                elif z == 115 or z == 83: ## THIS IS s and S
                    newBox = curses.newwin(max_row + 2, max_col, 1, 1)
                    newBox.box()
                    input_prompt = "Inside table: "
                    newBox.addstr(2,2, input_prompt)
                    newBox.addstr(2,len(input_prompt) + 2, str(table), curses.A_STANDOUT )
                    input_prompt = "Searching the column: "
                    newBox.addstr(3,2, input_prompt)
                    newBox.addstr(3,len(input_prompt) + 2, columnName, curses.A_STANDOUT )

                    input_prompt = "Please search item "
                    box.addstr(5, 2, input_prompt, normalText)
                    box.addstr(5, 2 + len(input_prompt), " ", curses.A_STANDOUT)
                    stdscr.refresh()
                    newBox.refresh()
                    curses.echo()
                    usersQuery = box.getstr(5, (2 + len(input_prompt) + 3), 60)
                    # if usersQuery.find(';') != True:
                    #     usersQuery = usersQuery + ';'
                    curses.noecho()
                    newQuery = "SELECT \"" + columnName + "\"" + " FROM " + "\"" + table + "\"" + " WHERE \"" + columnName + "\"" + "=" + "\'" + usersQuery + "\'"  + ";"

                    # Returns results form newQuery
                    results = searchDBUserQuery(stdscr, conn, newQuery)

                    if results != None:  #Bad logic here, it needs to be fixed. There is a better way to check if results is a good value or not
                        newBox = curses.newwin(max_row + 2, max_col, 1, 1)
                        newBox.box()
                        newBox.addstr(2,2, "Found Data")
                        newBox.addstr(4,2, columnName + " --> " + usersQuery)


                        stdscr.refresh()
                        newBox.refresh()
                        stallForNOW = stdscr.getch()  # THis only here to stall the program. Delete soon


        #THIS if statement is for WRITE YOUR OWN QUERY
        # The logic needs to be coded.
        elif x == ord('w') or x == ord('W'):
           pass


    # Reset the string
    global highlighted_text_string
    highlighted_text_string = None

    #return 4



###############################################
# Function: used to query the database when the user has selected a table and a column
#           from a list
#
# Inputs:   stdscr, conn, table, columnName
# Returns:  results
###############################################
def queryDBWithTableAndColumn(stdscr, conn, table, columnName):
    if table == '' or columnName =='':
        return None

    runMe = "SELECT \"" + columnName + "\"" + " FROM " + "\"" + table + "\"" + ";"

    stdscr.clear()
    cur = conn.cursor()
    cur.execute(runMe)
    results = cur.fetchall()
    #print str(rows)
    return results






###############################################
# Function: Use to get the dynamic size of the terminal window
#            i.e. if the terminal size changes, this will update the display
# Inputs:   stdscr
# Returns:  terminal_row_length
###############################################
def getScreenSize(stdscr):
    terminal_row_length, terminal_column_length = stdscr.getmaxyx()
    return terminal_row_length, terminal_column_length


###############################################
# Function: Cleans up the values from a query into a printable list format
# Inputs:   list
# Returns:  list of same length, having (),' characters removed
# Notes:    Might be best to pass in these characters for removal
###############################################
def cleanUpListForOutput(list):
    newlist = []
    for i in list:
        newlist.append(str(i).translate(None, '(),\''))
    return newlist


###############################################
# Function: Used to process up,down,left,right from the user
# Inputs:   stdscr, x, page, position, pages, row_num, max_row, i
# Returns:  x, position, page
###############################################
def processKeyboardArrowInputs(stdscr, x, page, position, pages, row_num, max_row, i):
    if x == curses.KEY_DOWN:
        if page == 1:
            if position < i:
                position = position + 1
            else:
                if pages > 1:
                    page = page + 1
                    position = 1 + ( max_row * ( page - 1 ) )
        elif page == pages:
            if position < row_num:
                position = position + 1
        else:
            if position < max_row + ( max_row * ( page - 1 ) ):
                position = position + 1
            else:
                page = page + 1
                position = 1 + ( max_row * ( page - 1 ) )
    if x == curses.KEY_UP:
        if page == 1:
            if position > 1:
                position = position - 1
        else:
            if position > ( 1 + ( max_row * ( page - 1 ) ) ):
                position = position - 1
            else:
                page = page - 1
                position = max_row + ( max_row * ( page - 1 ) )
    if x == curses.KEY_LEFT:
        if page > 1:
            page = page - 1
            position = 1 + ( max_row * ( page - 1 ) )

    if x == curses.KEY_RIGHT:
        if page < pages:
            page = page + 1
            position = ( 1 + ( max_row * ( page - 1 ) ) )

    return x, position, page


###############################################
# Function: Display a list of options and gather input from user
# Inputs:   stdscr, list
# Returns:  Input text string from user if it is in the listing, '' represents quit
# Notes:    Would be nicer to utilize either an up/down cursor selection or input by index
# kramerj --> Thanks for writing this function. I ended up finding a subtle bug based on the
#               terminals screen size. If the screen size is smaller then the rows that will be
#               printed, then addstr() errors out. I had this issue b4 and that's when I decided to
#               to use: max_row, max_col = getScreenSize(stdscr) b4 printing to screen.
###############################################
def getSelectionFromList(stdscr, list, displayHeader):
    if not stdscr:
        return ''

    max_row, max_col = getScreenSize(stdscr)
    max_row -= 4
    max_col -= 4
    box = curses.newwin(max_row + 2, max_col, 1, 1)
    box.box()
    row_num = len(list)
    pages = int(ceil(row_num / max_row))
    position = 1
    page = 1
    curses.echo()
    retval = ''
    #x = 4
    #y = 4
    inputPrompt = 'Input table name: '


    #Used to display the initial list
    i = displayInitialList(stdscr, box, list, row_num, max_row, position, displayHeader)

    box.addstr(i + 2, 2, inputPrompt)
    stdscr.refresh()
    box.refresh()

    ## USED TO CAPTURE USER INPUT
    ## Up, down, left, right, enter
    curses.noecho()
    x = stdscr.getch()

    while x != 27:  #27 == esc in ASCII

        #Used to process user entered arrow options
        x, position, page = processKeyboardArrowInputs(stdscr, x, page, position, pages, row_num, max_row, i)

        #If user hit enter, then return the highlighted text that enter was pressed on
        if x == ord("\n"):
            retval = highlighted_text_string
            curses.noecho()
            return retval

        if x == ord('w') or x == ord('W'):  # Write was selected
            #get user input, if it matches item in list, return, q/quit exits, or try again w/error
            while True:
                box.addstr(i + 2, 2 + len(inputPrompt), " ", curses.A_STANDOUT)
                box.refresh()
                curses.echo()
                input = box.getstr(i + 2, (2 + len(inputPrompt) + 2), 60)
                if input.lower() == 'q' or input.lower() == 'quit':
                    return retval
                elif input in list:
                    retval = list[list.index(input)]
                    curses.noecho()
                    return retval
                else:
                    #to clean up input from user, move cursor back to start, erase line, paint border
                    box.addstr(i + 2, 2,
                               inputPrompt + "                                          ")  # used to clear out previous entry
                    box.addstr(i + 2, 2 + len(inputPrompt), " ", curses.A_STANDOUT)
                    box.clrtoeol()
                    box.border(0)
                    box.addstr(i + 3, 2, "Invalid input. Please try again.")
        box.erase()
        stdscr.border(0)
        box.border(0)

        ## USED TO REPRINT AFTER USER'S KEYBOARD INPUT
        #displayHeader = 'Press [w] to write selection or Q to quit. '
        i = displayListAfterArrowSelection(stdscr, list, max_row, page, box, position, displayHeader, row_num)

        #Used to display input prompt the the user.
        if i == row_num and i < max_row:
            box.addstr(i + 2, 2,
                       inputPrompt + "                                          ")  # used to clear out previous entry
            box.move(i + 3, (2 + len(inputPrompt) + 1))

        stdscr.refresh()
        box.refresh()
        x = stdscr.getch()
    curses.noecho()
    return retval


###############################################
# Function: Get the users typed query.
# Inputs:   stdscr
# Returns:  userQuery
###############################################
def getUserCreatedQuery(stdscr):
    ## Used to create window size
    max_row, max_col = getScreenSize(stdscr)
    max_row -= 4
    max_col -= 4
    box = curses.newwin(max_row + 2, max_col, 1, 1)
    box.box()
    inputPrompt = "Please Enter Query here:"

    box.addstr(1, 1, "Escape [ESC] to exit and [ENTER] when done", normalText)
    box.addstr(3, 1, inputPrompt, normalText)
    box.addstr(3, 2 + len(inputPrompt), " ", curses.A_STANDOUT)

    box.refresh()
    curses.echo()
    usersQuery = box.getstr(3, (2 + len(inputPrompt) + 3), 60)
    if usersQuery == '':
        curses.noecho()
        return None
    elif usersQuery.find(';') != True:
        curses.noecho()
        usersQuery = usersQuery + ';'
        return usersQuery

    curses.noecho()
    return usersQuery


###############################################
# Function: Used to print the initial list data to the scren
# Inputs:   stdscr, box, list, row_num, max_row, position, displayHeader
# Returns   i -> The for loop counter.
###############################################
def displayInitialList(stdscr, box, list, row_num, max_row, position, displayHeader):
    # Used to display the initial list (query) results
    for i in range(1, max_row + 1):
        box.addstr(1, 1, displayHeader, normalText)
        if row_num == 0:
            box.addstr(2 + 1, 1, "Results returned empty", highlightText)
        else:
            if (i == position):
                global highlighted_text_string
                highlighted_text_string = str(list[i - 1]).translate(None, '()')
                box.addstr(i + 1, 2, str(list[i - 1]).translate(None, '()'), highlightText)
            else:
                box.addstr(i + 1, 2, str(list[i - 1]).translate(None, '()'), normalText)
            if i == row_num:
                break
    return i


###############################################
# Function: Used to display the arrow movement, copy the highlighted text into a global var -->highlighted_text_string
# Inputs:   stdscr, list, max_row, page, box, position, displayHeader, row_num
# Returns:  i
# Notes:    This could be used a header when displaying query results.
###############################################
def displayListAfterArrowSelection(stdscr, list, max_row, page, box, position, displayHeader, row_num):
    for i in range(1 + ( max_row * ( page - 1 ) ), max_row + 1 + ( max_row * ( page - 1 ) )):
        box.addstr(1, 1, displayHeader, normalText)
        if row_num == 0:
            box.addstr(1, 1, "There aren't strings", highlightText)
        else:
            if ( i + ( max_row * ( page - 1 ) ) == position + ( max_row * ( page - 1 ) ) ):
                global highlighted_text_position
                highlighted_text_position = (i + ( max_row * ( page - 1 )))
                global highlighted_text_string
                highlighted_text_string = str(list[i - 1]).translate(None, '()')
                box.addstr((i + 1) - ( max_row * ( page - 1 ) ), 2, str(list[i - 1]).translate(None, '()'),
                           highlightText)
            else:
                box.addstr((i + 1) - ( max_row * ( page - 1 ) ), 2, str(list[i - 1]).translate(None, '()'),
                           normalText)
            if i == row_num:
                break
    return i


###############################################
# Function: To print in a seperate window the results from the search.
# Inputs:   rows --> All the data returned from a SearchDB function
# Notes     Possible refactor of function once display is finalized.
###############################################
def displayResultsInNewWindow(stdscr, list, displayHeader):
    max_row, max_col = getScreenSize(stdscr)
    max_row -= 4
    max_col -= 4
    box = curses.newwin(max_row + 2, max_col, 1, 1)
    box.box()
    row_num = len(list)
    pages = int(ceil(row_num / max_row))
    position = 1
    page = 1


    i = displayInitialList(stdscr, box, list, row_num, max_row, position, displayHeader)

    stdscr.refresh()
    box.refresh()



    ## USED TO CAPTURE USER INPUT
    ## Up, down, left, right, enter
    x = stdscr.getch()
    box.keypad(1) #This allows the user to press ESC at anytime

    while x != 27:  #27 == esc in ASCII
        #Used to process user entered arrow options
        x, position, page = processKeyboardArrowInputs(stdscr, x, page, position, pages, row_num, max_row, i)
        if x == ord("\n") and row_num != 0:
            stdscr.erase()
            stdscr.border(0)
            break

        box.erase()
        stdscr.border(0)
        box.border(0)

        ## USED TO REPRINT AFTER USER'S KEYBOARD INPUT
        displayListAfterArrowSelection(stdscr, list, max_row, page, box, position, displayHeader, row_num)

        stdscr.refresh()
        box.refresh()
        x = stdscr.getch()


###############################################
# Function: Used to get all of the column names form a table in the database
# Inputs:   stdscr, conn
# Returns:  List of Tuples --> That contain query results
# Notes:    This could be used a header when displaying query results.
###############################################
def getTableColumnNames(stdscr, conn):
    cursor = conn.cursor()
    cursor.execute("SELECT column_name from information_schema.columns where table_name=\'Artist\';")
    data = cursor.fetchall()
    return data

def getTableColumnNamesTableIncluded(stdscr, conn, table):
    cursor = conn.cursor()
    #cursor.execute('SELECT * FROM \"{}\";'.format(table))
    cursor.execute('SELECT column_name from information_schema.columns where table_name=\'{}\';'.format(table))
    data = cursor.fetchall()
    return data



###############################################
# Function: Used to get all the tables names in the database
# Inputs:   stdscr, conn
# Returns:  List of Tuples --> That contain query results
###############################################
def getTableList(stdscr, conn):
    cursor = conn.cursor()
    cursor.execute("select relname from pg_class where relkind='r' and relname !~ '^(pg_|sql_)';")
    data = cursor.fetchall()
    return data


###############################################
# Function: To receive input form the users keyboard #
###############################################
def getKeyboardInput(stdscr, prompt):
    stdscr.clear()
    stdscr.border(0)
    stdscr.addstr(2, 2, prompt)
    stdscr.refresh()
    input = stdscr.getstr(3, 10, 60)
    return input


###############################################
# Function: To search the database
# Input:    conn --> an active conenction to the DB
# Updates needed: Variables for hard coded data
#
###############################################
def searchDB(stdscr, conn, table='Artist'):
    if table == '':
        return None
    stdscr.clear()
    cur = conn.cursor()
    cur.execute('SELECT * FROM \"{}\";'.format(table))
    rows = cur.fetchall()
    #print str(rows)
    return rows


###############################################
# Function: To use a user created query to search the database
# Input:    conn --> an active conenction to the DB
#           query --> User designed query
#
###############################################
def searchDBUserQuery(stdscr, conn, query):
    if query == '' or query == None:
        return None
    stdscr.clear()
    cur = conn.cursor()
    cur.execute(query)
    data = cur.fetchall()
    return data


###############################################
# Function: To connect the user to the database #
###############################################
def connectDB(stdscr):
    stdscr.clear()

    conn = psycopg2.connect(database="josephkramer", user="josephkramer",
                            host="127.0.0.1", port="5432")

    # conn = psycopg2.connect(database="chinook", user="ubuntu", password="cs419", \
    #                         host="127.0.0.1", port="5432")

    # conn = psycopg2.connect(database="chinook", user="ubuntu", password="cs419", \
    #                         host="127.0.0.1", port="5432")


    # conn = psycopg2.connect(database="chinook", user="kevin", password="chinook", \
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

    stdscr.addstr(6, 2, "Connected Successfully!")
    stdscr.addstr(7, 2, "Press any key to continue...")
    stdscr.getch()

    # Used to return the conenction so other functions can manipulate the database
    return conn


curses.wrapper(main)