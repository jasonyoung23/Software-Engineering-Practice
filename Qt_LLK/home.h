#ifndef HOME_H
#define HOME_H

#include <QtWidgets>
class home : public QWidget{

    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();

private:
    QPushButton *singlePlayerButton;
    QPushButton *multiPlayerButton;
    QPushButton *aboutButton;
    QPushButton *exitButton;
    QLabel      *titleLabel;

    void on_click_singlePlayerButton();
    void on_click_multiPlayerButton();
    void on_click_aboutButton();
    void on_click_exitButton();

};




#endif // HOME_H
