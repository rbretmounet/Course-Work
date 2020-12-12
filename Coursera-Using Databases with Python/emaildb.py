import sqlite3

conn = sqlite3.connect('emaildb.sqlite')
cur = conn.cursor()

cur.execute('DROP TABLE IF EXISTS Counts')

cur.execute('''
CREATE TABLE Counts (email TEXT, count INTEGER)''')

fname = input('Enter file name: ')
if (len(fname) < 1): fname = 'mbox.txt'
fh = open(fname)
for line in fh:
    if not line.startswith('From: '): continue
    pieces = line.split()
    email = pieces[1]
    cur.execute('SELECT count FROM Counts WHERE email = ? ', (email,))
    row = cur.fetchone()
    if row is None:
        cur.execute('''INSERT INTO Counts (email, count)
                VALUES (?, 1)''', (email,))
    else:
        cur.execute('UPDATE Counts SET count = count + 1 WHERE email = ?',
                    (email,))
    conn.commit()

# https://www.sqlite.org/lang_select.html
sqlstr = 'SELECT * FROM Counts'

list = []
for row in cur.execute(sqlstr):
    list.append(row[0])

orgs = {}
for size in list:
    pieces = size.split('@')
    argument = '%' + pieces[1]
    org = 'SELECT SUM(count) FROM Counts WHERE email LIKE "%s"' % (argument)
    for item in cur.execute(org):
        orgs.__setitem__(pieces[1],item[0])

dropTableStatement = "DROP TABLE Counts"
cur.execute(dropTableStatement)

cur.execute('''
CREATE TABLE Counts (org TEXT, count INTEGER)''')

sorted_dict = {}
sorted_keys = sorted(orgs, key=orgs.get,reverse=True)
for content in sorted_keys:
    sorted_dict[content] = orgs[content]

for key, value in sorted_dict.items():
    cur.execute('''INSERT INTO Counts (org, count)
            VALUES (?, ?)''', (key,value))
    conn.commit()

cur.close()
