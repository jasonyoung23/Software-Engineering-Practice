#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student. DONE

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
    
    return "";
}

// TODO: implement functions which are declared in Student.h. DONE

double Undergraduate::getGrade(){
    double total = 0;
    double totalcredit = 0;
    for(int i = 0; i < classes.size(); i++){
        StudentWrapper detail = classes[i]->getStudentWrapper(id);
        total = total + classes[i]->point * (detail.getScore()/20);
        totalcredit = totalcredit + classes[i]->point;
    }
    return total/totalcredit;
}

double Graduate::getGrade(){
    double total = 0;
    double totalcredit = 0;
    for(int i = 0; i < classes.size(); i++){
        StudentWrapper detail = classes[i]->getStudentWrapper(id);
        double score = detail.getScore();
        double tempScore = 0;
        if(score>=90 && score<=100){
            tempScore = 4.0;
        }
        else if(score>=80 && score<=89){
            tempScore = 3.5;
        }
        else if(score>=70 && score<=79){
            tempScore = 3.0;
        }
        else if(score>=60 && score<=69){
            tempScore = 2.5;
        }
        else{
            tempScore = 2.0;
        }
        total = total + classes[i]->point * tempScore;
        totalcredit = totalcredit + classes[i]->point;
    }
    return total/totalcredit;
}

Student::Student(const std::string &tid, std::string nm, std::string yr):id(tid){
    name = nm;
    year = yr;
}

Graduate::Graduate(std::string tid, std::string nm, std::string yr):Student(tid, nm, yr){

}

Undergraduate::Undergraduate(std::string tid, std::string nm, std::string yr):Student(tid, nm, yr){
    
}


