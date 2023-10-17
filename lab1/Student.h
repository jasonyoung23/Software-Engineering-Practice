#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <iostream>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student. DONE
private:
    std::string name;
    std::string year;
    Degree degree;
protected:
    std::vector<Class*> classes;
public:
    Student(const std::string &tid, std::string nm, std::string yr);
    const std::string id;
    std::string toString() const;
    virtual double getGrade(){ }
    void addClass(Class *c);
};

// TODO: implement class Graduate. DONE
class Graduate: public Student {
    private:
    
    protected:

    public:
    Graduate(std::string tid, std::string nm, std::string yr);
    double getGrade();
};

// TODO: implement class Undergraduate. DONE
class Undergraduate: public Student {
    private:

    protected:

    public:
    Undergraduate(std::string tid, std::string nm, std::string yr);
    double getGrade();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error DONE
    StudentWrapper(const std::string &id, const Student &student):id(id), student(student) {
        //this.id = id;
        //this.student = student;
    }

    void setScore(double score)
    {
        if (score < 0 || score > 100){
            score = 0;
            this->score = score;
            throw "Wrong score!";
        }
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
