#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("../Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate DONE
        // and Graduate.
    
        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);
        

        studentVec.push_back(st);
    }
    stfile.close();
    // TODO: load data from ./Classes.txt and push objects to the vector. DONE
    // Hint: how is student information read?
    ifstream stfile2("../Classes.txt");

    while (getline(stfile2, line)) {
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;
        bufv.clear();
        pos1 = line.find(':',0);
        if(line.substr(0, pos1) == "Class"){
            clsname = line.substr(pos1+1);
        }
        else if(line.substr(0, pos1) == "Points"){
            pos2 = line.find(':', pos1+1);
            point = stoi(line.substr(pos1+1));
            cl = new Class(clsname, point);
            classVec.push_back(cl);
        }
        else{
            for(int i = 0; i < studentVec.size(); i++){
                if(studentVec[i] -> id == line && cl != nullptr){
                    cl ->addStudent(*studentVec[i]);
                    studentVec[i] -> addClass(cl);
                }
            }
        }
    }
}

void AppX::inputScore()
{
    // TODO: implement inputScore. DONE
    // Hint: Take a look at printAvgScore().
    string sbuf;
    string cbuf;
    Class *cl;
    Student *st;
    double score;
    
    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> cbuf; 
        if (cbuf == "q")
            break;
        
        while (true){
            cout << "Please input the student ID (or input q to quit): ";
            cin >> sbuf;
            if (sbuf == "q")
            break;
            cout << "Please input the score: ";
            cin >> score;
            cl = nullptr;
            for (vector<Class *>::iterator it = classVec.begin();
                it != classVec.end();
                ++it) {
                    if ((*it)->name == cbuf) {
                    cl = *it;
                    break;
                    }
                }
            if (cl == nullptr) {
                cout << "No match class!" << endl;
                continue;
            }

            st = nullptr;
            for (vector<Student *>::iterator it = studentVec.begin();
                it != studentVec.end();
                ++it) {
                if ((*it)->id == sbuf) {
                    st = *it;
                    break;
                }
                }
            if (st == nullptr) {
                cout << "No match student!" << endl;
                continue;
            }

        
            try {
                cl -> getStudentWrapper(sbuf).setScore(score);
            }
            catch (const char* err){
                cout << err << endl;
            }
        }
    }
}

void AppX::printAvgScore()
{
    string cbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> cbuf;
        if (cbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == cbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: " << setprecision(2) << fixed << avg << endl;
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa. DONE
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Student *st;
    double gpa;

    while (true) {
        cout << "Please input the student ID (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        st = nullptr;
        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             ++it) {
            if ((*it)->id == sbuf) {
                st = *it;
                break;
            }
        }
        if (st == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }

        gpa = st->getGrade();
        cout << "GPA = " << setprecision(2) << fixed << gpa << endl;
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
