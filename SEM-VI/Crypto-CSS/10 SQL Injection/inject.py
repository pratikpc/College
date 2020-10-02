import sqlite3

def Create(c):
    return c.execute('''CREATE TABLE auth
                (username text PRIMARY KEY NOT NULL, pass text PRIMARY KEY NOT NULL)''')

def Insert(c, username, password):
    # Use Prepare Statements Here
    # This is the Proper way such operations must be done
    return c.execute('''INSERT OR REPLACE INTO auth(username, pass) values(?,?)''', username, password)

# Create Database in Memory
with sqlite3.connect(':memory:') as conn:

    c = conn.cursor()

    

    # Save (commit) the changes
    conn.commit()
