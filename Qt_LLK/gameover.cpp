#include "gameover.h"
#include "home.h"
#include <QtWidgets>

gameOver::gameOver(QWidget *parent) : QWidget(parent){
    gameOverText = new QLabel(tr("Game Over"));

    QFont titleFont;
    titleFont.setPointSize(23);
    gameOverText -> setFont(titleFont);

    QFont buttonFont;
    buttonFont.setPointSize(13);

    exitgameOverButton = new QPushButton(tr("Main Menu"));
    exitgameOverButton -> setFont(buttonFont);
    exitgameOverButton -> setCheckable(true);
    exitgameOverButton -> setFixedSize(QSize(200,60));

    connect(exitgameOverButton, &QPushButton::clicked, this, &gameOver::on_click_exitgameOverButton);

    QVBoxLayout *myLayout = new QVBoxLayout;

    myLayout -> setSizeConstraint(QLayout::SetFixedSize);
    myLayout -> addWidget(gameOverText);
    myLayout -> addSpacing(50);
    myLayout -> addWidget(exitgameOverButton);
    myLayout -> setContentsMargins(75, 75, 75, 75);

    setLayout(myLayout);

    setWindowTitle("Game Over");
    setFixedSize(100, 100);
}

void gameOver::on_click_exitgameOverButton(){
    home *homeWindow = new home;

    homeWindow -> show();

    this -> close();
}

gameOver::~gameOver(){

}
