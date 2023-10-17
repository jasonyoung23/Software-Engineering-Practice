#include "single.h"
#include "home.h"
#include "map.h"
#include <QtWidgets>

single::single(QWidget *parent) : QWidget(parent){
    singleText = new QLabel(tr("Singleplayer"));

    QFont titleFont;
    titleFont.setPointSize(23);
    singleText -> setFont(titleFont);

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

    exitSingleButton = new QPushButton(tr("Back"));
    exitSingleButton -> setFont(buttonFont);
    exitSingleButton -> setCheckable(true);
    exitSingleButton -> setFixedSize(QSize(200,60));

    connect(newButton, &QPushButton::clicked, this, &single::on_click_newButton);
    connect(loadButton, &QPushButton::clicked, this, &single::on_click_loadButton);
    connect(exitSingleButton, &QPushButton::clicked, this, &single::on_click_exitSingleButton);

    QVBoxLayout *myLayout = new QVBoxLayout;

    myLayout -> setSizeConstraint(QLayout::SetFixedSize);
    myLayout -> addWidget(singleText);
    myLayout -> addSpacing(50);
    myLayout -> addWidget(newButton);
    myLayout -> addWidget(loadButton);
    myLayout -> addWidget(exitSingleButton);
    myLayout -> setSpacing(15);
    myLayout -> setContentsMargins(75, 75, 75, 75);

    setLayout(myLayout);

    setWindowTitle("Singleplayer");
    setFixedSize(100, 100);
}

void single::on_click_newButton(){
    DDQTMap *gameWindow = new DDQTMap;

    gameWindow -> show();

    this -> close();
}

void single::on_click_loadButton(){
    DDQTMap *gameWindow = new DDQTMap;

    gameWindow -> loadMap();

    this -> close();
}

void single::on_click_exitSingleButton(){
    home *homeWindow = new home;

    homeWindow -> show();

    this -> close();
}

single::~single(){

}
