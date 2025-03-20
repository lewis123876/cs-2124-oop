//Deejuanae Lewis
//Rec08
/*
  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* studentPtr);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
}; // Course


class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* coursePtr);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* coursePtr);

private:
    string name;
    vector<Course*> courses;
}; // Student


class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string& name);
    // Creates a new student, if none with that name
    bool addStudent(const string& name);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string& name) const;
    size_t findCourse(const string& name) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

//course class
ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.getName() << ":";
    if(rhs.students.size() != 0) {
        for (const Student* student : rhs.students) {
            os << " " << student->getName();
        }
    } else {
        os << " No Students";
    }
    return os;
}

Course::Course(const string& courseName): name(courseName){}

const string& Course::getName() const{return name;}

bool Course::addStudent(Student* studentPtr) {
    for(const Student* student : students) {
        if(studentPtr == student) {
            return false;
        }
    }
    students.push_back(studentPtr);
    return true;
}

void Course::removeStudentsFromCourse() {
    for(Student* student: students) {
        student->removedFromCourse(this);
    }
    students.clear();
}


//Student class
ostream& operator<< (ostream& os, const Student& rhs) {
    os << rhs.name << ":";
    if (rhs.courses.size() == 0) {
        os << " No Courses";
    } else {
        for (const Course* course : rhs.courses) {
            os << " " << course->getName();
        }
    }
    os << endl;
    return os;
}

Student::Student(const string& name): name(name){};

const string& Student::getName() const{return name;}

bool Student :: addCourse(Course* coursePtr){
    for (const Course* course : courses){
        if (coursePtr == course){
            return false;
        }
    }
    courses.push_back(coursePtr);
    return true;
}

void Student::removedFromCourse(Course* coursePtr) {
    size_t index = courses.size();
    for(size_t i = 0; i < courses.size(); i++) {
        if(courses[i] == coursePtr) {
            index = i;
            break;
        }
    }

    for(size_t i = index; i < courses.size()-1; i++) {
        courses[i] = courses[i+1];
    }
    courses.pop_back();
}


//registrar class
Registrar::Registrar(){};

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os<< "Registrar's Report" << endl << "Courses: " << endl;
    for (const Course* course: rhs.courses) {
        os << *course <<endl;
    }
    os << "Students: " << endl;
    for(const Student* student: rhs.students) {
        os << *student << endl;
    }
    return os;
}

size_t Registrar::findStudent(const string& name) const {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getName() == name) {
            return i;
        }
    }
    return students.size();
}

size_t Registrar::findCourse(const string& name) const {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i]->getName() == name) {
            return i;
        }
    }
    return courses.size();
}

bool Registrar::addCourse(const string& name) {
    if(findCourse(name) == courses.size()) {
        courses.push_back(new Course(name));
        return true;
    }
    return false;
}

bool Registrar::addStudent(const string& name) {
    if(findStudent(name) == students.size()) {
        students.push_back(new Student(name));
        return true;
    }
    return false;
}


bool Registrar::enrollStudentInCourse(const string& studentName,
const string& courseName) {
    size_t studentInd = findStudent(studentName);
    size_t courseInd = findCourse(courseName);
    if((courseInd != courses.size()) && (studentInd != students.size())) {
        return courses[courseInd]->addStudent(students[studentInd]) &&
        students[studentInd]->addCourse(courses[courseInd]);
        // return true;
    }
    return false;
}


bool Registrar::cancelCourse(const string& courseName) {
    size_t courseInd = findCourse(courseName);
    if(courseInd != courses.size()) {
        courses[courseInd]->removeStudentsFromCourse();
        delete courses[courseInd];
        courses[courseInd] = courses[courses.size()-1];
        courses.pop_back();
        return true;
    }
    return false;
}

void Registrar::purge() {
    for(Student* student: students) {
        delete student;
    }
    students.clear();
    for(Course* course: courses) {
        delete course;
    }
    courses.clear();
}