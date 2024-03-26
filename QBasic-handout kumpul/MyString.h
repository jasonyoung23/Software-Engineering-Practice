#ifndef MYSTRING_H
#define MYSTRING_H
#include<iostream>
#include<sstream>
#include<QDebug>
using namespace std;

class MyString{
private:
    QStringList tokens;
    QString line;
public:
    MyString(QString _line)
    {
        line = _line;
    }
    void split(){
        tokens = line.split(' ');
        qDebug() <<tokens.size();
    }
    void display(){
        for(unsigned int i=0; i<tokens.size(); i++){
            qDebug() << tokens[i] ;
        }
    }
};

#endif // MYSTRING_H
