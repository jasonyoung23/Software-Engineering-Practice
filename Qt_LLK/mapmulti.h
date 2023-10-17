#ifndef MAPMULTI_H
#define MAPMULTI_H

#include <QWidget>
#include <QtWidgets>
#include <QLabel>
#include <QTimer>

#define MAX_MAP_SIZE 60
//! [0]
class DDQTMapMulti : public QWidget
{
    Q_OBJECT

public:
    DDQTMapMulti(QWidget *parent = nullptr);
    virtual ~DDQTMapMulti();
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
    void RemoveMatch(int a, int b, int c, int d, int player);
    void DeleteMatch(int a, int b, int c, int d, int t1, int t2);
    bool GameIsOver();
    void GameOver();

private:
    int n=20, m=13;
    int counter=0;
    int boxNum=3;
    int map[14][21];
    QLabel* mapLabels[14][21];

    int jx=2, jy=2;
    int tx=19, ty=2;
    int x1, y1, x2, y2, type1, type2;
    int x3, y3, x4, y4, type3, type4;
    int clickCountJerry = 0;
    int clickCountTom = 0;

    bool isPaused = false;

    QPushButton *exitSingleGame;
    QPushButton *saveButton;
    QPushButton *pauseButton;

    void on_click_exitSingleGame();
    void on_click_saveButton();
    void togglePause();

    QTimer *timer;
    QLabel *timerLabel;
    int timeLeft = 121;

    QLabel *scoreJerry;
    QLabel *scoreTom;
    void updateScore();
    int newValueJerry = 0;
    int newValueTom = 0;
};

#endif // MAPMULTI_H
