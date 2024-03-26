#include "buffer.h"

buffer::buffer(){
    head = new node(0, "head");
    tail = head;
    tail -> next = nullptr;
}

buffer::~buffer(){

}

bool buffer::isEmpty(){
    if(head == tail){
        return true;
    }
    else{
        return false;
    }
}

void buffer::newLine(int l, QString s){
    node *tmp = head;
    node *insert;

    while(tmp != tail){
        if(l > tmp -> next -> line){
            tmp = tmp -> next;
        }
        else if(l < tmp -> next -> line){
            insert = new node(l,s);
            insert -> next = tmp -> next;
            tmp -> next = insert;
            return;
        }
        else if(l == tmp -> next -> line){
            tmp = tmp -> next;
            tmp -> data = s;
            return;
        }
    }
    tmp -> next = new node(l,s);
    tail = tmp -> next;
    tail -> next = nullptr;
}

void buffer::clearBuf(){
    if(head == tail){
        return;
    }

    node *tmp;
    while (head != tail){
        tmp = head -> next;
        delete head;
        head = tmp;
    }
    tail -> next = nullptr;
}

QString buffer::lineList(){
    node *tmp = head;
    QString retValue = "";
    QString lineNumber;
    while(tmp != tail){
        tmp = tmp -> next;
        lineNumber = QString::number(tmp -> line);
        retValue.append(lineNumber + "\t" + tmp -> data + "\n");
    }
    return retValue;
}

vector<nodeT> buffer::parseLine(){
    vector<nodeT> dataNumber;
    node *tmp = head -> next;
    nodeT tmp_node(0, "");
    while(tmp != nullptr){
        tmp_node.line = tmp -> line;
        tmp_node.data = tmp -> data;
        dataNumber.push_back(tmp_node);
        tmp = tmp -> next;
    }
    return dataNumber;
}
