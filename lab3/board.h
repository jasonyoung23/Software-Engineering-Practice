#pragma once
#include "stack.h"

class Board {
    // TODO DONE
    Stack *s;
    int hf[30];
    int ht[30];
    int n;
    int numDisc;
public:
    Board(int num_disk);
    ~Board();
    void draw();
    void move(int from, int to, bool log = true);
    bool win();
    void autoplay();
    void hanoi(int n, int A, int B, int C);
};
