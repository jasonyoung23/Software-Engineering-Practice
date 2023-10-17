#ifndef MULTI_H
#define MULTI_H

#include <QtWidgets>

class multi : public QWidget{

    Q_OBJECT

public:
    multi(QWidget *parent = nullptr);
    ~multi();

private:
    QPushButton *exitMultiButton;
    QPushButton *newButton;
    QPushButton *loadButton;
    QLabel      *multiText;

    void on_click_newButton();
    void on_click_loadButton();
    void on_click_exitMultiButton();

};


#endif // MULTI_H
