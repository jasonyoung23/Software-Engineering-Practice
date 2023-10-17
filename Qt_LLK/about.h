#ifndef ABOUT_H
#define ABOUT_H

#include <QtWidgets>
class about : public QWidget{

    Q_OBJECT

public:
    about(QWidget *parent = nullptr);
    ~about();

private:
    QPushButton *exitAboutButton;
    QLabel      *aboutText;

    void on_click_exitAboutButton();

};




#endif // ABOUT_H
