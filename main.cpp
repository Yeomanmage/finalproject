#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

//Define SurfStudent
class SurfStudent {
public:
    SurfStudent(string name, string skill_level) : name(name), skill_level(skill_level), session(nullptr) {}
    string name;
    string skill_level;
    class SurfClass* session;
};

//Define SurfClass
class SurfClass {
public:
    //Constructor to initialize SurfClass attributes
    SurfClass(string session_time, int max_capacity, string difficulty_level)
        : session_time(session_time), max_capacity(max_capacity), difficulty_level(difficulty_level) {
        enrolled_students.reserve(max_capacity);
    }

    string session_time;
    int max_capacity;
    string difficulty_level;
    vector<SurfStudent*> enrolled_students;
};

//Comparison function for sorting SurfClass instances based on difficulty level
bool compareClassesByDifficulty(const SurfClass* class1, const SurfClass* class2) {
    return class1->difficulty_level < class2->difficulty_level;
}

//Function to enroll a student
void enrollStudent(vector<SurfClass*>& classes, list<SurfStudent*>& students) {
    string name, skill_level;

    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter skill level (Beginner/Intermediate/Advanced): ";
    cin >> skill_level;

    //Input Validation
    while (skill_level != "Beginner" && skill_level != "Intermediate" && skill_level != "Advanced") {
        cout << "Please enter a valid skill level: ";
        cin >> skill_level;
    }

    SurfStudent* student = new SurfStudent(name, skill_level);

    //Enroll the student in a surf class
    for (SurfClass* surf_class : classes) {
        if (surf_class->difficulty_level == skill_level) {
            if (surf_class->enrolled_students.size() < surf_class->max_capacity) {
                student->session = surf_class;
                surf_class->enrolled_students.push_back(student);
                students.push_back(student);
                cout << student->name << " has been enrolled in " << surf_class->session_time << "." << endl;
            } else {
                cout << "Sorry, " << surf_class->session_time << " is full." << endl;
                delete student;
            }
            return;
        }
    }

    cout << "No matching class found for the given skill level." << endl;
    delete student;
}

//Function to list surf classes
void listClasses(const vector<SurfClass*>& classes) {
    for (SurfClass* surf_class : classes) {
        cout << "Class: " << surf_class->session_time << ", Difficulty: " << surf_class->difficulty_level << ", Enrolled: " << surf_class->enrolled_students.size() << endl;
    }
}

//Function to list surf students
void listStudents(const list<SurfStudent*>& students) {
    cout << "List of all students:" << endl;
    for (const SurfStudent* student : students) {
        cout << "Student: " << student->name << ", Skill Level: " << student->skill_level << endl;
    }
}

int main() {
    //Declare vectors and lists
    vector<SurfClass*> classes; // Use vector instead of list for SurfClass
    list<SurfStudent*> students;

    //Add surf classes to vector
    SurfClass* class1 = new SurfClass("Morning Session", 1, "Beginner");
    SurfClass* class2 = new SurfClass("Afternoon Session", 8, "Intermediate");
    SurfClass* class3 = new SurfClass("Evening Session", 12, "Advanced");

    classes.push_back(class1);
    classes.push_back(class2);
    classes.push_back(class3);

    //Sort surf classes based on difficulty level
    sort(classes.begin(), classes.end(), compareClassesByDifficulty);

    //Main menu loop
    while (true) {
        cout << "Options:" << endl;
        cout << "1. Enroll student" << endl;
        cout << "2. List classes" << endl;
        cout << "3. List all students" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        //Input Validation
        while (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a number between 1 and 4: ";
            cin >> choice;
        }

        //Perform selected action
        switch (choice) {
        case 1:
            enrollStudent(classes, students);
            break;
        case 2:
            listClasses(classes);
            break;
        case 3:
            listStudents(students);
            break;
        case 4:
            //Delete students and classes
            for (SurfClass* surf_class : classes) {
                for (SurfStudent* student : surf_class->enrolled_students) {
                    delete student;
                }
                delete surf_class;
            }
            return 0;
        }
    }

    return 0;
}
