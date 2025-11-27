#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// A struct to represent a Task with priority
struct Task {
    string name;
    int priority;

    Task(string n, int p) : name(std::move(n)), priority(p) {}
};

// Custom comparator (higher priority = comes first)
struct TaskCompare {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority < b.priority; // max-heap by priority
    }
};

int main() {
    // 1. Max-heap (default)
    priority_queue<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(20);

    cout << "Max-Heap: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << "\n\n";

    // 2. Min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);

    cout << "Min-Heap: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n\n";

    // 3. Task scheduler with custom comparator
    priority_queue<Task, vector<Task>, TaskCompare> tasks;
    tasks.emplace("Do homework", 2);
    tasks.emplace("Pay bills", 5);
    tasks.emplace("Play games", 1);
    tasks.emplace("Go shopping", 3);

    cout << "Task execution order by priority:\n";
    while (!tasks.empty()) {
        Task t = tasks.top();
        cout << " - " << t.name << " (priority " << t.priority << ")\n";
        tasks.pop();
    }

    return 0;
}