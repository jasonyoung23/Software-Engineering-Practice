#include "statement.h"

Statement::Statement(){}

remarkStatement::remarkStatement(vector<string> &lineVec){
    string tmp = "";
    for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
        tmp = tmp + " " + *itr;
    }
    remark = tmp;
}

inputStatement::inputStatement(vector<string> &lineVec){
    varName = lineVec[1];
    value = 0x7fffffff;
}

void inputStatement::execute(){
    varTable[varName] = value;
}

printStatement::printStatement(vector<string> &lineVec){
    string tmp = "";
    for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
        tmp = tmp + *itr;
    }
    exp = new tree(tmp);
}

void printStatement::execute(){
    value = exp->eval().toString();
}

string printStatement::getValue(){
    execute();
    return value;
}

letStatement::letStatement(vector<string> &lineVec){
    string tmp = "";
    for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
        tmp = tmp + *itr;
    }
    exp = new tree(tmp);
}

void letStatement::execute(){
    success = exp->eval().toBoolean();
}

bool letStatement::getSuccess(){
    execute();
    return success;
}

gotoStatement::gotoStatement(vector<string> &lineVec){
    string tmp = "";
    for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
        tmp = tmp + *itr;
    }
    exp = new tree(tmp);
}

void gotoStatement::execute(){
    nextLine = exp->eval().getVal();
}

int gotoStatement::toLine(){
    execute();
    return nextLine;
}

ifStatement::ifStatement(vector<string> &lineVec){
    string tmp = "";
    auto itr = lineVec.begin()+1;
    while(itr != lineVec.end() && *itr != "THEN"){
        tmp = tmp + *itr;
        itr++;
    }
    if(itr == lineVec.end()) throw Exception("Invalid statement IF-THEN");
    exp = new tree(tmp);
    if(*itr == "THEN") itr++;
    nextLine = std::stoi(*itr);
}

void ifStatement::execute(){
    flag = (bool)exp->eval().toBoolean();
}

intAndbool ifStatement::toLine(){
    execute();
    return intAndbool(nextLine, flag);
}
