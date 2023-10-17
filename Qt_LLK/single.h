#ifndef SINGLE_H
#define SINGLE_H

#include <QtWidgets>

class single : public QWidget{

    Q_OBJECT

public:
    single(QWidget *parent = nullptr);
    ~single();

private:
    QPushButton *exitSingleButton;
    QPushButton *newButton;
    QPushButton *loadButton;
    QLabel      *singleText;

    void on_click_newButton();
    void on_click_loadButton();
    void on_click_exitSingleButton();

};

#endif // SINGLE_H
