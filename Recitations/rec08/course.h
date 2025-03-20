//Deejuanae Lewis
#ifndef course_h
#define course_h

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly {
    class Student;

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* studentPtr);

        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    }; // Course

}

#endif