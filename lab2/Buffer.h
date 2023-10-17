#pragma once

#include <string>
#include <iostream>
using namespace std;

class Node{
private:
    string data;
    Node *next;
public:
    Node();
    Node(string dt, Node *nxt){
        data = dt;
        next = nxt;
    }
    ~Node();
    const string &getData() const{
        return data;
    }
    Node* getNext(){
        return next;
    }
    void setNext(Node *nxt){
        next = nxt;
    }
    void display(){
        cout << data << "->";
    }
};

class Buffer {
private:
    // TODO: add a List here for storing the input lines DONE
    Node *head, *tail;
    int currentLineNum;

public:
    Buffer();
    ~Buffer();

    int getTotalLine();
    void goToLine(int num);

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) const;

    void showLines(int from, int to) const;
    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
