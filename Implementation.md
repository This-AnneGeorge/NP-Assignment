# 📡 Web-Based Network Latency Tester

## 📌 Overview

This project implements a **Web-Based Network Latency Tester** that measures **round-trip time (RTT)** using TCP socket programming and displays results in real-time via a web interface using WebSockets.

It integrates:

* Low-level networking (C)
* Real-time communication (WebSockets)
* Database logging (SQLite)
* Web visualization (HTML + Chart.js)

---

## 🧠 System Architecture

```
TCP Client (C)
     ↓
TCP Server (C)
     ↓
Python WebSocket Server
     ↓
SQLite Database
     ↓
Web Browser (UI + Graph)
```

---

## ⚙️ Features

* ✅ TCP-based latency measurement using timestamps
* ✅ Concurrent client handling (multi-threaded server)
* ✅ Real-time updates using WebSockets
* ✅ Live graph visualization (Chart.js)
* ✅ SQLite database logging
* ✅ Configurable socket options (TCP_NODELAY, buffers, etc.)

---

## 📁 Project Structure

```
NP-Assignment/
│
├── tcp-latency/
│   ├── TCPserver.c
│   ├── TCPclient.c
│
├── backend/
│   ├── app.py
│   ├── latency.db (auto-created)
│   ├── templates/
│       └── index.html
│
├── .gitignore
└── README.md
```

---

## 🚀 Setup & Execution

### 1️⃣ Install Requirements

* Install Python 3
* Install GCC (MinGW for Windows)

Install Python packages:

```
pip install flask flask-socketio eventlet
```

---

### 2️⃣ Compile TCP Programs

```
cd tcp-latency
gcc TCPserver.c -o server -lws2_32
gcc TCPclient.c -o client -lws2_32
```

---

### 3️⃣ Run the System

#### Step 1: Start TCP Server

```
./server
```

#### Step 2: Start WebSocket Backend

```
cd backend
python app.py
```

#### Step 3: Start TCP Client

```
cd tcp-latency
./client
```

Enter:

* Server IP → `127.0.0.1`
* Interval → `1000` (ms)

---

### 4️⃣ Open Web Interface

```
http://localhost:5000
```

👉 You will see:

* Live latency values
* Avg / Min / Max
* Real-time graph

---

## 📊 Performance Analysis Guide

To evaluate system performance, test under different conditions:

### 🔹 1. Socket Options

Modify in server code:

* Enable/disable `TCP_NODELAY`
* Change buffer sizes (`SO_RCVBUF`, `SO_SNDBUF`)

👉 Observe:

* Changes in latency

---

### 🔹 2. Multiple Clients

Run multiple client instances:

```
./client
```

👉 Observe:

* Increased server load
* Latency variation

---

### 🔹 3. Database Impact

Compare:

* With database logging
* Without database logging

👉 Observe:

* Slight latency increase due to disk I/O

---

### 🔹 4. Network Conditions

Change:

* Request interval (e.g., 500ms vs 2000ms)

👉 Observe:

* Stability of latency

---

## 🔐 Future Work (Authentication & Security)

Currently, authentication is not implemented.

### 🔹 To Add Login System:

* Add login page (HTML form)
* Store users in SQLite:

  ```
  users(username, password)
  ```
* Validate before allowing access

### 🔹 Security Enhancements:

* Use HTTPS / WSS (WebSocket Secure)
* Add token-based authentication
* Prevent unauthorized access

---

## 🧪 Testing Scenarios

* Single client vs multiple clients
* Different intervals
* Socket option variations
* Sudden client disconnection

---

## 📌 Observations

* TCP ensures reliable transmission
* WebSockets enable real-time updates
* TCP_NODELAY reduces latency
* Database logging introduces minor overhead

---

## 👥 Team Contributions

* **Person 1**: TCP client-server & latency measurement
* **Person 2**: WebSocket backend & UI
* **Person 3**: Database, socket options, analysis

---

## 📌 Conclusion

This project demonstrates how low-level TCP networking can be integrated with modern web technologies to build a real-time latency monitoring system. It highlights the impact of network configurations, concurrency, and system design on performance.

---
