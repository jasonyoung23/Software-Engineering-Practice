#include <iostream>
#include <string>
#include <climits>

#include "board.h"

using namespace std;

int main() {
    while (true) {
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        string input;
        getline(cin, input);
        if (input == "Q") {
            break;
        }
        // TODO
        try{
            int fr, to;
            string input1, input2;
            int ndisc = stoi(input);

            if(ndisc >= 1 && ndisc <= 5){
                Board b(ndisc);
                while(b.win() == false){
                    b.draw();
                    cout << "Move a disk. Format: x y" << endl;
                    string inputinput;
                    getline(cin, inputinput);
                    input1 = inputinput.substr(0,1);
                    input2 = inputinput.substr(2);
                    if((input1 == "0" || input1 == "1" || input1 == "2" || input1 == "3") &&
                       (input2 == "0" || input2 == "1" || input2 == "2" || input2 == "3")) {
                        fr = input1[0]-'0';
                        to = input2[0]-'0';

                        if (fr == 0 && to == 0) {
                            b.autoplay();
                            cout << "Congratulations! You win!" << endl;
                        } else if ((fr <= 3 && fr >= 1) && (to <= 3 && to >= 1)) {
                            fr--;
                            to--;
                            b.move(fr, to, true);
                            if (b.win()){
                                b.draw();
                                cout << "Congratulations! You win!" << endl;
                                break;
                            }
                        }
                    }
                    inputinput.clear();
                }
            }
        }
        catch(...){

        }
        input.clear();
    }
    return 0;
}
