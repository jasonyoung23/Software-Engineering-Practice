#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cmdLineEdit, SIGNAL(returnPressed()), this, SLOT(handleInput()), Qt::DirectConnection);
    connect(ui->btnLoadCode, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->btnClearCode, SIGNAL(clicked()), this, SLOT(clearCode()));
    connect(ui->btnRunCode, SIGNAL(clicked()), this, SLOT(runBegin()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayBuffer(){
    ui -> CodeDisplay -> setText(textBuffer -> lineList());
}

void MainWindow::clearVariable(){
    varTable.clear();
    stringTable.clear();
    typeTable.clear();
}

void MainWindow::clearCode()
{
    clearVariable();
    textBuffer -> clearBuf();
    ui->CodeDisplay->clear();
    ui->textBrowser->clear();
    ui->treeDisplay->clear();
}

void MainWindow::loadFile()
{
    clearCode();
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Files(*.txt)"));
    if(path.length() == 0) return;

    clearCode();
    QFile fileName(path);
    fileName.open(QIODevice::ReadWrite);
    QTextStream readEachLine(&fileName);
    while(!readEachLine.atEnd()){
        QString eachLine = readEachLine.readLine();
        string currentLine = eachLine.toStdString();
        int lineNumber = -1;

        vector<string> lineVec;
        stringstream ss;
        string buf;
        ss << currentLine;
        while(ss >> buf){
            lineVec.push_back(buf);
        }
        stringstream sstmp(lineVec[0]);
        sstmp >> lineNumber;
        inputLine(lineNumber, lineVec);
    }
}

void MainWindow::inputLine(int lineNumber, vector<string> &lineVec){
    string str = "";
    for(auto itr = lineVec.begin() + 1;itr != lineVec.end();++itr){
        str = str + " " + *itr;
    }

    QString dataQS = QString::fromStdString(str);
    textBuffer->newLine(lineNumber, dataQS);
    displayBuffer();
    return;
}

void MainWindow::runBegin()
{
    int index;
    try {
        if(textBuffer->isEmpty()) {
            ui->textBrowser->setText("Empty buffer");
            return;
        }

        vector<Syntax> SyntaxBlocks;
        vector<nodeT> NumData;
        QString displayBuffer="";
        vector<string> lineVec;
        string thisLine;
        int max;
        bool end;

        while(!end){
            if(max == index) break;

            lineVec.clear();
            thisLine = NumData[index].data.toStdString();

            int parsingIndex = 0;
            int maxIndex = thisLine.length();
            vector<string> lineVec;
            string buf = "";
            while(parsingIndex<maxIndex){
                buf = "";
                while(parsingIndex < maxIndex && thisLine[parsingIndex]!=' ' && thisLine[parsingIndex]!=','){
                    if(thisLine[parsingIndex]=='\"'){
                        if(!buf.empty()){
                            lineVec.push_back(buf);
                            buf="";
                        }
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                        while(parsingIndex < maxIndex && thisLine[parsingIndex]!='\"'){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        if(thisLine[parsingIndex]=='\"'){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        lineVec.push_back(buf);
                        std::cout << buf << std::endl;
                        buf = "";
                    }
                    else if(thisLine[parsingIndex]=='\''){
                        if(!buf.empty()){
                            lineVec.push_back(buf);
                            buf="";
                        }
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                        while(parsingIndex < maxIndex && thisLine[parsingIndex]!='\''){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        if(thisLine[parsingIndex]=='\''){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        lineVec.push_back(buf);
                        buf = "";
                    }
                    else{
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                    }
                }
                if(!buf.empty())
                    lineVec.push_back(buf);
                if(thisLine[parsingIndex]==' ' || thisLine[parsingIndex]==','){
                    parsingIndex++;
                }
            }

            if(lineVec.size()==0){
                index++;
                continue;
            }
            if(lineVec[0]=="REM"){
                remarkStatement remark(lineVec);
                index++;
                end = false;
            }
            else if(lineVec[0] == "INPUT" && lineVec.size()==2){

                for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
                    if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                        throw Exception("illegal variable");
                }
                if(lineVec[1][0]>='0'&&lineVec[1][0]<='9') throw Exception("illegal variable");

                handlingVar = lineVec[1];

                auto itr = typeTable.find(handlingVar);
                if(itr == typeTable.end()){
                    typeTable.insert(pair<string, variableType>(handlingVar, _INT));
                }
                else if(typeTable[handlingVar]==_STRING){
                    handlingVar = "";
                    throw Exception("input type error");
                }
                if(varTable.find(handlingVar)==varTable.end()){
                    varTable.insert(pair<string, int>(handlingVar, 0x7fffffff));
                    stringTable.insert(pair<string, string>(handlingVar, ""));
                }
                gotInput = false;
                handlingInput = true;

                ui->cmdLineEdit->setText("? ");
                ui->cmdLineEdit->setFocus();
                while(!gotInput){
                    QEventLoop loop;
                    QTimer::singleShot(300, &loop, SLOT(quit()));
                    loop.exec();
                    // after the slot function returns, the handling Value will be changed
                }

                varTable[handlingVar] = handlingVal;
                handlingVar = "";
                handlingVal = 0x7fffffff;
                ++index;
            }
            else if(lineVec[0]=="PRINT"){
                string tmp="";
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                for(auto itr = tmp.begin();itr!=tmp.end();++itr){
                    if(*itr=='='||*itr=='>'||*itr=='<'||*itr=='\''||*itr=='\"')
                        throw Exception("invalid expression after PRINT");
                }
                printStatement state(lineVec);
                displayBuffer = displayBuffer + QString::fromStdString(state.getValue()) + '\n';
                index++;
                end = false;
            }
            else if(lineVec[0]=="END" && lineVec.size()==1){
                end = true;
            }
            else if(lineVec[0]=="LET"){
                int count = 0;
                string tmp = "";
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                for(auto itr = tmp.begin();itr!=tmp.end();++itr){
                    if(*itr=='=') count++;
                    if(*itr=='>'||*itr=='<') throw Exception("invalid expression after LET");
                }
                if(count != 1) throw Exception("invalid expression after LET");
                string dfvar="";
                string exp = tmp;
                int len = exp.length();
                for(int i=0;i < len;++i){
                    if(!((exp[i]<='Z'&&exp[i]>='A')||(exp[i]<='z'&&exp[i]>='a')||(exp[i]<='9'&&exp[i]>='0')))
                        break;
                    dfvar+=exp[i];
                }
                auto itr=varTable.find(dfvar);
                if(itr==varTable.end()){
                    varTable.insert(pair<string,int>(dfvar, 0x7fffffff));
                    stringTable.insert(pair<string, string>(dfvar, ""));
                }

                letStatement state(lineVec);
                if(state.getSuccess()){
                    index++;
                    end = false;
                }
                else
                    throw Exception("invalid assignment");
            }
            else if(lineVec[0]=="GOTO" && lineVec.size()==2){
                gotoStatement state(lineVec);
                int nextLine = state.toLine();
                bool flag = false;
                for(int i = 0;i < max;++i){
                    if(NumData[i].line == nextLine){
                        index = i;
                        end = false;
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                    throw Exception("invalid line number after GOTO");
            }
            else if(lineVec[0]=="IF"){
                ifStatement state(lineVec);
                int nextLine = state.toLine().i;
                bool jump = state.toLine().b;
                bool flag = false;

                if(!jump){// do not jump
                    index++;
                    end = false;
                }
                else{// jump
                    for(int i = 0;i < max;++i){
                        if(NumData[i].line == nextLine){
                            index = i;
                            end = false;
                            flag = true;
                            break;
                        }
                    }
                    if(flag == false){
                        throw Exception("invalid line number after THEN");
                    }
                }
            }
            else throw Exception("invalid instruction");
        }
        ui->textBrowser->setText(displayBuffer);
        clearVariable();
    }
    catch(Exception &err) {
        string errInfo = "Error : ";
        errInfo = errInfo + err.info();
        clearVariable();
        ui->textBrowser->setText(QString::fromStdString(errInfo));
    }
    catch(std::invalid_argument&){
        clearVariable();
        ui->textBrowser->setText("Error : invalid argument");
        gotInput = true;
    }
    catch(std::out_of_range&){
        clearVariable();
        ui->textBrowser->setText("Error : out of range");
        gotInput = true;
    }
}

bool MainWindow::isString(string str) {
    int strlen = str.length();
    if(strlen > 2){
        if((str[0]=='\'' && str[strlen-1]=='\'')||(str[0]=='\"' && str[strlen-1]=='\"')){
            for(int i=1;i< strlen-1;++i){
                if(str[i]=='\''||str[i]=='\"')
                    return false;
            }
            return true;
        }
        else return false;
    }
    else return false;
}

string MainWindow::cutString(string str) {
    return str.substr(1, str.length()-2);
}

QString MainWindow::syntaxTree(expression *node){
    expression *tmp;
    queue<expression*> queueA;
    queue<expression*> queueB;
    char popNow = 'A';
    string output = "";
    int layer = 1;

    queueA.push(node);
    while(true){
        if(popNow == 'A'){
            if(queueA.empty()) break;
            tmp = queueA.front();
            queueA.pop();
            for(int i = 0;i < layer;i++){
                output = output + "   ";
            }
            output = output + tmp->toString() + '\n';
            if(tmp->type() == Comp){
                queueB.push(((compoundExpression*)tmp)->left);
                queueB.push(((compoundExpression*)tmp)->right);
            }
            if(queueA.empty()){
                popNow = 'B';
                layer++;
            }
        }
        else{
            if(queueB.empty()) break;
            tmp = queueB.front();
            queueB.pop();
            for(int i = 0;i < layer;i++){
                output = output + "   ";
            }
            output = output + tmp->toString() + '\n';
            if(tmp->type() == Comp){
                queueA.push(((compoundExpression*)tmp)->left);
                queueA.push(((compoundExpression*)tmp)->right);
            }
            if(queueB.empty()){
                popNow = 'A';
                layer++;
            }
        }
    }
    return QString::fromStdString(output);
}

void MainWindow::run()
{
    int index;
    try {
        if(textBuffer->isEmpty()) {
            ui->textBrowser->setText("Empty buffer");
            return;
        }

        vector<Syntax> SyntaxBlocks;
        vector<nodeT> NumData;
        QString displayBuffer="";
        vector<string> lineVec;
        string thisLine;
        int max;
        bool end;

        while(!end){
            if(max == index) break;

            lineVec.clear();
            thisLine = NumData[index].data.toStdString();

            int parsingIndex = 0;
            int maxIndex = thisLine.length();
            vector<string> lineVec;
            string buf = "";
            while(parsingIndex<maxIndex){
                buf = "";
                while(parsingIndex < maxIndex && thisLine[parsingIndex]!=' ' && thisLine[parsingIndex]!=','){
                    if(thisLine[parsingIndex]=='\"'){
                        if(!buf.empty()){
                            lineVec.push_back(buf);
                            buf="";
                        }
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                        while(parsingIndex < maxIndex && thisLine[parsingIndex]!='\"'){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        if(thisLine[parsingIndex]=='\"'){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        lineVec.push_back(buf);
                        std::cout << buf << std::endl;
                        buf = "";
                    }
                    else if(thisLine[parsingIndex]=='\''){
                        if(!buf.empty()){
                            lineVec.push_back(buf);
                            buf="";
                        }
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                        while(parsingIndex < maxIndex && thisLine[parsingIndex]!='\''){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        if(thisLine[parsingIndex]=='\''){
                            buf += thisLine[parsingIndex];
                            parsingIndex++;
                        }
                        lineVec.push_back(buf);
                        buf = "";
                    }
                    else{
                        buf += thisLine[parsingIndex];
                        parsingIndex++;
                    }
                }
                if(!buf.empty())
                    lineVec.push_back(buf);
                if(thisLine[parsingIndex]==' ' || thisLine[parsingIndex]==','){
                    parsingIndex++;
                }
            }

            if(lineVec.size()==0){
                index++;
                continue;
            }
            if(lineVec[0]=="REM"){
                remarkStatement remark(lineVec);
                index++;
                end = false;
            }
            else if(lineVec[0] == "INPUT" && lineVec.size()==2){

                for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
                    if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                        throw Exception("illegal variable");
                }
                if(lineVec[1][0]>='0'&&lineVec[1][0]<='9') throw Exception("illegal variable");

                handlingVar = lineVec[1];

                auto itr = typeTable.find(handlingVar);
                if(itr == typeTable.end()){
                    typeTable.insert(pair<string, variableType>(handlingVar, _INT));
                }
                else if(typeTable[handlingVar]==_STRING){
                    handlingVar = "";
                    throw Exception("input type error");
                }
                if(varTable.find(handlingVar)==varTable.end()){
                    varTable.insert(pair<string, int>(handlingVar, 0x7fffffff));
                    stringTable.insert(pair<string, string>(handlingVar, ""));
                }
                gotInput = false;
                handlingInput = true;

                ui->cmdLineEdit->setText("? ");
                ui->cmdLineEdit->setFocus();
                while(!gotInput){
                    QEventLoop loop;
                    QTimer::singleShot(300, &loop, SLOT(quit()));
                    loop.exec();
                    // after the slot function returns, the handling Value will be changed
                }

                varTable[handlingVar] = handlingVal;
                handlingVar = "";
                handlingVal = 0x7fffffff;
                ++index;
            }
            else if(lineVec[0]=="PRINT"){
                string tmp="";
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                for(auto itr = tmp.begin();itr!=tmp.end();++itr){
                    if(*itr=='='||*itr=='>'||*itr=='<'||*itr=='\''||*itr=='\"')
                        throw Exception("invalid expression after PRINT");
                }
                printStatement state(lineVec);
                displayBuffer = displayBuffer + QString::fromStdString(state.getValue()) + '\n';
                index++;
                end = false;
            }
            else if(lineVec[0]=="END" && lineVec.size()==1){
                end = true;
            }
            else if(lineVec[0]=="LET"){
                int count = 0;
                string tmp = "";
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                for(auto itr = tmp.begin();itr!=tmp.end();++itr){
                    if(*itr=='=') count++;
                    if(*itr=='>'||*itr=='<') throw Exception("invalid expression after LET");
                }
                if(count != 1) throw Exception("invalid expression after LET");
                string dfvar="";
                string exp = tmp;
                int len = exp.length();
                for(int i=0;i < len;++i){
                    if(!((exp[i]<='Z'&&exp[i]>='A')||(exp[i]<='z'&&exp[i]>='a')||(exp[i]<='9'&&exp[i]>='0')))
                        break;
                    dfvar+=exp[i];
                }
                auto itr=varTable.find(dfvar);
                if(itr==varTable.end()){
                    varTable.insert(pair<string,int>(dfvar, 0x7fffffff));
                    stringTable.insert(pair<string, string>(dfvar, ""));
                }

                letStatement state(lineVec);
                if(state.getSuccess()){
                    index++;
                    end = false;
                }
                else
                    throw Exception("invalid assignment");
            }
            else if(lineVec[0]=="GOTO" && lineVec.size()==2){
                gotoStatement state(lineVec);
                int nextLine = state.toLine();
                bool flag = false;
                for(int i = 0;i < max;++i){
                    if(NumData[i].line == nextLine){
                        index = i;
                        end = false;
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                    throw Exception("invalid line number after GOTO");
            }
            else if(lineVec[0]=="IF"){
                ifStatement state(lineVec);
                int nextLine = state.toLine().i;
                bool jump = state.toLine().b;
                bool flag = false;

                if(!jump){// do not jump
                    index++;
                    end = false;
                }
                else{// jump
                    for(int i = 0;i < max;++i){
                        if(NumData[i].line == nextLine){
                            index = i;
                            end = false;
                            flag = true;
                            break;
                        }
                    }
                    if(flag == false){
                        throw Exception("invalid line number after THEN");
                    }
                }
            }
            else throw Exception("invalid instruction");
        }
        ui->textBrowser->setText(displayBuffer);
        clearVariable();
    }
    catch(Exception &err) {
        string errInfo = "Error : ";
        errInfo = errInfo + err.info();
        clearVariable();
        ui->textBrowser->setText(QString::fromStdString(errInfo));
    }
    catch(std::invalid_argument&){
        clearVariable();
        ui->textBrowser->setText("Error : invalid argument");
        gotInput = true;
    }
    catch(std::out_of_range&){
        clearVariable();
        ui->textBrowser->setText("Error : out of range");
        gotInput = true;
    }
}

vector<Syntax> MainWindow::buildSyntaxTree()
{
    ui->treeDisplay->clear();
    vector<Syntax> SyntaxBlocks;

    if(textBuffer->isEmpty()) {
        return SyntaxBlocks;
    }

    vector<nodeT> NumData = textBuffer->parseLine();
    QString thisLineNumber;
    stringstream ss;
    vector<string> lineVec;
    string thisLine;
    string fragment;
    int index = 0;
    int max = NumData.size();

    QString syntax="";
    while(max != index){
        lineVec.clear();
        ss.clear();
        thisLine = NumData[index].data.toStdString();
        thisLineNumber = QString::number(NumData[index].line);
        ss << thisLine;
        while(ss >> fragment) lineVec.push_back(fragment);
        if(lineVec.size()==0){
            ++index;
            continue;
        }
        if(lineVec[0]=="REM"){
            remarkStatement remark(lineVec);
            syntax = thisLineNumber + " REM " + QString::fromStdString(remark.remark) + "\n";
            SyntaxBlocks.push_back(Syntax(true, syntax));
        }
        else if(lineVec[0]=="INPUT"){
            try{
                if(lineVec.size()==2){
                    for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
                        if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                            throw Exception("illegal variable");
                    }
                    if(lineVec[1][0]>='0'&&lineVec[1][0]<='9')
                        throw Exception("illegal variable");
                    syntax = thisLineNumber + " INPUT\n    " + QString::fromStdString(lineVec[1]) + "\n";
                    SyntaxBlocks.push_back(Syntax(true, syntax));
                }
                else
                    throw Exception("illegal variable");
            }
            catch(...){
                syntax = thisLineNumber+ " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else if(lineVec[0]=="INPUTS"){
            try{
                if(lineVec.size()==2){
                    for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
                        if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                            throw Exception("illegal variable");
                    }
                    if(lineVec[1][0]>='0'&&lineVec[1][0]<='9')
                        throw Exception("illegal variable");
                    syntax = thisLineNumber + " INPUTS\n    " + QString::fromStdString(lineVec[1]) + "\n";
                    SyntaxBlocks.push_back(Syntax(true, syntax));
                }
                else
                    throw Exception("illegal variable");
            }
            catch(...){
                syntax = thisLineNumber+ " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else if(lineVec[0]=="PRINT"){
            try{
                string tmp = "";
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                printStatement state(lineVec);
                expression *node = state.exp->root;
                syntax = thisLineNumber+ " PRINT\n" + syntaxTree(node);
                SyntaxBlocks.push_back(Syntax(true, syntax));
            }
            catch(...){
                syntax = thisLineNumber+ " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else if(lineVec[0]=="PRINTF"){
            syntax = thisLineNumber + " PRINTF\n";
            SyntaxBlocks.push_back(Syntax(true, syntax));
        }
        else if(lineVec[0]=="END" && lineVec.size()==1){
            syntax = thisLineNumber + " END\n";
            SyntaxBlocks.push_back(Syntax(true, syntax));
        }
        else if(lineVec[0]=="LET"){
            try{
                string tmp = "";
                int count = 0;
                for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
                    tmp = tmp + *itr;
                }
                for(auto itr = tmp.begin();itr!=tmp.end();++itr){
                    if(*itr=='=') count++;
                    if(*itr=='>'||*itr=='<') throw Exception("invalid expression after LET");
                }
                if(count != 1) throw Exception("invalid expression after LET");

                letStatement state(lineVec);
                expression *node = state.exp->root;
                syntax = thisLineNumber + " LET" + syntaxTree(node);
                SyntaxBlocks.push_back(Syntax(true, syntax));
            }
            catch(...){
                syntax = thisLineNumber+ " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else if(lineVec[0]=="GOTO"){
            if(lineVec.size()==2){
                syntax = thisLineNumber + " GOTO\n" + "     " + QString::fromStdString(lineVec[1]) + "\n";
                SyntaxBlocks.push_back(Syntax(true, syntax));
            }
            else{
                syntax = thisLineNumber + " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else if(lineVec[0]=="IF"){
            try{
                ifStatement state(lineVec);
                expression *node = state.exp->root;
                syntax = thisLineNumber + " IF THEN\n" + syntaxTree(node) + "   " + QString::number(state.nextLine) + "\n";
                SyntaxBlocks.push_back(Syntax(true, syntax));
            }
            catch(Exception &e){
                syntax = thisLineNumber + QString::fromStdString(e.info()) + "\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }

            catch(...){
                syntax = thisLineNumber + " ERROR\n";
                SyntaxBlocks.push_back(Syntax(false, syntax));
            }
        }
        else {
            syntax = thisLineNumber + " ERROR\n";
            SyntaxBlocks.push_back(Syntax(false, syntax));
        }
        index++;
    }
    return SyntaxBlocks;
}

void MainWindow::handleInput()
{
    try{
        HandlingInput();

    }catch(Exception &err){
        string errorInfo = "Error: ";
        errorInfo = errorInfo + err.info();
        ui -> textBrowser -> setText(QString::fromStdString(errorInfo));
    }
    catch(invalid_argument){
        ui -> textBrowser -> setText("Error: Invalid Argument");
    }
    catch(out_of_range){
        ui -> textBrowser -> setText("Error: Out of Range");
    }
}

void MainWindow::HandlingInput()
{
    if(handlingInput && ui->cmdLineEdit->text().length()==0){
        if(typeTable[handlingVar]==_INT){
            ui->textBrowser->setText("You must input a number begin with '? '");
            ui->cmdLineEdit->setText("? ");
        }
        return;
    }
    QString tmpQS = ui->cmdLineEdit->text();
    if(tmpQS.length()==0) return;
    ui->cmdLineEdit->clear();
    string tmpS = tmpQS.toStdString();


    int parsingIndex = 0;
    int maxIndex = tmpS.length();
    int lineNumber = -1;
    vector<string> lineVec;
    string buf = "";
    char delim = ' ';
    while(parsingIndex<maxIndex){
        buf = "";
        while(parsingIndex < maxIndex && tmpS[parsingIndex]!=delim){
            if(tmpS[parsingIndex]=='\"'){
                if(!buf.empty()){
                    if(buf!=string(buf.length(),' '))
                        lineVec.push_back(buf);
                    buf="";
                }
                buf += tmpS[parsingIndex];
                parsingIndex++;
                while(parsingIndex < maxIndex && tmpS[parsingIndex]!='\"'){
                    buf += tmpS[parsingIndex];
                    parsingIndex++;
                }
                if(tmpS[parsingIndex]=='\"'){
                    buf += tmpS[parsingIndex];
                    parsingIndex++;
                }
                lineVec.push_back(buf);
                buf = "";
            }
            else if(tmpS[parsingIndex]=='\''){
                if(!buf.empty()){
                    if(buf!=string(buf.length(),' '))
                        lineVec.push_back(buf);
                    buf="";
                }
                buf += tmpS[parsingIndex];
                parsingIndex++;
                while(parsingIndex < maxIndex && tmpS[parsingIndex]!='\''){
                    buf += tmpS[parsingIndex];
                    parsingIndex++;
                }
                if(tmpS[parsingIndex]=='\''){
                    buf += tmpS[parsingIndex];
                    parsingIndex++;
                }
                lineVec.push_back(buf);
                buf = "";
            }
            else{
                buf += tmpS[parsingIndex];
                parsingIndex++;
            }
        }
        if(!buf.empty())
            lineVec.push_back(buf);
        if(tmpS[parsingIndex]==delim){
            parsingIndex++;
        }
        if(lineVec[0]=="PRINTF")
            delim = ',';
    }

    stringstream sstmp(lineVec[0]);
    if(!(sstmp >> lineNumber)){
        if(lineVec[0] == "LET" || lineVec[0] == "PRINT" || lineVec[0] == "INPUT" || lineVec[0] == "PRINTF" || lineVec[0]=="INPUTS")
            action(lineVec);
        else if(handlingInput){
            if(typeTable[handlingVar]==_INT){// input
                if(lineVec[0] == "?" && lineVec.size() == 2) {
                    gotInput = true;
                    handlingInput = false;
                    handlingVal = std::stoi(lineVec[1]);
                }
                else{
                    ui->textBrowser->setText("You must input a number begin with '? '");
                    ui->cmdLineEdit->setText("? ");
                    return;
                }
            }
            else{ // inputs
                if(lineVec[0] == "??" && lineVec.size() == 2) {
                    if(isString(lineVec[1])){
                        gotInput = true;
                        handlingInput = false;
                        string trimmed = cutString(lineVec[1]);
                        handlingString = trimmed;
                    }
                    else{
                        ui->textBrowser->setText("not a string / string format error");
                        ui->cmdLineEdit->setText("?? ");
                        return;
                    }
                }
                else{
                    ui->textBrowser->setText("You must input a string begin with '?? '");
                    ui->cmdLineEdit->setText("?? ");
                    return;
                }
            }
        }
        else if(!handlingInput && lineVec[0] == "?"){
            throw Exception("unexpected input");
        }
        else if(!handlingInput && lineVec[0] == "??"){
            throw Exception("unexpected inputs");
        }
        else if(lineVec[0]=="LOAD" && lineVec.size() == 1)
            loadFile();
        else if(lineVec[0]=="RUN" && lineVec.size() == 1)
            runBegin();
        else if(lineVec[0]=="CLEAR" && lineVec.size() == 1)
            clearCode();
        else if(lineVec[0]=="QUIT" && lineVec.size() == 1)
            this->close();
        else
            throw Exception("invalid command "+tmpS);
    }
    else inputLine(lineNumber, lineVec);
}

void MainWindow::action(vector<string> &lineVec){
    string tmp = "";
    if(lineVec[0] == "PRINT"){
        for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
            tmp = tmp + *itr;
        }
        for(auto itr = tmp.begin();itr!=tmp.end();++itr){
            if(*itr=='='||*itr=='>'||*itr=='<') throw Exception("invalid expression after PRINT");
        }
        tree *expressionTree = new tree(tmp);
        string result = expressionTree->eval().toString();
        ui->textBrowser->setText(QString::fromStdString(result));
        delete expressionTree;
        return;
    }
    else if(lineVec[0] == "LET"){
        int count = 0;
        for(auto itr = lineVec.begin()+1;itr != lineVec.end();++itr){
            tmp = tmp + *itr;
        }
        for(auto itr = tmp.begin();itr!=tmp.end();++itr){
            if(*itr=='=') count++;
            if(*itr=='>'||*itr=='<') throw Exception("invalid expression after LET");
        }
        if(count != 1) throw Exception("invalid expression after LET");
        string dfvar="";
        string exp = tmp;
        int len = exp.length();
        for(int i=0;i < len;++i){
            if(!((exp[i]<='Z'&&exp[i]>='A')||(exp[i]<='z'&&exp[i]>='a')||(exp[i]<='9'&&exp[i]>='0')))
                break;
            dfvar+=exp[i];
        }
        auto itr=varTable.find(dfvar);
        if(itr==varTable.end()){
            varTable.insert(pair<string,int>(dfvar, 0x7fffffff));
        }

        tree *expressionTree = new tree(tmp);
        bool success= expressionTree->eval().toBoolean();
        if(!success)
            ui->textBrowser->setText("Syntax error");

        delete expressionTree;
        return;
    }
    else if(lineVec[0] == "INPUT"){
        if(lineVec.size()==1)
            throw Exception("need variable here");
        if(lineVec.size()>=3)
            throw Exception("too many arguments");
        for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
            if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                throw Exception("illegal variable");
        }
        if(lineVec[1][0]>='0'&&lineVec[1][0]<='9') throw Exception("illegal variable");

        handlingVar = lineVec[1];

        auto itr = typeTable.find(handlingVar);
        if(itr == typeTable.end()){
            typeTable.insert(pair<string, variableType>(handlingVar, _INT));
        }
        else if(typeTable[handlingVar]==_STRING){
            handlingVar = "";
            throw Exception("input type error");
        }
        if(varTable.find(handlingVar)==varTable.end()){
            varTable.insert(pair<string, int>(handlingVar, 0x7fffffff));
            stringTable.insert(pair<string, string>(handlingVar, ""));
        }
        gotInput = false;
        handlingInput = true;

        ui->cmdLineEdit->setText("? ");
        ui->cmdLineEdit->setFocus();
        while(!gotInput){
            QEventLoop loop;
            QTimer::singleShot(300, &loop, SLOT(quit()));
            loop.exec();
        }

        varTable[handlingVar] = handlingVal;
        handlingVar = "";
        handlingVal = 0x7fffffff;
    }
    else if(lineVec[0] == "INPUTS"){
        if(lineVec.size()==1)
            throw Exception("need variable here");
        if(lineVec.size()>=3)
            throw Exception("too many arguments");
        for(auto itr=lineVec[1].begin();itr!=lineVec[1].end();++itr){
            if(!(*itr>='a'&&*itr<='z') && !(*itr>='A'&& *itr<='Z') && !(*itr>='0'&&*itr<='9'))
                throw Exception("illegal variable");
        }
        if(lineVec[1][0]>='0'&&lineVec[1][0]<='9') throw Exception("illegal variable");

        handlingVar = lineVec[1];

        auto itr = typeTable.find(handlingVar);
        if(itr == typeTable.end()){
            typeTable.insert(pair<string, variableType>(handlingVar, _STRING));
        }
        else if(typeTable[handlingVar]==_INT){
            handlingVar = "";
            throw Exception("inputs type error");
        }
        if(stringTable.find(handlingVar)==stringTable.end()){
            varTable.insert(pair<string, int>(handlingVar, 0x7fffffff));
            stringTable.insert(pair<string, string>(handlingVar, ""));
        }
        gotInput = false;
        handlingInput = true;

        ui->cmdLineEdit->setText("?? ");
        ui->cmdLineEdit->setFocus();
        while(!gotInput){
            QEventLoop loop;
            QTimer::singleShot(300, &loop, SLOT(quit()));
            loop.exec();
        }

        stringTable[handlingVar] = handlingString;
        handlingVar = "";
        handlingString = "";
    }
}

void MainWindow::showSyntaxTree(vector<Syntax> &SyntaxBlocks){
    QString syntax = "";
    for(auto &itr:SyntaxBlocks){
        syntax += itr.syntaxTree;
    }
    ui->treeDisplay->setText(syntax);
}

void MainWindow::showSyntaxTreeLine(vector<Syntax> &SyntaxBlocks, int index){
    Syntax syntaxNode = SyntaxBlocks[index];
    QString syntax = syntaxNode.syntaxTree;
    ui->treeDisplay->setText(syntax);
}
