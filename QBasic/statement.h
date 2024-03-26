#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>
#include "expression.h"
#include "tree.h"

using namespace std;

struct intAndbool{
    int i;
    bool b;

    intAndbool(int x, bool y):i(x),b(y){}
};

enum stateType {Remark, Input, Print, End, Let, Goto, If, Inputs, Printf};

class Statement{
public:
    Statement();
    virtual ~Statement(){};
    virtual void execute()=0;
    virtual stateType type()=0;
};

class remarkStatement:public Statement{
public:
    remarkStatement(vector<string> &lineVec);
    ~remarkStatement(){};
    void execute(){};
    stateType type(){return Remark;}

    string remark;
};

class inputStatement:public Statement{
public:
    inputStatement(vector<string> &lineVec);
    ~inputStatement(){};
    void execute();
    stateType type(){return Input;}
    void getValue(string &input);
    string getName();

    string varName;
    int value;
};

class printStatement: public Statement{
public:
    printStatement(vector<string> &lineVec);
    ~printStatement(){delete exp;};
    void execute();
    string getValue();
    stateType type(){return Print;}

    tree *exp;
    string value;
};

class endStatement: public Statement{
public:
    endStatement(){};
    ~endStatement(){};
    void execute();
    stateType type(){return End;}
};

class letStatement: public Statement{
public:
    letStatement(vector<string> &lineVec);
    ~letStatement(){delete exp;}
    void execute();
    bool getSuccess();
    stateType type(){return Let;}

    tree *exp;
    bool success;
};

class gotoStatement:public Statement{
public:
    gotoStatement(vector<string> &lineVec);
    ~gotoStatement(){delete exp;}
    void execute();
    stateType type(){return Goto;}
    int toLine();

    tree *exp;
    int nextLine;
};

class ifStatement:public Statement{
public:
    ifStatement(vector<string> &lineVec);
    ~ifStatement(){delete exp;}
    void execute();
    stateType type(){return If;}
    intAndbool toLine();

    tree *exp;
    int nextLine;
    bool flag;
};
#endif // STATEMENT_H
