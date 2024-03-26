#include "evaluation.h"

evaluation::evaluation(const typeValue &_typeEval, const string &_val_str) {
    typeVal = _typeEval;
    val_str = _val_str;
}

evaluation::evaluation(const typeValue &_typeEval, const int &_val_int) {
    typeVal = _typeEval;
    val_int = _val_int;
}

evaluation::evaluation(const typeValue &_typeEval, const bool &_val_bool) {
    typeVal = _typeEval;
    val_bool = _val_bool;
}

evaluation::evaluation(const string &_val_str){
    typeVal = STRING;
    val_str = _val_str;
}

evaluation::evaluation(const int &_val_int){
    typeVal = INT;
    val_int = _val_int;
}

evaluation::evaluation(const bool &_val_bool){
    typeVal = BOOL;
    val_bool = _val_bool;
}

evaluation operator+(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(INT, e1.val_int+e2.val_int);
    if(e1.typeVal==STRING && e2.typeVal==STRING)
        return evaluation(STRING, e1.val_str+e2.val_str);
    throw Exception("type error (+)");
}

evaluation operator-(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(INT, e1.val_int-e2.val_int);
    throw Exception("type error (-)");
}

evaluation operator*(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(INT, e1.val_int*e2.val_int);
    throw Exception("type error (*)");
}

evaluation operator/(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(INT, e1.val_int/e2.val_int);
    throw Exception("type error (/)");
}

evaluation operator>(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(BOOL, e1.val_int>e2.val_int);
    throw Exception("type error (>)");
}

evaluation operator<(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(BOOL, e1.val_int<e2.val_int);
    throw Exception("type error (<)");
}

evaluation operator>=(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(BOOL, e1.val_int>=e2.val_int);
    throw Exception("type error (>=)");
}

evaluation operator<=(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(BOOL, e1.val_int<=e2.val_int);
    throw Exception("type error (<=)");
}

evaluation operator==(const evaluation &e1, const evaluation &e2) {
    if(e1.typeVal==INT && e2.typeVal==INT)
        return evaluation(BOOL, e1.val_int==e2.val_int);
    else if(e1.typeVal==STRING && e2.typeVal==STRING)
        return evaluation(BOOL, e1.val_str==e2.val_str);
    else if(e1.typeVal==BOOL && e2.typeVal==BOOL)
        return evaluation(BOOL, e1.val_bool==e2.val_bool);
    throw Exception("type error (==)");
}

string evaluation::toString() const {
    if(typeVal==INT)
        return std::to_string(val_int);
    else if(typeVal==STRING)
        return val_str;
    else
        return val_bool ? "1" : "0";
}

bool evaluation::toBoolean() const {
    if(typeVal==BOOL) return val_bool;
    throw Exception("not boolean variable");
}

bool evaluation::iszero() const {
    return (typeVal == INT && val_int == 0);
}

int evaluation::getVal() const {
    if(typeVal==INT) return val_int;
    throw Exception("not calculable value");
}

typeValue evaluation::getType() const {
    return typeVal;
}
