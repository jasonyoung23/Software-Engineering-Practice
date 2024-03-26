#ifndef SENTENCES_H
#define SENTENCES_H
#include <QString>
#include <QStringList>
#include <QVector>
#include "sentence.h"
class Sentences
{
private:
    QStringList listSentences;
    QVector<Sentence> VS;
public:
    Sentences();
    void clearSentence(){
        listSentences.clear();
        VS.clear();
    }
    void addSentence(QString str){
        //10 REM APA
        //=> addSentences(
        //20 INPUT X1
        VS.push_back(Sentence(str));
        sortVS();
        renewList();
    }
    void sortVS()
    {
        int nn = VS.size();
        for (int i=0; i<nn-1; i++){
            for (int j=i+1; j<nn; j++){
                if (VS[i].getLineNo() > VS[j].getLineNo()){
                    Sentence temp = VS[i];
                    VS[i] = VS[j];
                    VS[j] = temp;
                }
            }
        }
    }
    void renewList()
    {
        listSentences.clear();
        int nn = VS.size();
        for (int i=0; i<nn; i++){
            listSentences.append(VS[i].getALine());
        }
    }
    QStringList getListSentences(){
        return listSentences;
    }
    QString getSentence(int nomor){
        return listSentences.at(nomor);
    }
};

#endif // SENTENCES_H
