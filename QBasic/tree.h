#ifndef TREE_H
#define TREE_H

#include <QString>
#include <stack>
#include <vector>

#include "expression.h"

using namespace std;

enum stringType { constant, operand, variable, str};

struct binary{
    string data;
    stringType stp;

    binary(string s, stringType t){
        data = s;
        stp = t;
    }
};

class tree
{
public:
    tree(string s);
    ~tree();
    evaluation eval();
    bool check(const stack<binary> &opStack, const string &op);
    expressionType type() const;
    expression *root;
};

#endif // TREE_H
