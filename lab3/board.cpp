#include "board.h"
#include "canvas.h"

Board::Board(int num_disk) {
    // TODO DONE
    numDisc = num_disk;
    s = new Stack[3];
    for(int i = num_disk; i >= 1; i--){
        s[0].push(i);
    }
    n=0;
}

Board::~Board() {
    // TODO DONE
    delete [] s;
}

void Board::draw() {
    Canvas canvas;
    canvas.reset();
    
    // TODO DONE
    for(int i = 0; i < canvas.WIDTH; i++){
        canvas.buffer[10][i] = '-';
        if(i == 5 ||i == 20 || i == 35){
            canvas.buffer[10][i] = '|';
        }
    }

    for(int i = 0; i < 10; i++){
        canvas.buffer[i][5] = '|';
        canvas.buffer[i][20] = '|';
        canvas.buffer[i][35] = '|';
    }

    for(int i = 0; i < 3; i++){
        int pos = 2*s[i].size()-1;
        Stack temp;
        while(!s[i].empty()){
            int discnum = s[i].top();
            temp.push(discnum);
            s[i].pop();
            int tower = 5 + i*15;
            for(int j = 0; j < discnum*2 + 1; j++){
                canvas.buffer[10-pos][tower - discnum +j] = '*';
            }
            pos -= 2;
        }
        while(!temp.empty()){
            s[i].push(temp.top());
            temp.pop();
        }
    }
    canvas.draw();
}

void Board::move(int from, int to, bool log) {
    // TODO DONE
    if(log == true){
        if (s[to].top() > s[from].top()){
            hf[n] = from;
            ht[n] = to;
            n++;
            s[to].push(s[from].top());
            s[from].pop();
        }
    }
    else{
        if (s[from].empty()==false) {
            int nd = s[from].top();
            s[to].push(nd);
            s[from].pop();
        }
    }
}

bool Board::win() {
    // TODO DONE
    if(s[1].size() == numDisc){
        return true;
    }
    else{
        return false;
    }
}

void Board::autoplay() {
    // TODO DONE
    while(n>0){
        cout << "Auto moving:" << ht[n-1]+1 << "->" << hf[n-1]+1 << endl;

        move(ht[n-1], hf[n-1], false);

        n--;
        draw();
    }
    hanoi(numDisc,0,1,2);
}

void Board::hanoi(int n, int A, int B, int C){
    if(n == 0){
        return;
    }
    hanoi(n-1,A,C,B);
    cout << "Auto moving:" << A+1 << "->" << B+1 << endl;
    move(A,B,false);
    draw();
    hanoi(n-1,C,B,A);
}