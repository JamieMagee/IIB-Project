import re
import sqlite3

def init_db(cur):
    cur.execute('''CREATE TABLE foo (
        Subsampling INTEGER ,
        Transformation TEXT,
        Algorithm TEXT,
        Accuracy REAL)''')


db = sqlite3.connect(':memory:')

cur = db.cursor()
init_db(cur)
subsampling = ['1', '2', '4', '8', '16']
#subsampling = '1'
for subsample in subsampling:
    f = open(subsample + '/' + subsample + '.txt')
    lines = f.readlines()
    sampling = int(lines[3])
    for i in range(1, 13):
        method = str(re.findall('farneback|lucas\-kanade|simpleflow', lines[3*i+2])[0])
        transformation = str(re.findall('rotate|scale|skew|translate', lines[3*i+2])[0])
        accuracy = float(lines[3*i+3])
        cur.execute("INSERT into foo VALUES(?,?,?,?)", (sampling, transformation, method, accuracy))
cursor = cur.execute('SELECT Subsampling, Transformation, Algorithm, Accuracy FROM foo ORDER BY Transformation, CASE Algorithm')
for row in cursor:
    print(str(row[0]) + ' | ' + row[1] + ' | ' + row[2] + ' | ' + str(row[3]))