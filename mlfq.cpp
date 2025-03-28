#include <iostream>
#include <thread>
#include <vector>
#include <pthread.h>
#include <queue>
#include <mutex>
#include <algorithm>

#define TIME_SLICE 5

using namespace std;
mutex mtx ;

struct Process{
    string name;
    int remainingTime;
    int completionTime;
    int burstTime;

    Process(string n, int time): name(n), burstTime(time), remainingTime(time), completionTime(0) {}
};

struct customComparator {
    bool operator() (Process &p1 , Process &p2){
        return p1.burstTime > p2.burstTime ;
    }
};

void roundRobin(queue<Process>& q0, queue<Process>& q1, queue<Process>& q4, int& currTime) { 
    lock_guard<mutex> lock(mtx); 
    while (!q0.empty()) {
        Process p = q0.front();
        q0.pop();
        int executionTime = min(TIME_SLICE, p.remainingTime);
        currTime += executionTime;
        p.remainingTime -= executionTime;
        if (p.remainingTime > 0) {
            q1.push(p);
        } else {
            p.completionTime = currTime;
            q4.push(p);
        }
    }
}


void firstComeFirstServe(queue<Process> &q1, priority_queue<Process, vector<Process>, customComparator> &q2, queue<Process> &q4, int &currTime) {
    lock_guard<mutex> lock(mtx);
    while (!q1.empty()) {
        Process p = q1.front();
        q1.pop();
        int executionTime = min(TIME_SLICE, p.remainingTime);
        currTime += executionTime;
        p.remainingTime -= executionTime;

        if (p.remainingTime > 0) {
            q2.push(p);
        } else {
            p.completionTime = currTime;
            q4.push(p);
        }
    }
}

void prioritySchedule(priority_queue<Process, vector<Process>, customComparator> &q2, priority_queue<Process, vector<Process>, customComparator> &q3, queue<Process> &q4, int &currTime) {
    lock_guard<mutex> lock(mtx);
    while (!q2.empty()) {
        Process p = q2.top();
        q2.pop();
        int executionTime = min(TIME_SLICE, p.remainingTime);
        currTime += executionTime;
        p.remainingTime -= executionTime;

        if (p.remainingTime > 0) {
            q3.push(p);
        } else {
            p.completionTime = currTime;
            q4.push(p);
        }
    }
}

void shortestJobFirst(priority_queue<Process, vector<Process>, customComparator> &q3, queue<Process> &q0, queue<Process> &q4, int &currTime) {
    lock_guard<mutex> lock(mtx);
    while (!q3.empty()) {
        Process p = q3.top();
        q3.pop();
        int executionTime = min(TIME_SLICE, p.remainingTime);
        currTime += executionTime;
        p.remainingTime -= executionTime;

        if (p.remainingTime > 0) {
            q0.push(p);
        } else {
            p.completionTime = currTime;
            q4.push(p);
        }
    }
}

int main(){
    int totalProcesses = 0;
    cout << "Enter no. of Processes: " ;
    cin >> totalProcesses;
    int currTime = 0;

//Queue q0 = RR, q1 = FCFS, q2 = Priority Scheduling, q3 = Shortest Job First, q4 = Last queue(Calculation)
// Two queues in each funtion, so that after one quanta is over it will go to the next queue(also in RR)
queue<Process> q0,q1, q4;
priority_queue<Process, vector<Process>, customComparator> q2, q3;

    for(int i=0;i<totalProcesses;++i){
        cout << "Enter Process Name and BurstTime: ";
        string n = "";
        int t = 0;
        cin >> n >> t ;
        Process p(n,t);
        q0.push(p);
    }
    cout << endl ;

    cout << "Scheduling Started!(using threads)" << endl ;
    cout << endl ;

    while(!q0.empty() || !q1.empty() || !q2.empty() || !q3.empty()){
        thread t1(roundRobin, ref(q0), ref(q1), ref(q4), ref(currTime));
        thread t2(firstComeFirstServe, ref(q1), ref(q2), ref(q4), ref(currTime));
        thread t3(prioritySchedule, ref(q2), ref(q3), ref(q4), ref(currTime));
        thread t4(shortestJobFirst, ref(q3), ref(q0), ref(q4), ref(currTime));

        t1.join(), t2.join(), t3.join(), t4.join();
    }

    int totalTime =0;

    while(!q4.empty()){
        Process p = q4.front();
        totalTime += p.completionTime ;
        cout << "Turnaround Time of Process " << p.name << " is " << p.completionTime << " ms" << endl ;
        q4.pop();
    }
    cout << endl ;
    cout << "Average Turnaround Time is " << (float)totalTime/totalProcesses << "ms" << endl ;
    return 0 ;
}
