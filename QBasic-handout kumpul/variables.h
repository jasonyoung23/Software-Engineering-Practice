#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <map>

using namespace std;

enum variableType{_STRING, _INT};

extern map<string, int> varTable;
extern map<string, string> stringTable;
extern map<string, variableType> typeTable;

#endif // VARIABLES_H
