//Deejuanae Lewis
#include "registrar.h"
#include "student.h"
#include "course.h"
using namespace std;

namespace BrooklynPoly {
    Registrar::Registrar(){}

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
}