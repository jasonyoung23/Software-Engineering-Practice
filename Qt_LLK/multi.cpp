#include "multi.h"
#include "home.h"
#include "mapmulti.h"
#include <QtWidgets>

multi::multi(QWidget *parent) : QWidget(parent){
    multiText = new QLabel(tr("Multiplayer"));

    QFont titleFont;
    titleFont.setPointSize(25);
    multiText -> setFont(titleFont);

    QFont buttonFont;
    buttonFont.setPointSize(13);

    newButton = new QPushButton(tr("New Game"));
    newButton -> setFont(buttonFont);
    newButton -> setCheckable(true);
    newButton -> setFixedSize(QSize(200,60));

    loadButton = new QPushButton(tr("Load Game"));
    loadButton -> setFont(buttonFont);
    loadButton -> setCheckable(true);
    loadButton -> setFixedSize(QSize(200,60));

    exitMultiButton = new QPushButton(tr("Back"));
    exitMultiButton -> setFont(buttonFont);
    exitMultiButton -> setCheckable(true);
    exitMultiButton -> setFixedSize(QSize(200,60));

    connect(newButton, &QPushButton::clicked, this, &multi::on_click_newButton);
    connect(loadButton, &QPushButton::clicked, this, &multi::on_click_loadButton);
    connect(exitMultiButton, &QPushButton::clicked, this, &multi::on_click_exitMultiButton);

    QVBoxLayout *myLayout = new QVBoxLayout;

    myLayout -> setSizeConstraint(QLayout::SetFixedSize);
    myLayout -> addWidget(multiText);
    myLayout -> addSpacing(50);
    myLayout -> addWidget(newButton);
    myLayout -> addWidget(loadButton);
    myLayout -> addWidget(exitMultiButton);
    myLayout -> setSpacing(15);
    myLayout -> setContentsMargins(75, 75, 75, 75);

    setLayout(myLayout);

    setWindowTitle("Multiplayer");
    setFixedSize(100, 100);
}

void multi::on_click_newButton(){

    DDQTMapMulti *gameWindow = new DDQTMapMulti;

    gameWindow -> show();

    this -> close();
}

void multi::on_click_loadButton(){
    DDQTMapMulti *gameWindow = new DDQTMapMulti;

    gameWindow -> loadMap();

    this -> close();
}

void multi::on_click_exitMultiButton(){
    home *homeWindow = new home;

    homeWindow -> show();

    this -> close();
}

multi::~multi(){

}
