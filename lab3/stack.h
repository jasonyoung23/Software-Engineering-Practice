#pragma once

#include <cassert>
#include<iostream>

class Stack {
    // TODO DONE
    int *elem;
    int top_p;
    int maxSize;
 public:
    Stack() {
        // TODO DONE
        elem = new int[10];
        for(int i = 0; i < 10; i++){
            elem[i] = 0;
        }
        maxSize = 5;
        top_p = -1;
    }

    ~Stack() {
        // TODO DONE
        delete [] elem;
    }
    
    int size() {
        // TODO DONE
        return top_p + 1;
    }
    
    bool empty() {
        return size() == 0;
    }
    
    void push(int t) {
        // TODO DONE
        if(top_p < maxSize){
            elem[++top_p] = t;
        }
    }
    
    void pop() {
        // TODO DONE
        if(top_p >= 0){
            top_p--;
        }
    }
    
    int top() const {
        // TODO DONE
        if(top_p < 0){
            return 6;
        }
        return elem[top_p];
    }
};
