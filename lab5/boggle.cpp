#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "lexicon.h"

using namespace std;

Lexicon d("../EnglishWords.txt");
Lexicon a;
Lexicon f;
/* d = dictionary   a = answer   f = words found */

void recursiveAnswer(int n, char table[100][100], int row, int col, bool flag[100][100], string &s)
{
    if (flag[row][col]){
        return;
    }
    else if(!d.containsPrefix(s)){
        return;
    }
    else{
        flag[row][col] = true;
        s.push_back(table[row][col]);

        if (s.length() >= 4 && d.contains(s)) {
            a.add(s);
        }

        if (row - 1 >= 0) { //go up
            recursiveAnswer(n, table, row - 1, col, flag, s);
            if (col - 1 >= 0) //diagonal left up
                recursiveAnswer(n, table, row - 1,col - 1, flag, s);
            if (col + 1 < n) //diagonal right up
                recursiveAnswer(n, table, row - 1,col + 1, flag, s);
        }

        if (row + 1 < n) { //go down
            recursiveAnswer(n, table, row + 1, col, flag, s);
            if (col - 1 >= 0) //diagonal left down
                recursiveAnswer(n, table, row + 1, col - 1, flag, s);
            if (col + 1 < n)//diagonal right down
                recursiveAnswer(n, table, row + 1, col + 1, flag, s);
        }

        if (col - 1 >= 0) //go left
            recursiveAnswer(n, table, row, col - 1, flag, s);

        if (col + 1 < n) //go right
            recursiveAnswer(n, table, row, col + 1, flag, s);

        flag[row][col] = false;
        s.pop_back();
    }

}

void searchAllAnswer(char table[100][100], int size) {
    bool flag[100][100];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            flag[i][j] = false;
        }
    }
    a.clear();
    string s;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            recursiveAnswer(size, table, i, j, flag, s);
        }
    }
}

void initTable(char table[100][100], int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            char tableLetter = 0;
            cin >> tableLetter;
            table[i][j] = tableLetter;
        }
    }
}

void printTable(char table[100][100], int size) {
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << table[i][j];
        }
        cout << endl;
    }
}

void computerPlay()
{
    set<string> compAns = a.toStlSet();
    int compScore = 0;

    f.mapAll([&](string s){ compAns.erase(s); });

    for (string scoreComp : compAns){
        compScore += scoreComp.length() -3;
    }

    cout << "Computer Score: " << compScore << endl << "Computer Words:";
    for (string foundComp : compAns) {
        transform(foundComp.begin(), foundComp.end(), foundComp.begin(), (int (*)(int))toupper);
        cout << " " << foundComp;
    }
}

int main() {
    int size = 0;
    int score = 0;
    char table[100][100];
    string playerAnswer;
    vector<string> playerList;

    cin >> size;
    initTable(table, size);
    searchAllAnswer(table, size);

    while (true) {
        printTable(table, size);
        cout << "Your Score: " << score << endl;
        cout << "Your Words:";
        for (int i = 0; i < playerList.size(); i++) {
            cout << " " << playerList[i];
        }
        cout << endl;
        cin >> playerAnswer;

        if(playerAnswer == "???"){
            computerPlay();
            break;
        }

        transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), (int (*)(int))tolower);

        if(playerAnswer.length() < 4){
            cout << playerAnswer << " is too short." << endl;
        }
        else if(!d.contains(playerAnswer)){
            cout << playerAnswer << " is not a word." << endl;
        }
        else if(!a.contains(playerAnswer)){
            cout << playerAnswer << " is not on board." << endl;
        }
        else if(f.contains(playerAnswer)){
            cout << playerAnswer << " is already found." << endl;
        }
        else{
            score += playerAnswer.length() - 3;
            f.add(playerAnswer);
            playerList.push_back(playerAnswer);
        }
    }
    return 0;
}
