#include "mapmulti.h"
#include "home.h"
#include "gameover.h"
#include <iostream>
#include <QTime>
#include <QPixmap>
#include <QtWidgets>

DDQTMapMulti::DDQTMapMulti(QWidget *parent)
    : QWidget(parent)
{
    srand((int)time(0));
    createMap();
    setWindowTitle(tr("MultiMap"));

    resize(800, 600);

}

DDQTMapMulti::~DDQTMapMulti()
{
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            delete mapLabels[i][j];
        }
    }
}

/*
 * 0 = bata
 * 1 = hitam
 * 2 = keju
 * 3 = botol
 * 4 = daging
 * 5 = kejuin
 * 6 = botolin
 * 7 = dagingin
 * 11 = jerry
 * 12 = tom
 */

void DDQTMapMulti::updateTimer(){
    timeLeft--;

    if(timeLeft > 0){
        int seconds = timeLeft;
        timerLabel -> setText("Time: " + QString("%1").arg(seconds,2,10));
    }
    else{
        timer -> stop();
        GameOver();
    }
}

bool DDQTMapMulti::IsValidMatch(int a, int b, int c, int d) {
    if(map[b][a] == map[d][c]){
        return 1;
    }
    else{
        return 0;
    }
}

void DDQTMapMulti::RemoveMatch(int x1, int y1, int x2, int y2, int player) {
    map[y1][x1] = 1;
    map[y2][x2] = 1;
    counter++;
    if(player == 11){
        newValueJerry++;
    }
    else if(player == 12){
        newValueTom++;
    }
    updateScore();
}

void DDQTMapMulti::DeleteMatch(int x1, int y1, int x2, int y2, int t1, int t2){
    if(t1 == 2){
        map[y1][x1] = 2;
    }
    else if(t1 == 3){
        map[y1][x1] = 3;
    }
    else if(t1 == 4){
        map[y1][x1] = 4;
    }

    if(t2 == 2){
        map[y2][x2] = 2;
    }
    else if(t2 == 3){
        map[y2][x2] = 3;
    }
    else if(t2 == 4){
        map[y2][x2] = 4;
    }
}

