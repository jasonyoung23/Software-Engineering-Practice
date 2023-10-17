#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    currentLine = 1;
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor DONE
    delete buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        cmd = "  ";
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend. DONE
    buffer -> goToLine(currentLine);
    while(true){
        string text;
        getline(cin, text);
        if(text == "."){
            break;
        }
        buffer -> appendLine(text);
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    buffer -> goToLine(currentLine);
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".") {
            break;
        }
        buffer -> insertLine(text);
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    if(line < 0 || line > buffer -> getTotalLine()){

        throw "Line number out of range";
    }
    else{
        currentLine = line;
        cout << buffer->moveToLine(line) << endl;
    }
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        if(cmd.substr(2).length() == 0){
            throw "Filename not specified";
        }
        else{
            cmdWrite(cmd.substr(2));
        }
        return;
    }

    // TODO: handle special case "1,$n". DONE
    int start, end;
    string what;
    char comma, type = ' ';

    if(cmd[0] == '1' && cmd[1] == ',' && cmd[2] == '$' && cmd[3] == 'n'){
        end = buffer -> getTotalLine();
        if(end == 0){
            throw "Number range error";
        }
        stringstream ss(cmd);
        ss >> start;
        cmdNumber(start,end);
    }

    else{
        stringstream ss(cmd);
        ss >> start;
        if (ss.eof()) {
            cmdNull(start);
            return;
        }
        ss >> comma >> end >> type;

        if(type == 'n'){
            if(start > end){
                throw "Number range error";
            }
            else if(buffer -> getTotalLine() < end){
                throw "Line number out of range";
            }
        }
        else if(type == 'd'){
            if(start > end){
                throw "Delete range error";
            }
            else if(buffer -> getTotalLine() < end){
                throw "Line number out of range";
            }
        }
        if (ss.good()) {
            if (type == 'n') {
                cmdNumber(start, end);
                return;
            } else if (type == 'd') {
                cmdDelete(start, end);
                return;
            }
        }

        throw "Bad/Unknown command";
    }
}
