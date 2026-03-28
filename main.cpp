#include <iostream>   
#include <vector>     
#include <string>     
#include <algorithm>  
#include <set>        

using namespace std;


class person {
protected:
    string name;

public:
    person(string n = "") {
        name = n;
    }

    void setName(string n) {
        name = n;
    }

    string getName() const { 
        return name;
    }


    virtual void display() const {
        cout << "Name: " << name << endl;
    }
};


class student : public person {
private:
    int id;
    float gpa;
    set<string> courses;

public:
    student(int i, string n, float g) : person(n) {
        id = i;
        gpa = g;
    }

    void setId(int i) { id = i; }
    void setGpa(float g) { gpa = g; }

    int getId() const { return id; }
    float getGpa() const { return gpa; }

    void addCourse(string courseName) {
        auto result = courses.insert(courseName);
        if (!result.second) {
            cout << "Student is already enrolled in this course!\n";
        }
        else {
            cout << "Course added successfully!\n";
        }
    }


    void display() const override {
        cout << "ID: " << id << " | Name: " << name << " | GPA: " << gpa << "\n";
        cout << "Courses: ";
        if (courses.empty()) {
            cout << "No courses enrolled yet.";
        }
        else {
            for (const string& course : courses) {
                cout << "[" << course << "] ";
            }
        }
        cout << "\n-----------------------\n";
    }
};


int main() {
    vector<student> students;
    int choice;

    do {
        cout << "\nStudent Management System \n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student (by ID)\n";
        cout << "4. Sort Students (by GPA)\n";
        cout << "5. Add Course to Student\n";
        cout << "6. Delete Student\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id; 
            string name; 
            float gpa;
            cout << "Enter ID: "; 
            cin >> id;

      
            auto it = find_if(students.begin(), students.end(), [id](const student& s) {
                return s.getId() == id;
                });
            if (it != students.end()) {
                cout << "Error: Student ID already exists!\n";
                continue;
            }

            cout << "Enter Name: "; 
            cin.ignore();
            getline(cin, name);
            cout << "Enter GPA: "; 
            cin >> gpa;

    
            if (gpa < 0.0 ) {
                cout << "Error: GPA must be between 0.0 and 4.0!\n";
                continue;
            }

            students.push_back(student(id, name, gpa));
            cout << "Student added successfully!\n";
        }
        else if (choice == 2) {
            if (students.empty()) {
                cout << "No students in the system.\n";
            }
            else {
                cout << "\n List of Students \n";
                for (const auto& s : students) {
                    s.display();
                }
            }
        }
        else if (choice == 3) {
            int searchId;
            cout << "Enter ID to search: "; 
            cin >> searchId;
            auto it = find_if(students.begin(), students.end(), [searchId](const student& s) {
                return s.getId() == searchId;
                });

            if (it != students.end()) {
                cout << "Student Found \n";
                it->display();
            }
            else {
                cout << "Student not found!\n";
            }
        }
        else if (choice == 4) {
            if (students.empty()) {
                cout << "No students to sort.\n";
            }
            else {
                sort(students.begin(), students.end(), [](const student& a, const student& b) {
                    return a.getGpa() > b.getGpa();
                    });
                cout << "Students sorted by GPA (Highest to Lowest)!\n";
            }
        }
        else if (choice == 5) {
            int targetId;
            cout << "Enter Student ID: ";
            cin >> targetId;
            auto it = find_if(students.begin(), students.end(), [targetId](const student& s) {
                return s.getId() == targetId;
                });

            if (it != students.end()) {
                string cName;
                cin.ignore(); getline(cin, cName);
                it->addCourse(cName);
            }
            else {
                cout << "Student not found!\n";
            }
        }
        else if (choice == 6) {
            int deleteId;
            cout << "Enter ID to delete: "; 
            cin >> deleteId;
            auto it = remove_if(students.begin(), students.end(), [deleteId](const student& s) {
                return s.getId() == deleteId;
                });

            if (it != students.end()) {
                students.erase(it, students.end());
                cout << "Student deleted successfully!\n";
            }
            else {
                cout << "Student ID not found!\n";
            }
        }
        else if (choice == 7) {
            cout << "Exiting system. Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
