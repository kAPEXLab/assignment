---
layout: default
title: POSIX FIFO
nav: true
nav_order: 4
---

## Command Dispatcher Terminal

_Problem Statement_

Design a system where:
* A server waits for commands from a FIFO.
* A client sends commands (LED_ON, LED_OFF, STATUS).
* The server performs simulated actions.

---

**Step 1 — Understand FIFO**
Learn:

* Difference between PIPE vs FIFO:
  * FIFO works for unrelated processes.
  * FIFO is a file on the filesystem.
* Study mkfifo() and FIFO permissions.

---

**Step 2 — Manual FIFO Test Using Terminal**

Task:
* Run: mkfifo myfifo
* In terminal 1: cat myfifo
* In terminal 2: echo hello > myfifo

Goal: understand blocking behavior.

---

**Step 3 — Implement Server**

Server should:
* Create FIFO at /tmp/cmdfifo.
* Open it read-only (O_RDONLY).
* Continuously read commands and print responses.
* Implement simple LED state variable.

---

**Step 4 — Implement Client**

Client should:
* Open FIFO write-only (O_WRONLY).
* Take input from user.
* Write the command into FIFO.
* Exit.

---

**Step 5 — Demonstrate Client–Server Operation**

Procedure:
* Start server in Terminal 1
* Start client in Terminal 2
* Send different commands
* Observe server actions

---

**Expected Outcomes**
* FIFO creation and deletion
* Client-server architecture
* Unrelated process IPC
* Blocking read/write behavior
* Real industrial CLI command-processing pattern
