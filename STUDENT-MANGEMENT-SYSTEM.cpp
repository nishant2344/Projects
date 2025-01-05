#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Student {
    string name;
    string rollNo;
    int age;
    string grade;
};

bool compareByRollNo(const Student& a, const Student& b) {
    return a.rollNo < b.rollNo;
}

class StudentManagementSystem {
private:
    vector<Student> students;

public:
    void addStudent() {
        Student student;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Enter student roll number: ";
        getline(cin, student.rollNo);
        cout << "Enter student age: ";
        cin >> student.age;
        cout << "Enter student grade: ";
        cin.ignore();
        getline(cin, student.grade);

        students.push_back(student);

        sort(students.begin(), students.end(), compareByRollNo);

        cout << "Student added successfully!\n\n";
    }

    void searchStudentByRollNo() {
        string queryRollNo;
        cout << "Enter roll number to search: ";
        cin >> queryRollNo;

        auto start = high_resolution_clock::now();

        int left = 0, right = students.size() - 1;
        bool found = false;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (students[mid].rollNo == queryRollNo) {
                displayStudent(students[mid]);
                found = true;
                break;
            }
            else if (students[mid].rollNo < queryRollNo) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        if (!found) {
            cout << "No student found with that roll number.\n\n";
        }

        cout << "Binary Search execution time: " << duration.count() << " microseconds.\n\n";
    }

    void searchStudentByName() {
        string queryName;
        cout << "Enter name to search: ";
        cin.ignore();
        getline(cin, queryName);

        auto start = high_resolution_clock::now();

        bool found = false;


        for (const auto& student : students) {
            if (student.name == queryName) {
                displayStudent(student);
                found = true;
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        if (!found) {
            cout << "No student found with that name.\n\n";
        }

        cout << "Linear Search execution time: " << duration.count() << " microseconds.\n\n";
    }

    void viewStudents() {
        if (students.empty()) {
            cout << "No students available.\n\n";
            return;
        }

        cout << "All Students:\n\n";
        for (const auto& student : students) {
            displayStudent(student);
        }
    }

    void deleteStudent() {
        string rollNo;
        cout << "Enter roll number of student to delete: ";
        cin.ignore();
        getline(cin, rollNo);

        auto it = students.begin();
        bool found = false;
        for (; it != students.end(); ++it) {
            if (it->rollNo == rollNo) {
                students.erase(it);
                cout << "Student deleted successfully!\n\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student not found.\n\n";
        }
    }

private:
    void displayStudent(const Student& student) {
        cout << "Name: " << student.name << "\n";
        cout << "Roll Number: " << student.rollNo << "\n";
        cout << "Age: " << student.age << "\n";
        cout << "Grade: " << student.grade << "\n\n";
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;

    while (true) {
        cout<<"\n";
        cout << "Student Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student by roll_no (Binary Search)\n";
        cout << "3. Search Student by Name (Linear Search)\n";
        cout << "4. View All Students\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.searchStudentByRollNo();
                break;
            case 3:
                sms.searchStudentByName();
                break;
            case 4:
                sms.viewStudents();
                break;
            case 5:
                sms.deleteStudent();
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. .\n";
        }
    }
}
