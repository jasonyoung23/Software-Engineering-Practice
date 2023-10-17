#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QtWidgets>

class gameOver : public QWidget{

    Q_OBJECT

public:
    gameOver(QWidget *parent = nullptr);
    ~gameOver();

private:
    QPushButton *exitgameOverButton;
    QLabel      *gameOverText;

    void on_click_exitgameOverButton();

};

#endif // GAMEOVER_H
