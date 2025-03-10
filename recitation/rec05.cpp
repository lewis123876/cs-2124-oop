//Deejuanae Lewis
/*
  rec05-start.cpp

  Remember that the file you are to submit should be named rec05.cpp.
  And YOUR NAME should appear up here in the comment.
 */

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    friend ostream& operator<<(ostream& os, const Section& obj) {
        os << "Section: " << obj.name << ", Time slot: " << obj.timeSlot << ", Students:" << endl;
        if(obj.studentPtrs.size() > 0) {
            for (const Student* s: obj.studentPtrs) {
                os <<*s<< endl ;
            }
        }
        else {
            os << "None";
        }
        return os;
    }
public:
    Section(const string& name, const string& day, int hour): name(name),
    timeSlot{day,hour} {}

    Section (const Section& section): name(section.name), timeSlot(section.timeSlot) {
        for(const Student* s: section.studentPtrs) {
            Student* newStudent = new Student(*s);
            studentPtrs.push_back(newStudent);
        }
    }

    ~Section() {
        cout << "Section " << name << " is being deleted" << endl;
        for (Student* s: studentPtrs) {
            cout << "Deleting " << s->getName() << endl;
            delete s;
        }
        studentPtrs.clear();

    }

    void addStudent(const string& name);
    void addStudentGrade(const string& name, int grade, int week);


private:
    class Student {
        friend ostream& operator<<(ostream& os, const Student& obj) {
            os << "Name: " << obj.name << ", Grades: ";
            for( int i : obj.grades ) {
                os << " " << i ;
            }
            return os;
        }
    public:
        Student(const string& name) : name(name), grades(14, -1) {}
        const string& getName() const { return name; }
        void setGrade(int grade, int week) {
            grades[week-1] = grade;
        }

    private:
        string name;
        vector<int> grades;
    };

    class TimeSlot {
        friend ostream& operator<<(ostream& os, const TimeSlot& obj) {
            string meridiem = obj.hour > 12 ? "PM" : "AM";
            os << "[ Day: " << obj.day << ", Start time: " << (obj.hour % 12)
            << meridiem << " ]";
            return os;
        }
    public:
        TimeSlot(const string& day, int hour): day(day), hour(hour) {}
    private:
        string day;
        int hour;
    };

    string name;
    TimeSlot timeSlot;
    vector<Student*> studentPtrs;
};

void Section::addStudent(const string& name){
    Student* s = new Student(name);
    studentPtrs.push_back(s);
}

void Section::addStudentGrade(const string& name, int grade, int week) {
    int index;
    for(int i = 0; i< studentPtrs.size(); i++) {
        if(name == studentPtrs[i]->getName()) {
            index = i;
            break;
        }
    }
    studentPtrs[index]->setGrade(grade, week);
}


class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& obj) {
        if(obj.section == nullptr) {
            os << obj.name << " does not have a section";
        }
        else {
            os << obj.name << " has " << *obj.section;
        }
        return os;
    }
public:
    LabWorker(const string& name) : name(name), section(nullptr) {}

    void addSection(Section& section);
    void addGrade(const string& name, int grade, int week);

private:
    string name;
    Section* section;
};


void LabWorker::addSection(Section& section) {
    if(this->section != nullptr) {
        cout << this->name << " already has a section." << endl;
        return;
    }
    this->section = &section;
}

void LabWorker::addGrade(const string& name, int grade, int week) {
    if(section == nullptr) {
        cout << name << " has no section to add grades." << endl;
        return;
    }
    section->addStudentGrade(name,grade,week);
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main
