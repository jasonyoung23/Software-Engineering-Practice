#include "Class.h"
#include <string>
#include "Student.h"
#include <iostream>

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

void Student::addClass(Class *c){
    classes.push_back(c);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!";
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore. DONE
    if(students.size()>0){
        double total = 0.0;
        for(int i=0; i < students.size(); i++){
            total = total + students[i].getScore();
        }
        std::cout << students.size() << std::endl;
        return total/students.size();
    }
    return 0.0;
}
