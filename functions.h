#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

// Student structure
struct Student {
    int id;
    std::string name;
    std::vector<double> grades; // store grades 0-100
};

// Function declarations

// Core operations
void addStudent(std::vector<Student>& db);
void listStudents(const std::vector<Student>& db);
int findStudent(const std::vector<Student>& db, int id); // find by ID
int findStudent(const std::vector<Student>& db, const std::string& name); // find by name (overloaded)
double calculateGPA(const Student& s);

// File operations
bool saveToFile(const std::vector<Student>& db, const std::string& filename);
bool loadFromFile(std::vector<Student>& db, const std::string& filename);

// Utility & validation
int getIntInput(const std::string& prompt);
double getDoubleInput(const std::string& prompt, double min, double max);

// Bonus: recursive sum
double recursiveSum(const std::vector<double>& arr, int n);

#endif // FUNCTIONS_H
