//Deejuanae Lewis
#include "student.h"
#include "course.h"
using namespace std;

namespace BrooklynPoly {
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

}