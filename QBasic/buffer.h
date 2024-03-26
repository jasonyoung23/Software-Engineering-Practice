#ifndef BUFFER_H
#define BUFFER_H

#include <QString>
#include <QTextStream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct node{
    int line;
    QString data;
    node *next;
    node(int l, QString s){
        line = l;
        data = s;
    }
};

struct nodeT{
    int line;
    QString data;

    nodeT(int l, QString s){
        line = l;
        data = s;
    }
};

class buffer
{
private:
    node *head;
    node *tail;
public:
    buffer();
    ~buffer();
    bool isEmpty();
    void newLine(int l, QString s);
    void clearBuf();
    QString lineList();
    vector<nodeT> parseLine();
};

#endif // BUFFER_H
