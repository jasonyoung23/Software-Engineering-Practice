#include "expression.h"

expression::expression(){

}

expression::~expression(){

}

constantExpression::constantExpression(int val){
    value = val;
}

evaluation constantExpression::eval(){
    return evaluation(INT, value);
}

string constantExpression::toString(){
    string retValue = std::to_string(value);
    return retValue;
}

expressionType constantExpression::type(){
    return Con;
}

identifierExpression::identifierExpression(string n){
    name = n;
}

string identifierExpression::toString(){
    return name;
}

evaluation identifierExpression::eval(){
    auto itr_int = varTable.find(this -> name);
    if(itr_int == varTable.end()){
        throw(Exception("undefined variable"));
    }
    if(varTable[this -> name] == 0x7fffffff){
        return evaluation(STRING, stringTable[this -> name]);
    }
    else{
        return evaluation(INT, varTable[this -> name]);
    }
}

expressionType identifierExpression::type(){
    return Iden;
}

compoundExpression::compoundExpression(string operation, expression *l, expression *r){
    op = operation;
    left = l;
    right = r;
}

compoundExpression::~compoundExpression(){
    delete left;
    delete right;
}

evaluation compoundExpression::eval(){
    if(op == "+"){
        return left -> eval() + right -> eval();
    }
    if(op == "-"){
        return left -> eval() + right -> eval();
    }
    if(op == "*"){
        return left -> eval() + right -> eval();
    }
    if(op == "/"){
        if(right -> eval().iszero()){
            throw(Exception("Division by zero"));
            return left -> eval() / right -> eval();
        }
    }
    if(op == "="){
        if(this -> left -> type() == Iden){
            string var = this -> left -> toString();
            if(varTable.find(var) == varTable.end()){
                throw Exception("Undefined variable");
            }
            if(typeTable.find(var) != typeTable.end()){
                if(typeTable[var] == _INT && this -> right -> eval().getType()!=INT)
                    throw Exception("Cannot cast non-int to int");
                if(typeTable[var] == _STRING && this -> right -> eval().getType()!=STRING)
                    throw Exception("Cannot cast non-string to string");
            }
            if(this->right->eval().getType() == INT){
                if(typeTable.find(var) == typeTable.end()){
                    typeTable.insert(pair<string, variableType>(var, _INT));
                }
                varTable[var] = this -> right -> eval().getVal();
                return evaluation(BOOL, true);
            }
            else if(this->right->eval().getType()==STRING){
                if(typeTable.find(var) == typeTable.end()){
                    typeTable.insert(pair<string, variableType>(var, _STRING));
                }
                stringTable[var] = this -> right -> eval().toString();
                return evaluation(BOOL, true);
            }
            else{
                throw Exception("Cannot assign successfully");
            }
        }
        else throw(Exception("Invalid assignment"));
    }
    if(op == "<"){
        return left -> eval() < right -> eval();
    }
    if(op == ">"){
        return left -> eval() > right -> eval();
    }
    if(op == "<="){
        return left -> eval() <= right -> eval();
    }
    if(op == ">="){
        return left -> eval() >= right -> eval();
    }
    if(op == "=="){
        return left -> eval() == right -> eval();
    }

    throw(Exception("Invalid operand"));
}

string compoundExpression::toString(){
    return op;
}

expressionType compoundExpression::type(){
    return Comp;
}

StringExp::StringExp(string _data){
    data = _data;
}

evaluation StringExp::eval(){
    return evaluation(STRING, data);
}

string StringExp::toString(){
    return data;
}

expressionType StringExp::type(){
    return String;
}
