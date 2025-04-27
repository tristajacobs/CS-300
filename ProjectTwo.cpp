/*
 * ProjectTwo.cpp
 * CS-300-18412-M01: DSA: Analysis and Design
 * Author: Trista Jacobs
 * Date: April 20, 2025
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

// Course represents a catalog entry: id, title, prereq
struct Course {
    string id;               // course number
    string title;            // course title
    vector<string> prereq;   // prerequisites
};

vector<Course> courses;  // Global list of courses

void LoadData(const string &fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Error: Cannot open '" << fileName << "'" << endl;
        return;
    }
    courses.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Course c;
        string field;
        getline(ss, c.id, ',');      // course number
        getline(ss, c.title, ',');   // course title
        while (getline(ss, field, ',')) {
            if (!field.empty())
                c.prereq.push_back(field);
        }
        courses.push_back(c);
    }
    cout << "Loaded " << courses.size() << " course(s) from '" << fileName << "'" << endl;
}

void PrintCourseList() {
    if (courses.empty()) {
        cout << "No data loaded. Please load data first." << endl;
        return;
    }
    cout << "\nHere is a sample schedule:\n";
    vector<Course> sorted = courses;
    sort(sorted.begin(), sorted.end(), [](const Course &a, const Course &b) {
        return a.id < b.id;
    });
    for (auto &c : sorted) {
        cout << c.id << ", " << c.title << endl;
    }
}

void PrintCourseDetails() {
    if (courses.empty()) {
        cout << "No data loaded. Please load data first." << endl;
        return;
    }
    cout << "\nEnter course number: ";
    string target;
    getline(cin, target);
    for (auto &ch : target) ch = toupper(ch);
    for (auto &c : courses) {
        string idUpper = c.id;
        for (auto &ch : idUpper) ch = toupper(ch);
        if (idUpper == target) {
            cout << "\n" << c.id << ", " << c.title << endl;
            if (!c.prereq.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < c.prereq.size(); ++i) {
                    cout << c.prereq[i];
                    if (i + 1 < c.prereq.size()) cout << ", ";
                }
                cout << endl;
            }
            return;
        }
    }
    cout << "\nCourse '" << target << "' not found." << endl;
}

int main() {
    cout << "Welcome to the course planner." << endl;
    while (true) {
        cout << "\n1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course Details" << endl;
        cout << "9. Exit" << endl;
        cout << "\nChoose an option: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) {
            cout << "Enter data file name: ";
            string fileName;
            getline(cin, fileName);
            LoadData(fileName);
        } else if (choice == 2) {
            PrintCourseList();
        } else if (choice == 3) {
            PrintCourseDetails();
        } else if (choice == 9) {
            cout << "\nThank you for using the course planner!" << endl;
            break;
        } else {
            cout << choice << " is not a valid option." << endl;
        }
    }
    return 0;
}