#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "variables.h"
#include "evaluation.h"
#include "exception.h"

using namespace std;

enum expressionType{ Con, Iden, Comp, String};

class expression
{
public:
    expression();
    virtual ~expression();
    virtual evaluation eval() = 0;
    virtual string toString() = 0;
    virtual expressionType type() = 0;
};

class constantExpression : public expression
{
public:
    constantExpression(int val);
    virtual evaluation eval();
    virtual string toString();
    virtual expressionType type();
    int value;
};

class identifierExpression: public expression
{
public:
    identifierExpression(string name);

    virtual evaluation eval();
    virtual string toString();
    virtual expressionType type();

    string name;
};

class compoundExpression: public expression
{
public:
    compoundExpression(string op, expression *left, expression *right);

    virtual ~compoundExpression();
    virtual evaluation eval();
    virtual string toString();
    virtual expressionType type();

    string op;
    expression *left, *right;
};

class StringExp: public expression
{
public:
    StringExp(string _data);

    virtual ~StringExp(){};
    virtual evaluation eval();
    virtual string toString();
    virtual expressionType type();

    string data;
};

#endif // EXPRESSION_H
