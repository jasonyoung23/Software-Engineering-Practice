#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

class Exception : public exception{
public:
    Exception(string errorInfo){
        information = errorInfo;
    }
    string info(){
        return information;
    }
private:
    string information;
};

#endif // EXCEPTION_H
