#include "home.h"
#include "about.h"
#include "single.h"
#include "multi.h"
#include <QtWidgets>

home::home(QWidget *parent) : QWidget(parent){
    titleLabel = new QLabel(tr("连连看"));
    QFont titleFont("DengXian");
    titleFont.setPointSize(40);
    titleLabel -> setFont(titleFont);

    QFont buttonFont;
    buttonFont.setPointSize(13);

    singlePlayerButton = new QPushButton(tr("Single Player"));
    singlePlayerButton -> setFont(buttonFont);
    singlePlayerButton -> setCheckable(true);
    singlePlayerButton -> setFixedSize(QSize(200,60));

    multiPlayerButton = new QPushButton(tr("Multi Player"));
    multiPlayerButton -> setFont(buttonFont);
    multiPlayerButton -> setCheckable(true);
    multiPlayerButton -> setFixedSize(QSize(200,60));

    aboutButton = new QPushButton(tr("About"));
    aboutButton -> setFont(buttonFont);
    aboutButton -> setCheckable(true);
    aboutButton -> setFixedSize(QSize(200,60));

    exitButton = new QPushButton(tr("Exit"));
    exitButton -> setFont(buttonFont);
    exitButton -> setCheckable(true);
    exitButton -> setFixedSize(QSize(200,60));

    connect(singlePlayerButton, &QPushButton::clicked, this, &home::on_click_singlePlayerButton);
    connect(multiPlayerButton, &QPushButton::clicked, this, &home::on_click_multiPlayerButton);
    connect(aboutButton, &QPushButton::clicked, this, &home::on_click_aboutButton);
    connect(exitButton, &QPushButton::clicked, this, &home::on_click_exitButton);

    QVBoxLayout *myLayout = new QVBoxLayout;

    myLayout -> setSizeConstraint(QLayout::SetFixedSize);
    myLayout -> addWidget(titleLabel);
    myLayout -> addSpacing(50);
    myLayout -> addWidget(singlePlayerButton);
    myLayout -> addWidget(multiPlayerButton);
    myLayout -> addWidget(aboutButton);
    myLayout -> addWidget(exitButton);
    myLayout -> setSpacing(15);
    myLayout -> setContentsMargins(75, 75, 75, 75);

    setLayout(myLayout);

    setWindowTitle("Home");
    setFixedSize(100, 100);
}
void home::on_click_singlePlayerButton(){
    single *singleWindow = new single;

    singleWindow -> show();

    this -> close();
}
void home::on_click_multiPlayerButton(){
    multi *multiWindow = new multi;

    multiWindow -> show();

    this -> close();
}
void home::on_click_aboutButton(){
    about *aboutWindow = new about;

    aboutWindow -> show();

    this -> close();
}
void home::on_click_exitButton(){
    this -> close();
}
home::~home(){

}
