---
layout: default
title: Signals
category: Process Control
nav: true
nav_order: 2
---

# Scenario: Log Monitoring System Using SIGUSR1 Between Unrelated Processes

### Context:

You are building a simple software setup with two independent processes:
* **Worker Process**: Continuously generates log entries in a file app.log.
* **Monitor Process**: Periodically checks the size of app.log. When the file grows beyond a limit (given 	by user), the Monitor sends SIGUSR1 to the Worker.

When the Worker receives SIGUSR1, it must switch from detailed logging to minimal logging.

### PART 1 — Implement the Worker Process
Create a C file named worker.c
* Print own PID on startup
* Open a file app.log in append mode
* Install a signal handler for SIGUSR1
* Maintain a global flag minimal_mode = 0
* Inside the handler, set minimal_mode = 1
* Keep writing logs every 1 second:
  * If minimal_mode == 0: write “detailed log entry…”
  * Else: write “minimal log entry”

### PART 2 — Implement the Monitor Process
Create a C file named monitor.c
* Take two command-line arguments:
  * PID of worker
  * Maximum allowed file size in bytes
* Every 2 seconds:
  * Check size of app.log using stat()
 * If file size > limit → print a message and send SIGUSR1 to worker using kill(pid, SIGUSR1)

