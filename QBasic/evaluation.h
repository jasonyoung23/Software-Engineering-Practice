#ifndef EVALUATION_H
#define EVALUATION_H

#include <string>
#include <exception.h>

using namespace std;

enum typeValue {INT, BOOL, STRING};

class evaluation
{
private:
    typeValue typeVal;
    string val_str;
    int val_int;
    bool val_bool;
public:
    evaluation(const typeValue &_typeVal, const string &_val_str);
    evaluation(const typeValue &_typeVal, const int &_val_int);
    evaluation(const typeValue &_typeVal, const bool &_val_bool);
    evaluation(const string &_val_str);
    evaluation(const int &_val_int);
    evaluation(const bool &_val_bool);

    string toString() const;
    bool toBoolean() const;
    bool iszero() const;
    int getVal() const;
    typeValue getType() const;

    friend evaluation operator+  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator-  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator*  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator/  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator>  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator<  (const evaluation &e1, const evaluation &e2);
    friend evaluation operator>= (const evaluation &e1, const evaluation &e2);
    friend evaluation operator<= (const evaluation &e1, const evaluation &e2);
    friend evaluation operator== (const evaluation &e1, const evaluation &e2);
};

evaluation operator+  (const evaluation &e1, const evaluation &e2);
evaluation operator-  (const evaluation &e1, const evaluation &e2);
evaluation operator*  (const evaluation &e1, const evaluation &e2);
evaluation operator/  (const evaluation &e1, const evaluation &e2);;
evaluation operator>  (const evaluation &e1, const evaluation &e2);
evaluation operator<  (const evaluation &e1, const evaluation &e2);
evaluation operator>= (const evaluation &e1, const evaluation &e2);
evaluation operator<= (const evaluation &e1, const evaluation &e2);
evaluation operator== (const evaluation &e1, const evaluation &e2);

#endif // EVALUATION_H
