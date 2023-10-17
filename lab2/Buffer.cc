#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    head = NULL;
    tail = NULL;
}

Buffer::~Buffer() {}

int Buffer::getTotalLine() {
    Node *temp = head;
    int numberOfLine = 0;
    while(temp != NULL){
        numberOfLine++;
        temp = temp -> getNext();
    }
    return numberOfLine;
}

void Buffer::goToLine(int num){
    currentLineNum = num-1;
}

void Buffer::writeToFile(const string &filename) const {
    ofstream f;
    f.open(filename, ios::binary);
    if(f.is_open()){
        Node *temp = head;
        while(temp != NULL){
            f << temp -> getData() << "\n";
            temp = temp -> getNext();
        }
    }
    f.close();

    ifstream f1;
    f1.open(filename, ios::binary);
    f1.seekg(0, ios::end);
    int file_size = f1.tellg();
    cout << file_size << " byte(s) written" << endl;
}

void Buffer::showLines(int from, int to) const {
    Node *temp = head;
    for(int i = 0; i < from-1 && temp != NULL; i++){
        temp = temp -> getNext();
    }
    if(temp != NULL){
        for(int i = from; i <= to && temp != NULL; i++){
            cout << i << "\t" << temp->getData() << endl;
            temp = temp->getNext();
        }
    }
}

void Buffer::deleteLines(int from, int to) {
    from--;
    to--;
    Node *temp = head;
    if(from == 0){
        int del = to - from + 1;
        for(int i = 0; i < del; i++){
            Node *t = head;
            head = t -> getNext();
            free(t);
        }
    }
    else{
        for (int i = 0; i < from - 1; i++) {
                temp = temp->getNext();
        }
        int del = to - from + 1;
        for (int i = 0; i < del; i++) {
            Node *t = temp->getNext();
            temp->setNext(t->getNext());
            free(t);
        }
    }
}

void Buffer::insertLine(const string &text){
    Node *newnode = new Node(text, NULL);
    if(currentLineNum == 0){
        if(head == NULL){
            head = newnode;
            tail = newnode;
        }
        else{
            newnode -> setNext(head);
            head = newnode;
        }
    }
    else{
        Node *temp = head;
        for(int i = 0; i < currentLineNum - 1 && temp != NULL; i++){
            temp = temp -> getNext();
        }
        Node *temp1 = temp -> getNext();
        temp -> setNext(newnode);
        newnode -> setNext(temp1);
    }
    currentLineNum++;
}

void Buffer::appendLine(const string &text){
    Node *newnode = new Node(text, NULL);
    if(currentLineNum == 0){
        if(head == NULL){
            head = newnode;
            tail = newnode;
        }
        else{
            newnode -> setNext(head);
            head = newnode;
        }
    }
    else{
        Node *temp = head;
        for(int i = 0; i < currentLineNum && temp -> getNext() !=NULL; i++){
            temp = temp -> getNext();
        }
        if(temp ->getNext() != NULL){
            Node *temp1 = temp -> getNext();
            temp -> setNext(newnode);
            newnode -> setNext(temp1);
        }
        else{
            temp -> setNext(newnode);
        }
    }
    currentLineNum++;
}

const string &Buffer::moveToLine(int idx) const {
    Node *temp = head;
    for(int i = 0; i < idx-1 && temp != NULL; i++){
        temp = temp -> getNext();
    }
    return temp -> getData();
}
