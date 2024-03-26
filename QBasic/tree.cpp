#include "tree.h"

tree::tree(string s)
{
    stack<binary> operandStack;
    stack<expression*> variableStack;
    vector<binary> table;
    vector<binary> table_tmp;
    int powerNumber = 0;
    int powerNow = 0;
    int strlen = s.length();
    string tmp;

    for(int i = 0;i < strlen;){
        tmp = "";
        // string
        if(s[i]=='\''){
            ++i;
            while(i<strlen && s[i] != '\'' && s[i] != '\"'){
                tmp = tmp + s[i];
                ++i;
            }
            if(s[i] == '\"' || i==strlen){
                throw Exception("string format error");
            }
            else{
                ++i;
                table.push_back((binary(tmp, str)));
            }
            continue;
        }
        else if(s[i]=='\"'){
            ++i;
            while(i<strlen && s[i] != '\"' && s[i] != '\''){
                tmp = tmp + s[i];
                ++i;
            }
            if(s[i] == '\'' || i==strlen){
                throw Exception("String format error");
            }
            else{
                ++i;
                table.push_back((binary(tmp, str)));
            }
            continue;
        }
        else if(s[i] <= '9' && s[i] >= '0'){
            while(s[i] <= '9' && s[i] >= '0' && i < strlen){
                tmp = tmp + s[i];
                ++i;
            }
            table.push_back(binary(tmp, constant));
            continue;
        }
        else if(s[i]=='<'||s[i]=='>'||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='('||s[i]==')'||s[i]=='='){
            if(s[i]=='-' && (i==0 || s[i-1]=='(' || s[i-1]=='=')){
                table.push_back(binary("0", constant));
            }
            tmp = tmp + s[i];
            ++i;
            if(i<strlen && s[i]=='=' && (s[i-1]=='>' || s[i-1]=='<' || s[i-1]=='=')){
                tmp = tmp + s[i];
                ++i;
            }
            table.push_back(binary(tmp, operand));
            continue;
        }
        else if((s[i]<='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')){
            while((!(s[i]=='<'||s[i]=='>'||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='('||s[i]=='='||s[i]==')'))&&i<strlen){
                tmp = tmp + s[i];
                ++i;
            }
            table.push_back(binary(tmp, variable));
            continue;
        }
        else throw Exception("Unknown symbol");
    }
    while(powerNumber != powerNow){
        int tableSize = table.size();
        int count = 0;
        int tableIndex;
        int bracketIndex1, bracketIndex2;
        int countBracket1, countBracket2;
        for(tableIndex=tableSize-1;tableIndex >= 0;--tableIndex){
            if(table[tableIndex].stp==operand && table[tableIndex].data=="**") count++;
            if(count>powerNow) break;
        }
        powerNow++;
        countBracket1=0;
        countBracket2=0;
        for(bracketIndex1=tableIndex-1;bracketIndex1>=0;--bracketIndex1){
            if(table[bracketIndex1].data=="(") countBracket1++;
            if(table[bracketIndex1].data==")") countBracket2++;
            if(countBracket1==countBracket2) break;
        }
        countBracket1=0;
        countBracket2=0;
        for(bracketIndex2=tableIndex+1;bracketIndex1<=tableSize-1;++bracketIndex2){
            if(table[bracketIndex2].data=="(") countBracket1++;
            if(table[bracketIndex2].data==")") countBracket2++;
            if(countBracket1==countBracket2) break;
        }
        int i=-1;
        while(i<tableSize-1){
            ++i;
            if(i==bracketIndex1){
                table_tmp.push_back(binary("(", operand));
                table_tmp.push_back(table[i]);
            }
            else if(i==bracketIndex2){
                table_tmp.push_back(table[i]);
                table_tmp.push_back(binary(")", operand));
            }
            else{
                table_tmp.push_back(table[i]);
            }
        }
        table.clear();
        table = table_tmp;
        table_tmp.clear();
    }
    int veclen = (int)table.size();
    for(int i = 0;i < veclen;++i){
        // variable or constant
        if(table[i].stp != operand){
            if(table[i].stp == variable){
                expression* treeNode = new identifierExpression(table[i].data);
                variableStack.push(treeNode);
            }
            else if(table[i].stp == constant){
                int constVal = std::stoi(table[i].data);
                expression* treeNode = new constantExpression(constVal);
                variableStack.push(treeNode);
            }
            else if(table[i].stp == str){
                expression* treeNode = new StringExp(table[i].data);
                variableStack.push(treeNode);
            }
        }
        else if(table[i].data != "(" && table[i].data != ")"){
            while(true){
                if(operandStack.empty() || operandStack.top().data == "("){
                    operandStack.push(table[i]);
                    break;
                }
                else if(check(operandStack, table[i].data)){
                    operandStack.push(table[i]);
                    break;
                }
                else{
                    binary tmpOp = operandStack.top();
                    operandStack.pop();

                    expression *left, *right, *treeNode;
                    if(variableStack.empty()) throw Exception("Illegal expression");
                    right = variableStack.top();
                    variableStack.pop();
                    if(variableStack.empty()) throw Exception("Illegal expression");
                    left = variableStack.top();
                    variableStack.pop();
                    treeNode = new compoundExpression(tmpOp.data, left, right);
                    root = treeNode;
                    variableStack.push(treeNode);
                }
            }
        }
        else if(table[i].data == "("){
            operandStack.push(table[i]);
        }
        else if(table[i].data == ")"){
            while(!operandStack.empty() && operandStack.top().data != "("){
                binary tmpOp = operandStack.top();
                operandStack.pop();

                expression *left, *right, *treeNode;
                if(variableStack.empty()) throw Exception("Illegal expression");
                right = variableStack.top();
                variableStack.pop();
                if(variableStack.empty()) throw Exception("Illegal expression");
                left = variableStack.top();
                variableStack.pop();
                treeNode = new compoundExpression(tmpOp.data, left, right);
                root = treeNode;
                variableStack.push(treeNode);
            }
            if(operandStack.empty()) throw Exception("Unexpected ')'");
            operandStack.pop();//pop "("
        }
    }
    while(!operandStack.empty()){
        binary tmpOp = operandStack.top();
        operandStack.pop();
        if(tmpOp.data == "(") throw Exception("Missing ')'");

        expression *left, *right, *treeNode;
        if(variableStack.empty()) throw Exception("Illegal expression");
        right = variableStack.top();
        variableStack.pop();
        if(variableStack.empty()) throw Exception("Illegal expression");
        left = variableStack.top();
        variableStack.pop();
        treeNode = new compoundExpression(tmpOp.data, left, right);
        root = treeNode;
        variableStack.push(treeNode);
    }
    if(variableStack.size() != 1) throw Exception("Error occurred when splitting expression");
    root = variableStack.top();
}

tree::~tree(){
    delete root;
}

bool tree::check(const stack<binary> &opStack, const string &op){
    if(op=="**"){
        if(opStack.top().data == "*"|| opStack.top().data == "/"||
            opStack.top().data == "+"|| opStack.top().data == "-"||
            opStack.top().data == "<"|| opStack.top().data == ">"||
            opStack.top().data == "=")
            return true;
    }
    else if(op=="*" || op=="/"){
        if(opStack.top().data == "+"|| opStack.top().data == "-"||
            opStack.top().data == "<"|| opStack.top().data == ">"||
            opStack.top().data == "=")
            return true;
    }
    else if(op=="+" || op=="-"){
        if(opStack.top().data == "<"|| opStack.top().data == ">"|| opStack.top().data == "=")
            return true;
    }
    return false;
}

evaluation tree::eval(){
    return root -> eval();
}

expressionType tree::type() const{
    return root -> type();
}
