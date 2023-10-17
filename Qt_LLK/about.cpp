#include "about.h"
#include "home.h"
#include <QtWidgets>

about::about(QWidget *parent) : QWidget(parent){
    aboutText = new QLabel(tr("How to Play: \n \n"
                              "1. Objective: Eliminate matching pairs of blocks to earn points. \n"
                              "2. Movement (RPG Mode): Control a character to activate and eliminate blocks. (WASD)\n"
                              "3. Activation: Move toward a block to activate it. \n"
                              "4. Elimination: Activate two matching blocks with a path of at most two bends. \n"
                              "5. Scoring: Earn points for each successful elimination. \n"
                              "6. Power-Ups (Single-Player): Collect items for special effects: \n"
                              "- '+1s': Add 30 seconds to the timer. \n"
                              "- 'Shuffle': Rearrange block positions. \n"
                              "- 'Flash': Move character to click location in 5 seconds. \n"
                              "7. Two-Player Mode : Compete for the highest score. \n"
                              "8. Timer: Game ends when time runs out. \n"
                              "9. Game Over: Ends with timer or no blocks. \n"
                              "10. Pause and Save/Load (Single-Player): Pause game or save progress. \n"
                              "11. Winning (Two-Player Mode): Highest score wins. \n"
                              "12. Start New Game: Return to the main menu to begin a new game. \n \n"
                              "Enjoy strategizing and maximizing your score by eliminating matching blocks!"));

    QFont titleFont;
    titleFont.setPointSize(12);
    aboutText -> setFont(titleFont);

    QFont buttonFont;
    buttonFont.setPointSize(13);

    exitAboutButton = new QPushButton(tr("Back"));
    exitAboutButton -> setFont(buttonFont);
    exitAboutButton -> setCheckable(true);
    exitAboutButton -> setFixedSize(QSize(200,60));

    connect(exitAboutButton, &QPushButton::clicked, this, &about::on_click_exitAboutButton);

    QVBoxLayout *myLayout = new QVBoxLayout;

    myLayout -> setSizeConstraint(QLayout::SetFixedSize);
    myLayout -> addWidget(aboutText);
    myLayout -> addSpacing(50);
    myLayout -> addWidget(exitAboutButton);
    myLayout -> setSpacing(15);
    myLayout -> setContentsMargins(75, 75, 75, 75);

    setLayout(myLayout);

    setWindowTitle("About");
    setFixedSize(100, 100);
}

void about::on_click_exitAboutButton(){
    home *homeWindow = new home;

    homeWindow -> show();

    this -> close();
}

about::~about(){

}
