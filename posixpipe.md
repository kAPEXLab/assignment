---
layout: default
title: POSIX PIPE
nav: true
nav_order: 4
---

# Sensor Data Splitter Using Parent + Two Children

_Problem Statement_

You will create an application where:
* The parent process simulates a temperature sensor by generating values periodically.
* Child 1 logs raw temperature values.
* Child 2 checks for high‑temperature warnings.

All communication must happen using a POSIX PIPE.

---

**Step 1 — Understand What a Pipe Is**

Read about:
* Pipes are unidirectional communication channels.
* They allow communication only between related processes.
* Learn file descriptors: read-end (fd[0]) and write-end (fd[1]).
* Draw a simple diagram of pipe → parent → children.

---

**Step 2 — Write a Minimal Pipe Program**

Implement a tiny tester before starting the project:
Task:
* Create a pipe.
* Parent writes “Hello”.
* Child reads and prints it.

Goal:
* Understand pipe(), fork(), read(), write(), close().

---

**Step 3 — Generate Random Temperature in Parent**

Implement:
* Parent generates an integer temperature every second.
* Use rand() % 20 + 50 to simulate values from 50–70°C.
* Print what parent is sending.

---

**Step 4 — Create Two Children Using fork() Twice**

Parent must create:
* Child 1
* Child 2

Both should share the same read end of the pipe.

---

**Step 5 — Implement Child 1 (Logger)**

Child 1 must:

* Close unused write-end.
* Read integers in a loop.
* Print: Child1: Logging <value>
* End when pipe closes.

---

**Step 6 — Implement Child 2 (Warning Checker)**

Child 2 must:

* Read same integers, independently.
* If temp > 60 → print WARNING.
* Else print normal temperature.

---

**Step 7 — Run, Observe Behavior**

Important learning:

* Pipe reads are destructive.
* Only one child will get each specific item in real pipe behavior.
* This introduces students to real limitations of pipes.

---

**Expected Outcomes**
* Create pipes and use file descriptors correctly.
* Create two children and manage independent read loops.
* Understand destructive reads & pipe limitations.
* Build a complete parent–child pipeline.
