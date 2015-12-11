import psycopg2     ##Used to connect to PostgresSQL
import sys
import pprint

def main():
   
    #Used as a connection string
    connection_string = "host='localhost' dbname='chinook' user='postgres' password='cs419'"
    
    #Print connection string to screen
    print "Connected to database --> %s" % (connection_string)
    
    #Used to create the connection
    connection = psycopg2.connect(connection_string)
    
    #Used to return a cursor object, that will be used to to perform queries
    cursor = connection.cursor()
    if cursor == True:
        print "Cursor is connected"
    else:
        print "Issue connecting to cursor"
        
    # Used for queries
    cursor.exectue("SELECT * FROM Artist")
    
    records = cursor.fetchall()
    
        
    
   
   
if __name__ == "__main__":
    main()
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
    