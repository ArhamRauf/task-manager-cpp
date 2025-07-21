#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Task {
    string title;
    bool completed;
};

vector<Task> tasks;

void addTask() {
    Task task;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, task.title);
    task.completed = false;
    tasks.push_back(task);
    cout << " Task added!\n";
}

void displayTasks() {
    if (tasks.empty()) {
        cout << " No tasks available.\n";
        return;
    }
    cout << "\n Your Tasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "✔" : " ") << "] " << tasks[i].title << "\n";
    }
}

void markComplete() {
    int index;
    displayTasks();
    cout << "Enter task number to mark complete: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << " Task marked as complete!\n";
    } else {
        cout << " Invalid index.\n";
    }
}

void deleteTask() {
    int index;
    displayTasks();
    cout << "Enter task number to delete: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << " Task deleted.\n";
    } else {
        cout << " Invalid index.\n";
    }
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.title << ";" << task.completed << "\n";
    }
    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");
    if (!file) return;
    tasks.clear();
    string line;
    while (getline(file, line)) {
        size_t sep = line.find(';');
        if (sep != string::npos) {
            Task task;
            task.title = line.substr(0, sep);
            task.completed = (line.substr(sep + 1) == "1");
            tasks.push_back(task);
        }
    }
    file.close();
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    loadTasks();
    int choice;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "=== Task Manager ===\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Complete\n";
        cout << "4. Delete Task\n";
        cout << "5. Save & Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); pause(); break;
            case 2: displayTasks(); pause(); break;
            case 3: markComplete(); pause(); break;
            case 4: deleteTask(); pause(); break;
            case 5: saveTasks(); cout << "👋 Bye!\n"; return 0;
            default: cout << " Invalid option\n"; pause();
        }
    }
}
