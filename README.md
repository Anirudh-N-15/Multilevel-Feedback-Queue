# **Multilevel Feedback Queue (MLFQ) Scheduler** 

## **Problem Statement**
Implemented a Multi-level Feedback Queue Scheduling algorithm which simulates how processes are scheduled in a MLFQ in Operating systems.

### **MLFQ Scheduling Details**
An operating system implements **multilevel feedback queue scheduling** with **four queues**:

1. **Q0 (Highest Priority)** → Uses **Round-Robin (RR)** with a time slice of **5ms**.  
2. **Q1** → Uses **First-Come, First-Served (FCFS)** scheduling.  
3. **Q2** → Uses **Priority Scheduling**, where priority is taken as the inverse of the CPU time needed by the jobs.  
4. **Q3 (Lowest Priority)** → Uses **Shortest Job First (SJF)** scheduling.

### **Rules of Execution**
- Each job is **allocated 5ms in each queue** before moving to a lower-level queue.  
- Once **all processes finish execution in a queue,** the next queue starts processing.  
- If jobs are **still incomplete** after **Q3**, they are **returned to Q0** and the cycle repeats until completion.  
- **All scheduling algorithms are assumed to be preemptive**.  
- The goal is to **calculate the average turnaround time** for the given workload.


### **Sample Workload**
| Process | Total CPU Time Needed |
|---------|-----------------------|
| A       | 300 ms                |
| B       | 150 ms                |
| C       | 250 ms                |
| D       | 350 ms                |
| E       | 450 ms                |

---

## **How to Run the Code**
### **1. Install a C++ Compiler**
The program is written in **C++**. You need a **C++ compiler** to run the code.

#### **On Windows**
You can install **MinGW** (which includes `g++`):
```sh
winget install -e --id MSYS2.MSYS2
```
Then, open **MSYS2** and install `gcc`:
```sh
pacman -S mingw-w64-ucrt-x86_64-gcc
```
Verify installation:
```sh
g++ --version
```

Alternatively, if you have **Visual Studio** installed, you can compile the code using:
```sh
cl /EHsc filename.cpp
```

#### **On macOS**
```sh
xcode-select --install
```

---

## **User Input Format**
When prompted, enter the number of processes and their CPU times:

Example:
```
Enter number of Processes: 5
Enter Process Name and BurstTime: A 300
Enter Process Name and BurstTime: B 150
Enter Process Name and BurstTime: C 250
Enter Process Name and BurstTime: D 350
Enter Process Name and BurstTime: E 450
```

---

## **Output**
The program will display the **turnaround time** for each process and the **average turnaround time**:

Example:
```
Scheduling Started!
Turnaround Time of Process A is 850 ms
Turnaround Time of Process B is 400 ms
Turnaround Time of Process C is 700 ms
Turnaround Time of Process D is 950 ms
Turnaround Time of Process E is 1200 ms
Average Turnaround Time: 820 ms
```

---