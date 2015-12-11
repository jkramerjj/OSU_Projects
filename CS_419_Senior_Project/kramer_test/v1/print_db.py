import csv
import curses
from os import system
import sys
import psycopg2
import locale

conn = psycopg2.connect(database="chinook", user="ubuntu", 
                        password="cs419", host="127.0.0.1", port="5432")
if conn:
    print "conencted"
    

                        
cur = conn.cursor()
cur.execute("SELECT * FROM \"Album\";")
rows = cur.fetchall()
print rows[305]

number_list = []
for i in range(0, len(rows)-1):
    number_list.append(i)

print "len(rows) == " + str(len(rows))
for i, row in enumerate(rows):
     j = number_list[i-1]
            


# parser = csv.reader(rows[0])
# print "parser == " + str(parser)

# for fields in parser:
#     for i,f in enumerate(fields):
#         print i,f



# holder =[]
# for i,row in enumerate(rows):
#     #print row[1]
#     holder.append(row[1])
# print min(holder)
   
    
    

   
    