#ifndef QTMAP_H
#define QTMAP_H

#include <QWidget>
#include <QtWidgets>
#include <QLabel>
#include <QTimer>
#include "clickablelabel.h"

#define MAX_MAP_SIZE 60
//! [0]
class DDQTMap : public QWidget
{
    Q_OBJECT

public:
    DDQTMap(QWidget *parent = nullptr);
    virtual ~DDQTMap();
    bool isMulti = false;
    void loadMap();

protected:

    void updateTimer();
    void createMap();
    void showMap();
    void randomMap();
    void createTextBox();
    void keyPressEvent(QKeyEvent *event);
    bool IsValidMatch(int a, int b, int c, int d);
    void RemoveMatch(int a, int b, int c, int d);
    void DeleteMatch(int a, int b, int c, int d, int t1, int t2);
    bool GameIsOver();
    void GameOver();
    void spawnPowerUp();
    void addTime();
    void shuffle();
    void flash();

    void move(int nextJx, int nextJy, char xy);
    void moveleft(int nextJx, int nextJy);
    void moveup(int nextJx, int nextJy);
    void movedown(int nextJx, int nextJy);
    void moveright(int nextJx, int nextJy);
    void playerGo(int nextJx, int nextJy, char xy);
    void chooseItem(int nextJx, int nextJy, int itemIn, int itemFirst);
    void goFlash(int row, int kol);


private:

    int n=20, m=13;
    int counter=0;
    int boxNum=3;
    int map[14][21];
    ClickableLabel* mapLabels[14][21];

    int jx=2, jy=2;
    int x1, y1, x2, y2, type1, type2;
    int clickCount = 0;
    int wPower;

    bool isPaused = false;
    bool isFlash = false;

    QPushButton *exitSingleGame;
    QPushButton *saveButton;
    QPushButton *pauseButton;

    void on_click_exitSingleGame();
    void on_click_saveButton();
    void togglePause();

    QTimer *timer;
    QLabel *timerLabel;
    int timeLeft = 121;

    QLabel *scoreLabel;
    void updateScore();
    int newValue = 0;

    QTimer *powerUpTimer;
};
//! [0]

#endif
