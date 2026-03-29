import eventlet
eventlet.monkey_patch()

from flask import Flask, render_template, request, redirect, session
from flask_socketio import SocketIO
import socket
import struct
import time
import sqlite3

app = Flask(__name__)
app.secret_key = "secret123"   # 🔐 added for session
socketio = SocketIO(app, async_mode='eventlet')

# DB setup
conn = sqlite3.connect('latency.db', check_same_thread=False)
cursor = conn.cursor()

# existing table (unchanged)
cursor.execute("""
CREATE TABLE IF NOT EXISTS latency_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    latency REAL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")

# 🔐 NEW: users table
cursor.execute("""
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password TEXT
)
""")

# 🔐 insert default user
cursor.execute("INSERT OR IGNORE INTO users VALUES (?, ?)", ("admin", "1234"))

conn.commit()


def tcp_listener():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", 8080))

    while True:
        try:
            send_time = time.time()
            s.send(struct.pack('d', send_time))

            data = s.recv(8)
            recv_time = time.time()

            latency = (recv_time - send_time) * 1000

            print("Latency:", latency)

            # store in DB
            cursor.execute("INSERT INTO latency_logs (latency) VALUES (?)", (latency,))
            conn.commit()

            # send to UI
            socketio.emit('latency', {'value': latency})

            time.sleep(1)

        except Exception as e:
            print("Error:", e)
            break


# 🔐 NEW: login route
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        user = request.form['username']
        pwd = request.form['password']

        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (user, pwd))
        result = cursor.fetchone()

        if result:
            session['user'] = user
            return redirect('/')
        else:
            return "Invalid credentials"

    return render_template('login.html')


# 🔐 MODIFIED: protect main page
@app.route('/')
def index():
    if 'user' not in session:
        return redirect('/login')
    return render_template('index.html')


# 🔐 OPTIONAL: logout
@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect('/login')


if __name__ == "__main__":
    socketio.start_background_task(tcp_listener)
    socketio.run(app, port=5000)
