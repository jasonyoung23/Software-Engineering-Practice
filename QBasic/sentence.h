#ifndef SENTENCE_H
#define SENTENCE_H
#include <QString>
#include <QStringList>
#include <QDebug>
class Sentence
{
private:
    QString str; //10 REM APA
    QStringList listStr;//[REM] [APA]
    int no; //[10]
public:
    Sentence();
    Sentence(QString _str){
        this->str = _str;
        listStr = _str.split(" ");
        this->no = listStr[0].toInt();
    }
    QString getALine(){
        return str;
    }
    QStringList getListWords(){
        return listStr;
    }
    void printStr(){
        qDebug() << str ;
    }
    QString getWordAt(int n){
        return listStr.at(n);
    }
    int getLineNo(){
        return this->no;
    }
};

#endif // SENTENCE_H