void DDQTMapMulti::keyPressEvent(QKeyEvent *event){
    if(!isPaused){
        int nextJy = jy;
        int nextJx = jx;
        int nextTy = ty;
        int nextTx = tx;

        if(event->key() == Qt::Key_S){
            nextJy++;
            if (nextJy <= 12){
                if (map[nextJy][nextJx] == 1){
                    map[jy][jx] = 1;
                    jy = nextJy;
                    map[jy][jx] = 11;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 2){
                    map[nextJy][nextJx] = 5;
                    if(clickCountJerry == 0){
                        type1 = 2;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 2;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 3){
                    map[nextJy][nextJx] = 6;
                    if(clickCountJerry == 0){
                        type1 = 3;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 3;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 4){
                    map[nextJy][nextJx] = 7;
                    if(clickCountJerry == 0){
                        type1 = 4;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 4;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_W){
            nextJy--;
            if (nextJy >= 2){
                if (map[nextJy][nextJx] == 1){
                    map[jy][jx] = 1;
                    jy = nextJy;
                    map[jy][jx] = 11;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 2){
                    map[nextJy][nextJx] = 5;
                    if(clickCountJerry == 0){
                        type1 = 2;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 2;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 3){
                    map[nextJy][nextJx] = 6;
                    if(clickCountJerry == 0){
                        type1 = 3;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 3;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 4){
                    map[nextJy][nextJx] = 7;
                    if(clickCountJerry == 0){
                        type1 = 4;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 4;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_D){
            nextJx++;
            if (nextJx <= 19){
                if (map[nextJy][nextJx] == 1){
                    map[jy][jx] = 1;
                    jx = nextJx;
                    map[jy][jx] = 11;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 2){
                    map[nextJy][nextJx] = 5;
                    if(clickCountJerry == 0){
                        type1 = 2;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 2;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 3){
                    map[nextJy][nextJx] = 6;
                    if(clickCountJerry == 0){
                        type1 = 3;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 3;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 4){
                    map[nextJy][nextJx] = 7;
                    if(clickCountJerry == 0){
                        type1 = 4;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 4;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_A){
            nextJx--;
            if (nextJx >= 2){
                if (map[nextJy][nextJx] == 1){
                    map[jy][jx] = 1;
                    jx = nextJx;
                    map[jy][jx] = 11;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 2){
                    map[nextJy][nextJx] = 5;
                    if(clickCountJerry == 0){
                        type1 = 2;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 2;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 3){
                    map[nextJy][nextJx] = 6;
                    if(clickCountJerry == 0){
                        type1 = 3;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 3;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
                else if(map[nextJy][nextJx] == 4){
                    map[nextJy][nextJx] = 7;
                    if(clickCountJerry == 0){
                        type1 = 4;
                        x1 = nextJx;
                        y1 = nextJy;
                    }
                    else if(clickCountJerry == 1){
                        type2 = 4;
                        x2 = nextJx;
                        y2 = nextJy;
                    }
                    clickCountJerry++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_K){
            nextTy++;
            if (nextTy <= 12){
                if (map[nextTy][nextTx] == 1){
                    map[ty][tx] = 1;
                    ty = nextTy;
                    map[ty][tx] = 12;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 2){
                    map[nextTy][nextTx] = 5;
                    if(clickCountTom == 0){
                        type3 = 2;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 2;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 3){
                    map[nextTy][nextTx] = 6;
                    if(clickCountTom == 0){
                        type3 = 3;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 3;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 4){
                    map[nextTy][nextTx] = 7;
                    if(clickCountTom == 0){
                        type3 = 4;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 4;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_I){
            nextTy--;
            if (nextTy >= 2){
                if (map[nextTy][nextTx] == 1){
                    map[ty][tx] = 1;
                    ty = nextTy;
                    map[ty][tx] = 12;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 2){
                    map[nextTy][nextTx] = 5;
                    if(clickCountTom == 0){
                        type3 = 2;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 2;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 3){
                    map[nextTy][nextTx] = 6;
                    if(clickCountTom == 0){
                        type3 = 3;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 3;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 4){
                    map[nextTy][nextTx] = 7;
                    if(clickCountTom == 0){
                        type3 = 4;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 4;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_L){
            nextTx++;
            if (nextTx <= 19){
                if (map[nextTy][nextTx] == 1){
                    map[ty][tx] = 1;
                    tx = nextTx;
                    map[ty][tx] = 12;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 2){
                    map[nextTy][nextTx] = 5;
                    if(clickCountTom == 0){
                        type3 = 2;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 2;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 3){
                    map[nextTy][nextTx] = 6;
                    if(clickCountTom == 0){
                        type3 = 3;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 3;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 4){
                    map[nextTy][nextTx] = 7;
                    if(clickCountTom == 0){
                        type3 = 4;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 4;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
            }
        }
        else if(event->key() == Qt::Key_J){
            nextTx--;
            if (nextTx >= 2){
                if (map[nextTy][nextTx] == 1){
                    map[ty][tx] = 1;
                    tx = nextTx;
                    map[ty][tx] = 12;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 2){
                    map[nextTy][nextTx] = 5;
                    if(clickCountTom == 0){
                        type3 = 2;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 2;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 3){
                    map[nextTy][nextTx] = 6;
                    if(clickCountTom == 0){
                        type3 = 3;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 3;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
                else if(map[nextTy][nextTx] == 4){
                    map[nextTy][nextTx] = 7;
                    if(clickCountTom == 0){
                        type3 = 4;
                        x3 = nextTx;
                        y3 = nextTy;
                    }
                    else if(clickCountTom == 1){
                        type4 = 4;
                        x4 = nextTx;
                        y4 = nextTy;
                    }
                    clickCountTom++;
                    showMap();
                }
            }
        }


        if(clickCountJerry == 2){
            if(IsValidMatch(x1, y1, x2, y2)){
                RemoveMatch(x1, y1, x2, y2, 11);
            }
            else{
                DeleteMatch(x1, y1, x2, y2, type1, type2);
            }
            clickCountJerry = 0;
        }

        if(clickCountTom == 2){
            if(IsValidMatch(x3, y3, x4, y4)){
                RemoveMatch(x3, y3, x4, y4, 12);
            }
            else{
                DeleteMatch(x3, y3, x4, y4, type3, type4);
            }
            clickCountTom = 0;
        }

        if(counter == 72){
            GameOver();
        }
    }
}

void DDQTMapMulti::GameOver(){

    gameOver *gameOverScreen = new gameOver;

    gameOverScreen -> show();

    this -> close();
}

void DDQTMapMulti::randomMap(){

    std::vector<int> tileTypes;
    for(int j = 1; j <= 24; ++j){
        for (int i = 2; i <= 4; ++i) {
            tileTypes.push_back(i);
            tileTypes.push_back(i);
        }
    }
    std::random_shuffle(tileTypes.begin(), tileTypes.end());

    int currentTileType = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(i == 1 || i == m || j == 1 || j == n){
                map[i][j] = 0;
            }else if((i==2 && j!=1 && j!=n)||(i==m-1 && j!=1 && j!=n)||(j==2 && i!=1 && i!=m-1)||(j==n-1 && i!=1 && i!=m-1)){
                map[i][j] = 1;
            } else{
                map[i][j] = tileTypes[currentTileType];
                currentTileType++;
            }
        }
    }
    map[2][2]=11;
    map[2][19]=12;
}

void DDQTMapMulti::showMap(){
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            QPixmap boxImage;
            switch(map[i][j]){
            case 0:
                boxImage.load(":/resources/images/wall.png");
                break;
            case 1:
                boxImage.load(":/resources/images/road.png");
                break;
            case 2:
                boxImage.load(":/resources/images/cheese.png");
                break;
            case 3:
                boxImage.load(":/resources/images/milk.png");
                break;
            case 4:
                boxImage.load(":/resources/images/steak.png");
                break;
            case 5:
                boxImage.load(":/resources/images/cheeseinvert.png");
                break;
            case 6:
                boxImage.load(":/resources/images/milkinvert.png");
                break;
            case 7:
                boxImage.load(":/resources/images/steakinvert.png");
                break;
            case 11:
                boxImage.load(":/resources/images/jerry.png");
                break;
            case 12:
                boxImage.load(":/resources/images/tom.png");
                break;
            default:
                break;
            }
            mapLabels[i][j]->setPixmap(boxImage);

        }
    }
}

void DDQTMapMulti::createMap(){

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout -> setSizeConstraint(QLayout::SetFixedSize);
    mainLayout -> setContentsMargins(75, 75, 75, 75);

    QGridLayout *mapLayout = new QGridLayout;
    mapLayout -> setSpacing(0);
    mainLayout -> addLayout(mapLayout);

    randomMap();

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            mapLabels[i][j] = new QLabel(this);
            mapLabels[i][j] -> setFixedSize(QSize(50, 50));
            mapLabels[i][j]->setScaledContents(true);
            mapLayout->addWidget(mapLabels[i][j], i-1 , j-1 );
        }
    }

    showMap();

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    mainLayout -> addLayout(buttonLayout);

    QFont buttonFont;
    buttonFont.setPointSize(13);

    pauseButton = new QPushButton(tr("Pause"));
    pauseButton->setFont(buttonFont);
    pauseButton->setCheckable(true);
    pauseButton->setFixedSize(QSize(200, 60));

    exitSingleGame = new QPushButton(tr("Exit"));
    exitSingleGame->setFont(buttonFont);
    exitSingleGame->setCheckable(true);
    exitSingleGame->setFixedSize(QSize(200, 60));

    saveButton = new QPushButton(tr("Save and Exit"));
    saveButton->setFont(buttonFont);
    saveButton->setCheckable(true);
    saveButton->setFixedSize(QSize(200, 60));

    connect(exitSingleGame, &QPushButton::clicked, this, &DDQTMapMulti::on_click_exitSingleGame);
    connect(saveButton, &QPushButton::clicked, this, &DDQTMapMulti::on_click_saveButton);
    connect(pauseButton, &QPushButton::clicked, this, &DDQTMapMulti::togglePause);

    timer = new QTimer(this);
    timer -> setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DDQTMapMulti::updateTimer);
    timer -> start();
    timerLabel = new QLabel(this);
    //timerLabel -> setFixedSize(QSize(160,60));
    timerLabel -> setFont(buttonFont);

    scoreJerry = new QLabel(this);
    scoreJerry -> setFixedSize(QSize(140,60));
    scoreJerry -> setFont(buttonFont);
    scoreTom = new QLabel(this);
    scoreTom -> setFixedSize(QSize(140,60));
    scoreTom -> setFont(buttonFont);
    QTimer *scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, &DDQTMapMulti::updateScore);
    scoreTimer -> start();

    buttonLayout -> addWidget(pauseButton);
    buttonLayout -> addWidget(saveButton);
    buttonLayout -> addWidget(exitSingleGame);
    buttonLayout -> addWidget(scoreJerry);
    buttonLayout -> addWidget(scoreTom);
    buttonLayout -> addWidget(timerLabel);
}

void DDQTMapMulti::on_click_exitSingleGame(){
    timer -> stop();
    home *homeScreen = new home;

    homeScreen -> show();

    this -> close();
}

void DDQTMapMulti::on_click_saveButton(){
    timer -> stop();
    home *homeScreen = new home;

    homeScreen -> show();

    QString fname = "savefilemulti.txt";
    QFile file(fname);

    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                if(map[i][j] == 0){
                    out << 0 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 1){
                    out << 1 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 2){
                    out << 2 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 3){
                    out << 3 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 4){
                    out << 4 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 5){
                    out << 5 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 6){
                    out << 6 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 7){
                    out << 7 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 8){
                    out << 8 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 9){
                    out << 9 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 10){
                    out << 10 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 11){
                    out << 11 << endl;
                    out << i << endl;
                    out << j << endl;
                }
                else if(map[i][j] == 12){
                    out << 12 << endl;
                    out << i << endl;
                    out << j << endl;
                }
            }
        }

        out << newValueJerry << endl;
        out << newValueTom << endl;
        out << timeLeft << endl;

        file.close();
    }
    else {
        qDebug() << "Error";
        qDebug() << "File path:" << fname;
    }
    this -> close();
}

void DDQTMapMulti::loadMap(){

    QString fname = "savefilemulti.txt";
    QFile file(fname);

    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        for(int k = 1; k <= 260; ++k){
            int typeload, y, x;
            in >> typeload;
            if(typeload == 5){
                typeload = 2;
            }
            else if(typeload == 6){
                typeload = 3;
            }
            else if(typeload == 7){
                typeload = 4;
            }
            in.readLine();
            in >> y;
            in.readLine();
            in >> x;
            in.readLine();
            if(typeload == 11){
                jx = x;
                jy = y;
            }
            else if(typeload == 12){
                tx = x;
                ty = y;
            }
            qDebug() << k << " " << y << " " << x << " " << typeload;
            map[y][x] = typeload;
        }

        in >> newValueJerry;
        in >> newValueTom;
        in >> timeLeft;
        file.close();
    }
    else{
        qDebug() << "Error";
        qDebug() << "File path:" << fname;
    }

    showMap();
    this -> show();
}

void DDQTMapMulti::togglePause(){
    isPaused = !isPaused;

    if(isPaused){
        timer -> stop();
    }
    else{
        timer -> start();
    }
}

void DDQTMapMulti::updateScore(){

    scoreJerry -> setText("P1 Score:" + QString::number(newValueJerry));
    scoreTom -> setText("P2 Score:" + QString::number(newValueTom));
}
