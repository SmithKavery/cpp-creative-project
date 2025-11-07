#include "functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>   // Needed for round()

using namespace std;

// Input validation for integers
int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Input validation for doubles (grades)
double getDoubleInput(const string& prompt, double min, double max) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            if (val < min || val > max) {
                cout << "Please enter a number between " << min << " and " << max << ".\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Add a new student
void addStudent(vector<Student>& db) {
    Student s;
    s.id = getIntInput("Enter student ID (integer): ");
    cout << "Enter student name: ";
    getline(cin, s.name);
    int nGrades = getIntInput("How many grades to enter? (0-10): ");
    if (nGrades < 0) nGrades = 0;
    if (nGrades > 10) nGrades = 10;
    for (int i = 0; i < nGrades; ++i) {
        double g = getDoubleInput("  Enter grade (0-100): ", 0.0, 100.0);
        s.grades.push_back(g);
    }
    db.push_back(s);
    cout << "Student added: " << s.name << " (ID: " << s.id << ")\n";
}

// List all students
void listStudents(const vector<Student>& db) {
    if (db.empty()) {
        cout << "No students in the database.\n";
        return;
    }
    for (const auto& s : db) {
        cout << "ID: " << s.id << " | Name: " << s.name << " | Grades: ";
        if (s.grades.empty()) cout << "None";
        else {
            for (double g : s.grades) cout << g << " ";
        }
        cout << "| GPA: " << calculateGPA(s) << "\n";
    }
}

// Find student by ID
int findStudent(const vector<Student>& db, int id) {
    for (size_t i = 0; i < db.size(); ++i) {
        if (db[i].id == id) return static_cast<int>(i);
    }
    return -1;
}

// Find student by name (overloaded)
int findStudent(const vector<Student>& db, const string& name) {
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    for (size_t i = 0; i < db.size(); ++i) {
        string candidate = db[i].name;
        transform(candidate.begin(), candidate.end(), candidate.begin(), ::tolower);
        if (candidate.find(lowerName) != string::npos) return static_cast<int>(i);
    }
    return -1;
}

// Calculate GPA
double calculateGPA(const Student& s) {
    if (s.grades.empty()) return 0.0;
    double sum = recursiveSum(s.grades, (int)s.grades.size());
    double avg = sum / s.grades.size();
    double gpa = (avg / 100.0) * 4.0;
    return round(gpa * 100.0) / 100.0; // round to 2 decimals
}

// Save database to file
bool saveToFile(const vector<Student>& db, const string& filename) {
    ofstream ofs(filename);
    if (!ofs) return false;
    for (const auto& s : db) {
        ofs << s.id << "|" << s.name << "|";
        for (size_t i = 0; i < s.grades.size(); ++i) {
            ofs << s.grades[i];
            if (i + 1 < s.grades.size()) ofs << ",";
        }
        ofs << "\n";
    }
    ofs.close();
    return true;
}

// Load database from file
bool loadFromFile(vector<Student>& db, const string& filename) {
    ifstream ifs(filename);
    if (!ifs) return false;
    db.clear();
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, gradesStr;
        if (!getline(ss, idStr, '|')) continue;
        if (!getline(ss, name, '|')) continue;
        if (!getline(ss, gradesStr)) gradesStr = "";

        Student s;
        try { s.id = stoi(idStr); } catch (...) { continue; }
        s.name = name;
        if (!gradesStr.empty()) {
            stringstream gss(gradesStr);
            string gToken;
            while (getline(gss, gToken, ',')) {
                try { s.grades.push_back(stod(gToken)); } catch (...) {}
            }
        }
        db.push_back(s);
    }
    ifs.close();
    return true;
}

// Recursive sum of grades
double recursiveSum(const vector<double>& arr, int n) {
    if (n <= 0) return 0.0;
    if (n == 1) return arr[0];
    return recursiveSum(arr, n - 1) + arr[n - 1];
}
