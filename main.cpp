// Student Records Manager
// Created by Kavery Smith
// November 2025

#include "functions.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

void printMenu() {
    array<string, 8> options = {
        "1) Add student",
        "2) List students",
        "3) Find student by ID",
        "4) Find student by name",
        "5) Save to file",
        "6) Load from file",
        "7) Show help / sample subjects",
        "0) Exit"
    };
    cout << "=== Student Records Manager ===\n";
    for (const auto& opt : options) cout << opt << "\n";
}

int main() {
    vector<Student> db;
    const string filename = "students.txt";

    cout << "Welcome! This program was created by Kavery Smith.\n";
    cout << "It manages student records and saves them to '" << filename << "'.\n";

    if (loadFromFile(db, filename)) {
        cout << "Loaded " << db.size() << " students from " << filename << ".\n";
    } else {
        cout << "No existing file loaded (" << filename << " not found or could not be read).\n";
    }

    while (true) {
        printMenu();
        int choice = getIntInput("Enter choice: ");
        switch (choice) {
            case 1: addStudent(db); break;
            case 2: listStudents(db); break;
            case 3: {
                int id = getIntInput("Enter ID to find: ");
                int idx = findStudent(db, id);
                if (idx == -1) cout << "Not found.\n";
                else cout << "Found: ID " << db[idx].id << " | " << db[idx].name << " | GPA: " << calculateGPA(db[idx]) << "\n";
                break;
            }
            case 4: {
                cout << "Enter name (partial allowed): ";
                string name;
                getline(cin, name);
                int idx = findStudent(db, name);
                if (idx == -1) cout << "Not found.\n";
                else cout << "Found: ID " << db[idx].id << " | " << db[idx].name << " | GPA: " << calculateGPA(db[idx]) << "\n";
                break;
            }
            case 5:
                if (saveToFile(db, filename)) cout << "Saved to " << filename << ".\n";
                else cout << "Failed to save to " << filename << ".\n";
                break;
            case 6:
                if (loadFromFile(db, filename)) cout << "Loaded " << db.size() << " students from " << filename << ".\n";
                else cout << "Failed to load from " << filename << ".\n";
                break;
            case 7: {
                array<string,5> sampleSubjects = {"Math", "History", "Science", "Art", "PE"};
                cout << "Sample subjects (example): ";
                for (const auto& s : sampleSubjects) cout << s << " ";
                cout << "\n";
                break;
            }
            case 0:
                cout << "Goodbye — remember to save before exit if needed.\n";
                return 0;
            default: cout << "Unknown option, try again.\n";
        }
        cout << "\n";
    }

    return 0;
}
