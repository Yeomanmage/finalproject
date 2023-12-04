#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QBuffer>
#include <QTextStream>
#include <iostream>
using namespace std;


class SurfStudent {
public:
    SurfStudent(string name, string skill_level) : name(name), skill_level(skill_level), session(nullptr) {}
    string name;
    string skill_level;
    class SurfClass* session;
};

class SurfClass {
public:
    //Constructor to initialize SurfClass attributes
    SurfClass(string session_time, int max_capacity, string difficulty_level)
        : session_time(session_time), max_capacity(max_capacity), difficulty_level(difficulty_level) {
        enrolled_students.reserve(max_capacity);
    }


class SurfSchoolTests : public QObject {
    Q_OBJECT

private slots:
    //Test case for enrolling a student
    void testEnrollStudent() {
        //Initialize your classes vector and students list
        vector<SurfClass*> classes;
        list<SurfStudent*> students;

        //Create instances of SurfClass
        SurfClass* class1 = new SurfClass("Morning Session", 1, "Beginner");
        SurfClass* class2 = new SurfClass("Afternoon Session", 8, "Intermediate");
        SurfClass* class3 = new SurfClass("Evening Session", 12, "Advanced");

        classes.push_back(class1);
        classes.push_back(class2);
        classes.push_back(class3);

        //Sort surf classes based on difficulty level
        sort(classes.begin(), classes.end(), compareClassesByDifficulty);

        QBuffer inputBuffer;
        inputBuffer.setData("John\nIntermediate\n");
        inputBuffer.open(QIODevice::ReadOnly);
        cin.rdbuf(&inputBuffer);

        QBuffer outputBuffer;
        outputBuffer.open(QIODevice::WriteOnly);
        cout.rdbuf(&outputBuffer);

        // Run the enrollment function
        enrollStudent(classes, students);

        //Verify that the student has been enrolled in the correct class
        QVERIFY(students.size() == 1);
        QVERIFY(students.front()->session == class2);
        QVERIFY(class2->enrolled_students.size() == 1);
    }

    //Test case for listing classes
    void testListClasses() {
        //Initialize your classes vector
        vector<SurfClass*> classes;

        //Create instances of SurfClass
        SurfClass* class1 = new SurfClass("Morning Session", 1, "Beginner");
        SurfClass* class2 = new SurfClass("Afternoon Session", 8, "Intermediate");
        SurfClass* class3 = new SurfClass("Evening Session", 12, "Advanced");

        classes.push_back(class1);
        classes.push_back(class2);
        classes.push_back(class3);

        //Sort surf classes based on difficulty level
        sort(classes.begin(), classes.end(), compareClassesByDifficulty);

        //Redirect cout to a buffer for testing output
        QBuffer outputBuffer;
        outputBuffer.open(QIODevice::WriteOnly);
        cout.rdbuf(&outputBuffer);

        //Run the list classes function
        listClasses(classes);

        //Verify the output matches the expected format
        QString output = outputBuffer.data();
        QVERIFY(output.contains("Morning Session"));
        QVERIFY(output.contains("Afternoon Session"));
        QVERIFY(output.contains("Evening Session"));
    }

    //Test case for listing students
    void testListStudents() {
        // Initialize your students list
        list<SurfStudent*> students;

        //Create instances of SurfStudent
        SurfStudent* student1 = new SurfStudent("John", "Intermediate");
        SurfStudent* student2 = new SurfStudent("Alice", "Beginner");

        students.push_back(student1);
        students.push_back(student2);

        //Redirect cout to a buffer for testing output
        QBuffer outputBuffer;
        outputBuffer.open(QIODevice::WriteOnly);
        cout.rdbuf(&outputBuffer);

        //Run the list students function
        listStudents(students);

        //Verify the output matches the expected format
        QString output = outputBuffer.data();
        QVERIFY(output.contains("John"));
        QVERIFY(output.contains("Alice"));
        QVERIFY(output.contains("Intermediate"));
        QVERIFY(output.contains("Beginner"));
    }
};

QTEST_APPLESS_MAIN(SurfSchoolTests)
#include "surf_school_tests.moc"

