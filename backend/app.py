import eventlet
eventlet.monkey_patch()

from flask import Flask, render_template
from flask_socketio import SocketIO
import socket
import struct
import time
import sqlite3

app = Flask(__name__)
socketio = SocketIO(app, async_mode='eventlet')

# DB setup
conn = sqlite3.connect('latency.db', check_same_thread=False)
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS latency_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    latency REAL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
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


@app.route('/')
def index():
    return render_template('index.html')


if __name__ == "__main__":
    socketio.start_background_task(tcp_listener)
    socketio.run(app, port=5000)