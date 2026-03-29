

# 🚨 First — What you ACTUALLY need to submit

From your assignment instructions:


You need **TWO things**:

## 📄 FISAC-1 (PDF – handwritten)

Must include:

* Theory (TCP lifecycle, WebSocket handshake)
* Architecture diagram
* Screenshots (VERY IMPORTANT)
* Analysis (socket options, performance)
* Team contributions

## 💻 FISAC-2 (ZIP)

* Full working code
* Must be runnable
* Dynamic inputs (NOT hardcoded)



# ✅ FINAL TECH STACK 


| Component        | Tech                       |
| ---------------- | -------------------------- |
| TCP Server       | C (keep your current work) |
| WebSocket Server | Python (Flask-SocketIO)    |
| Frontend         | HTML + JS                  |
| Database         | SQLite                     |
| OS               | Linux (or WSL)             |



# 🔧 SYSTEM ARCHITECTURE 

```
TCP Client (C)
        ↓
TCP Server (C)  ---> SQLite DB
        ↓
Python WebSocket Bridge
        ↓
Web Browser UI (HTML/JS)
```

---

# 🧑‍🤝‍🧑 WORK DIVISION (3 PEOPLE)

## 👨‍💻 Person 1 — TCP + Core Logic (MOST IMPORTANT)

### Tasks:

* Fix your current code
* Add:

  * socket options
  * concurrency improvements
  * error handling
* Make inputs dynamic (IP, port, interval)

### Deliverables:

* server.c
* client.c

---

## 👩‍💻 Person 2 — WebSocket + UI

### Tasks:

* Python WebSocket server
* Receive latency data
* Broadcast to UI
* Build frontend:

  * current latency
  * avg/min/max

---

## 👨‍💻 Person 3 — Database + Security + Analysis

### Tasks:

* SQLite integration
* Store latency values
* Add simple login system
* Run experiments:

  * with/without TCP_NODELAY
  * multiple clients
* Prepare graphs/screenshots

---


### Make client dynamic

Take input:

* server IP
* number of requests
* interval

---

# 🌐 WEB SOCKET BRIDGE (simple version)

Python (don’t overcomplicate):

* Read latency from TCP (or simulate initially)
* Broadcast using WebSocket

---

# 🧠 THEORY (YOU WILL WRITE THIS IN PDF)

## ✍️ 1. TCP Socket Lifecycle

Write this EXACT structure:

* **Connection Establishment**

  * SYN → SYN-ACK → ACK

* **Data Transfer**

  * Reliable, ordered delivery

* **Connection Termination**

  * FIN → ACK → FIN → ACK
  * TIME_WAIT state

---

## ✍️ 2. WebSocket Handshake

* Starts as HTTP request
* Contains:

  * `Upgrade: websocket`
* Server responds:

  * `101 Switching Protocols`
* Connection becomes persistent

---

## ✍️ 3. Why WebSockets?

* No repeated TCP handshake
* Real-time updates
* Low latency

---

# 📊 PERFORMANCE ANALYSIS (THIS GETS YOU MARKS)

Do experiments:

| Test             | Observation    |
| ---------------- | -------------- |
| TCP_NODELAY OFF  | Higher latency |
| TCP_NODELAY ON   | Lower latency  |
| Small buffer     | More delay     |
| Multiple clients | Increased load |

---

# 🔐 SECURITY (DON’T OVERDO)

Just implement:

* simple username/password
* explain:

  * WSS adds encryption overhead
  * improves security

---

# 📸 WHAT IMAGES TO ADD IN PDF

VERY IMPORTANT FOR MARKS:

1. Architecture diagram
2. Terminal output (latency logs)
3. Web UI screenshot
4. Multiple clients running
5. Database table screenshot

---

# 🧾 FINAL REPORT STRUCTURE (WRITE THIS)

Use this EXACT flow:

### 1. Introduction

### 2. System Architecture

### 3. TCP Design & Lifecycle

### 4. WebSocket Communication

### 5. Implementation Details

### 6. Socket Options Analysis

### 7. Database Design

### 8. Security Mechanism

### 9. Results & Observations

### 10. Conclusion

---

