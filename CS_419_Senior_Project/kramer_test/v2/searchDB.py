


class SearchDB(object):

    """
    Used the connection object to query the database.
    :class: SearchDB
    :
    """
    def __init__(self, conn):
        self.conn = conn
        self.data = None



    ###############################################
    # Function: Used to get all the tables names in the database
    # Inputs:   self
    # Returns:  List of Tuples --> That contain query results
    # ###############################################
    def tableList(self):
        cursor = self.conn.connection.cursor()
        cursor.execute("select relname from pg_class where relkind='r' and relname !~ '^(pg_|sql_)';")
        self.data = cursor.fetchall()
        self.cleanUpListForOutput()
        #return self.data

    ###############################################
    # Function: Cleans up the values from a query into a printable list format
    # Inputs:   self
    # Returns:  list of same length, having (),' characters removed
    # Notes:    Might be best to pass in these characters for removal
    ###############################################
    def cleanUpListForOutput(self):
        newlist = []
        for i in self.data:
            newlist.append(str(i).translate(None, '(),\''))
        self.data = newlist




















