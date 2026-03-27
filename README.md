# Web-Based Network Latency Tester (TCP + WebSocket)

## 📌 Overview

This project implements a **Web-Based Network Latency Tester** that measures **round-trip time (RTT)** between a TCP client and server using timestamped packets. The latency results are streamed in real-time to a web interface using WebSockets.

The system demonstrates:

* TCP socket programming in C
* Concurrent client handling
* Socket option configuration
* Database logging of latency metrics
* Real-time visualization via WebSockets
* Basic secure communication

---

## 🧠 System Architecture

```
TCP Client → TCP Server → WebSocket Bridge → Web Interface
                    ↓
                 Database
```

---

## ⚙️ Features

### 1. TCP Latency Measurement

* Client sends timestamp to server
* Server echoes it back immediately
* Client calculates RTT:

  ```
  RTT = current_time - sent_time
  ```

---

### 2. Concurrent TCP Server

* Handles multiple clients using threads
* Uses high-resolution timers for accuracy

---

### 3. Real-Time Web Interface

* WebSocket-based communication
* Displays:

  * Current latency
  * Average latency
  * Minimum and maximum latency

---

### 4. Socket Optimization

Configured socket options:

* `SO_REUSEADDR`
* `SO_RCVBUF`
* `SO_SNDBUF`
* `TCP_NODELAY`
* `SO_KEEPALIVE`
* Timeout settings

---

### 5. Database Logging

* Stores latency values with timestamps
* Enables performance analysis

---

### 6. Basic Security

* Simple authentication mechanism
* Secure communication using HTTPS/WSS (basic setup)

---

## 📁 Project Structure

```
project/
│
├── tcp/
│   ├── server.c
│   └── client.c
│
├── websocket/
│   ├── bridge.py
│   └── index.html
│
├── backend/
│   ├── database.c
│   └── schema.sql
│
├── .gitignore
└── README.md
```

---

## 🚀 Setup & Execution

### 1. Compile TCP Programs

Run in terminal:

```
gcc tcp/server.c -o server -lpthread
gcc tcp/client.c -o client
```

---

### 2. Run Server

```
./server
```

---

### 3. Run Client

```
./client
```

---

### 4. Start WebSocket Bridge

```
python websocket/bridge.py
```

---

### 5. Open Web Interface

Open in browser:

```
http://localhost:5000
```

---

## 🧪 Testing

* Run multiple clients simultaneously to test concurrency
* Modify socket options and observe latency changes
* Disconnect clients to test fault handling

---

## 📊 Observations

* TCP ensures reliable data transmission for accurate RTT measurement
* WebSockets enable real-time updates without repeated TCP handshakes
* Socket options significantly affect latency and responsiveness
* Database logging introduces slight overhead
* Secure communication may slightly increase latency

---

## 👥 Team Contributions

### Person 1 – TCP & Latency Measurement

* Implemented TCP client-server communication
* Designed RTT calculation using timestamps
* Handled concurrent client connections

---

### Person 2 – WebSocket & Web Interface

* Built WebSocket bridge for real-time data streaming
* Developed web interface for latency visualization

---

### Person 3 – Socket Options, Database & Security

* Configured advanced socket options
* Implemented database logging
* Added authentication and secure communication

---

## 📌 Conclusion

This project demonstrates how low-level TCP communication can be integrated with modern web technologies to build a real-time latency monitoring system. It highlights the impact of network configurations, concurrency, and security on performance and reliability.

---
