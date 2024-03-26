#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include <QTime>

#include <vector>
#include <queue>
#include "buffer.h"
#include "variables.h"
#include "exception.h"
#include "tree.h"
#include "expression.h"
#include "statement.h"
#include "MyString.h"
#include "sentences.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Syntax{
    bool r;
    QString syntaxTree;

    Syntax(bool _r, QString _syntaxTree){
        r = _r;
        syntaxTree = _syntaxTree;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayBuffer();
    void action(vector<string> &lineVec);
    void inputLine(int lineNumber, vector<string> &lineVec);
    QString syntaxTree(expression *node);
    vector<Syntax> buildSyntaxTree();
    void clearVariable();

    bool isString(string str);
    string cutString(string str);
    void showVariable();
    void showSyntaxTree(vector<Syntax> &SyntaxBlocks);
    void showSyntaxTreeLine(vector<Syntax> &SyntaxBlocks, int index);

    void run();
    void HandlingInput();

public slots:
    void clearCode();
    void loadFile();
    void runBegin();
    void handleInput();


private:
    Ui::MainWindow *ui;
    buffer *textBuffer;
    string handlingVar;
    int handlingVal;
    string handlingString;
    bool gotInput;
    bool handlingInput;
};
#endif // MAINWINDOW_H
