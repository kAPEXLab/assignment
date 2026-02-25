---
layout: default
title: Mini Project 1 Guidelines
category: MiniProject
nav: true
nav_order: 20
---

# **Mini Project Guidelines – Linux System Calls & IPC (Simulation-Based)**

## **1. Objective**

You will design and implement a **simulation-based engineering system** that demonstrates your understanding of Linux system calls and POSIX APIs.  
Your project must reflect **practical use** of as many of these topics as possible:

*   **File I/O:** `open`, `read`, `write`, `lseek`, `close`
*   **Process Control:** `fork`, `exec`, `waitpid`
*   **Signals:** signal handling using `signal` or `sigaction`
*   **IPC:** pipe, FIFO (named pipe), message queue, shared memory, semaphore
*   **Threads & Sync:** pthreads, mutexes, condition variables

No hardware is allowed; all data must be **simulated**, e.g., using timers, random numbers, or predefined files.

***

# **2. What You Need to Do**

Your mini project has three major phases:

***

## **Phase 1: Choose an Engineering Scenario**

Select a **realistic scenario** from engineering, industry, automotive, IoT or any domains.  
Examples include (but are not limited to):

*   Machine monitoring system
*   Traffic signal simulation
*   Hospital patient vital tracking
*   Factory production line simulation
*   Data aggregation and alerting system
*   Multi-sensor monitoring and processing system

Your scenario **must justify** the use of multiple system calls and IPC mechanisms.

***

## **Phase 2: Design the Architecture**

Before writing code, create a **clear and detailed architecture**, including:

### **A. Process-Level Design**

*   Which parts run as separate processes?
*   Where will you use `fork`, `exec`, and `waitpid`?
*   How does the parent supervise the children?

### **B. Thread-Level Design**

*   Which components require threads?
*   What tasks do the threads perform?
*   Where are mutexes or condition variables needed?

### **C. IPC and Communication Plan**

For each communication path, specify:

*   Whether you will use **pipe**, **FIFO**, **message queue**, **shared memory**, or **semaphore**
*   What data is shared and how synchronization is maintained

### **D. Signal Handling Plan**

Explain:

*   Which signals you will handle
*   What actions each signal will trigger (e.g., shutdown, snapshot, periodic tasks)

### **E. File I/O Plan**

Explain how you will use:

*   `open`, `read`, `write`, `lseek`, and `close`  
    for logs, reports, or simulation data.

### **F. Data Flow Diagram**

Include:

*   Process flow
*   Thread flow
*   IPC connections
*   Control signals
*   Input/output behavior

***

## **Phase 3: Implement the System**

After your design is approved, implement your solution in **C with a multi‑file structure** and a **Makefile**.

Your implementation must include:

### **A. Multiple Processes**

*   Create at least one parent–child relationship
*   Handle child exit using `waitpid`

### **B. Multiple Threads**

*   Use pthreads for concurrent internal tasks
*   Show proper synchronization using mutex/condition variable

### **C. At Least Two Different IPC Mechanisms**

Choose any two (or more):

*   pipe
*   FIFO
*   message queue
*   shared memory + semaphore

### **D. Signals**

You must:

*   Install custom signal handlers
*   Use signals for at least one important function (e.g., shutdown, periodic update, special command)

### **E. File Handling**

Demonstrate:

*   Log creation
*   Structured writing/reading
*   Using `lseek` to update headers, offsets, or metadata

### **F. Simulated Data**

Use:

*   Random number generator
*   Predefined test files
*   Timers
*   Controlled anomalies (optional)  
    No real sensors/hardware.

### **G. Testing**

Your project must run:

*   A normal simulation run
*   A stress/failure scenario
*   Proper cleanup of processes, threads, IPC resources

***

# **3. Deliverables**

Submit the following:

### **1. Project Proposal**

*   Scenario description
*   List of system calls/APIs you plan to use and why
*   Initial block diagram
*   High-level data flow

### **2. Detailed Design (4–6 pages)**

*   Process design
*   Thread design
*   IPC mapping
*   Signal handling plan
*   File-handling plan
*   Error-handling strategy
*   Testing approach

### **3. Source Code**

*   Clean multi-file C code
*   Proper folder structure
*   Header files for each module
*   No unused code/variables

### **4. Makefile**

Must support:

*   `make all`
*   `make clean`
*   `make run`
*   `make test` (optional)

### **5. README**

Include:

*   Scenario summary
*   Architecture diagram
*   Build steps
*   Run instructions
*   Explanation of where each system call is used
*   Sample run output (non-verbose)

### **6. Demo**

You will perform a short live demo showing:

*   How processes/threads start
*   IPC working
*   Signal handling
*   Logs or output files
*   Clean shutdown
*   No zombie processes

### **7. Reflection**

Briefly explain:

*   What worked
*   What challenges you faced
*   What you learned

***

# **5. General Tips**

*   Start with **architecture**, not coding.
*   Keep modules small and focused.
*   Document every major function and module.
*   Use proper error checks for all system calls.
*   Never ignore return values.
*   Use deterministic seeds for testing (same output every run).
*   Do gradual testing: IPC first, then processes, then threads.
*   Ensure clean shutdown: no zombies, no leaked IPC resources.
*   Keep the design *simple but complete*.

***
