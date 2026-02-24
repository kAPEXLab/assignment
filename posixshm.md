# POSIX Shared Memory
## Real-Time System Dashboard: Shared Memory Data Exchange

_Problem Statement_

Create a real-time shared dashboard using shared memory, where:
* A writer process updates system statistics every second.
* A reader process continuously displays those statistics.
* A shared memory segment holds a struct with CPU %, RAM %, and timestamp.
* Add synchronization using POSIX semaphores.

---

**Step 1 — Study Shared Memory**

* Fastest IPC mechanism
* Memory is shared between processes
* Requires synchronization
* Learn APIs:
  * shm_open()
  * ftruncate()
  * mmap()
  * munmap()

---

**Step 2 — Write a Tiny Shared Memory Test**

Task:

* Program A writes integer 42
* Program B reads and prints 42
* Run both programs together

---

**Step 3 — Create a Shared Struct**

Define a struct:
```
typedef struct {
  float cpu_usage;
  float ram_usage;
  char timestamp[32];
} stats_t;
```

---

**Step 4 — Implement Writer (Producer)**

Writer:
* Opens shared memory
* Maps struct
* Updates data every second
* Generates CPU/RAM random values
* Updates timestamp

---

**Step 5 — Implement Reader (Monitor)**

Reader:

* Opens shared memory
* Maps the same struct
* Prints values every second
* Creates dashboard-like output

---

**Step 6 — Study Synchronization**

Study and Implement:
* Why race conditions occur
* Use POSIX semaphore 

---

**Expected Outcomes**
* Understand shared memory mapping
* Implement producer–consumer data sharing
* Identify race conditions
* Build a real-time dashboard
* Appreciate speed advantages of shared memory
