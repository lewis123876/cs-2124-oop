//Deejuanae Lewis
#include <stdio.h>

#include "course.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly {
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
}