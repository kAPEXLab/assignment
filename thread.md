# Scenario: Robot Battery Monitor

* Imagine you are developing basic software for a home-cleaning robot. The robot continuously moves around the house and its battery slowly drains. When the battery becomes too low, the robot must automatically go to the charging dock and start charging.
* To simulate this behavior, you must write a C program that uses:
  * One background thread → simulates the battery draining
  * Main thread → checks battery level periodically
  * fork() + exec() → to run an external “charging program”  (such as your own charger program that prints "Robot is now charging...")

## Problem Statement
Design and implement a C program that simulates a robot’s battery monitoring system. The program must meet the following requirements:

### Part 1: Battery Drain Simulation (Thread)
Create a thread named battery_thread which:
* Starts with battery_level = 100%.
* Every 1 second: 
  * Reduces the battery by a random value between 1% and 10%.
  * Prints: [Sensor] Battery = XX%
* When battery level drops below 20%, it must set a shared flag: low_battery = 1.
* Use a mutex to safely update the shared variables.


### Part 2: Main Thread Monitoring
In the main thread:
* Periodically (every 1 second) check the low_battery flag.
* When low_battery == 1, print: [Main] Low battery detected! Going to charging station...
Then trigger the charging process.

### Part 3: Charging Action
When low battery is detected:
* Use fork() to create a child process.
* In the child process, run an external program such as:
  * Your own program ./charger --> which prints: Robot is now charging...
* In the parent process:
  * Wait for the child to finish using wait().
  * Print: [Main] Charging completed!

### Part 4: Reset & Continue
After charging finishes:
* Reset battery_level back to 100%.
* Reset the flag low_battery = 0.
Continue monitoring forever.

