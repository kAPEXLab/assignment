---
layout: default
title: POSIX Message Queue
category: IPC
nav: true
nav_order: 6
---

# Priority-Based Task Notification System

_Problem Statement_

Implement a scheduler system where:
* Two sender processes send tasks.
* Sender 1 sends low-priority tasks.
* Sender 2 sends high-priority tasks.
* Scheduler receives tasks in priority order using POSIX message queues.

---

**Step 1 — Study Message Queues**

Understand:
* A queue holds discrete messages.
* Each message has a priority.
* Higher priority messages are delivered earlier.
* Learn APIs:
  * mq_open
  * mq_send
  * mq_receive
  * mq_close
  * mq_unlink

---

**Step 2 — Create a Tiny MQ Test**

Task:
* One program sends "hello".
* One program receives and prints.

Compile and verify.

---

**Step 3 — Implement Sender 1**

Sender 1:
* Sends "TASK_LOW_xxxx" messages.
* Priority = 0.

---

**Step 4 — Implement Sender 2**

Sender 2:
* Sends "TASK_HIGH_xxxx" messages.
* Priority = 5 (or higher).

---

**Step 5 — Implement Scheduler (Receiver)**

Scheduler should:
* Continuously call mq_receive().
* Print:
  * message text
  * priority
* Maintain counters:
  * total tasks
  * high-priority tasks
  * low-priority tasks

---

**Step 6 — Observe Message Prioritization**

* Start scheduler, then sender 1 and sender 2.
* Observe that high-priority tasks arrive first even if sent later.

---

**Expected Outcomes**

* How priority-based IPC works
* Message queue lifetime and attributes
* Difference between FIFO stream vs message queue packets
* Real-world scheduler-like implementation
* Message queue lifetime and attributes
* Difference between FIFO stream vs message queue packets
* Real-world scheduler-like implementation
