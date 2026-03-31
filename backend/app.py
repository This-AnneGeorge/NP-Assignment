import eventlet
eventlet.monkey_patch()

from flask import Flask, render_template, request, redirect, session
from flask_socketio import SocketIO
import socket, struct, time, sqlite3

app = Flask(__name__)
app.secret_key = "secret123"   # needed for login session
socketio = SocketIO(app, async_mode='eventlet')

# DB setup
conn = sqlite3.connect('latency.db', check_same_thread=False)
cursor = conn.cursor()

# tables
cursor.execute("""
CREATE TABLE IF NOT EXISTS latency_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    latency REAL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")

cursor.execute("""
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password TEXT
)
""")

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

            # store
            cursor.execute("INSERT INTO latency_logs (latency) VALUES (?)", (latency,))
            conn.commit()

            # send to UI
            socketio.emit('latency', {'value': latency})

            time.sleep(1)

        except:
            break



@app.route('/')
def home():
    if 'user' in session:
        return render_template('index.html')
    return redirect('/login')


@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username,password))
        user = cursor.fetchone()

        if user:
            session['user'] = username
            return redirect('/')
        else:
            return "Invalid credentials"

    return render_template('login.html')


@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            cursor.execute("INSERT INTO users VALUES (?,?)", (username,password))
            conn.commit()
            return redirect('/login')
        except:
            return "User already exists"

    return render_template('register.html')


@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect('/login')


if __name__ == "__main__":
    socketio.start_background_task(tcp_listener)
    socketio.run(app, port=5000)