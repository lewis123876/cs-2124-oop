//Deejuanae Lewis
#ifndef student_h
#define student_h

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly {
    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course* coursePtr);

        // Student method needed by Course::removeStudentsFromCourse
        void removedFromCourse(Course* coursePtr);

    private:
        std::string name;
        std::vector<Course*> courses;
    }; // Student

}

#endif
