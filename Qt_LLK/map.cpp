#include "map.h"
#include "home.h"
#include "gameover.h"
#include <iostream>
#include <QTime>
#include <QPixmap>
#include <QtWidgets>
#include <string>

DDQTMap::DDQTMap(QWidget *parent)
    : QWidget(parent)
{
    srand((int)time(0));
    createMap();
    setWindowTitle(tr("SingleMap"));

    resize(800, 600);

}

DDQTMap::~DDQTMap()
{
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            delete mapLabels[i][j];
        }
    }
}

/*
 * 0 = wall
 * 1 = road
 * 2 = cheese
 * 3 = milk
 * 4 = steak
 * 5 = cheesein
 * 6 = milkin
 * 7 = steakin
 * 8 = time
 * 9 = shuffle
 * 10 = flash
 * 11 = jerry
 */

void DDQTMap::updateTimer(){
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

void DDQTMap::spawnPowerUp() {
    int x, y;
    int maxAttempts = 1000;

    while (maxAttempts > 0) {
        x = QRandomGenerator::global()->bounded(2, 20);
        y = QRandomGenerator::global()->bounded(2, 13);

        if (map[y][x] == 1) {
            int powerUpType = QRandomGenerator::global()->bounded(1, 4);

            switch (powerUpType) {
            case 1:
                map[y][x] = 8;
                break;
            case 2:
                map[y][x] = 9;
                break;
            case 3:
                map[y][x] = 10;
                break;
            default:
                break;
            }

            showMap();
            return;
        }

        maxAttempts--;
    }

}

bool DDQTMap::IsValidMatch(int a, int b, int c, int d) {
    if(map[b][a] == map[d][c]){
        return 1;
    }
    else{
        return 0;
    }
}

void DDQTMap::RemoveMatch(int x1, int y1, int x2, int y2) {
    map[y1][x1] = 1;
    map[y2][x2] = 1;
    counter++;
    newValue++;
    updateScore();
}

void DDQTMap::DeleteMatch(int x1, int y1, int x2, int y2, int t1, int t2){
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

void DDQTMap::move(int nextJx, int nextJy, char xy)
{
    map[jy][jx] = 1;
    if (xy == 'x'){
        jx = nextJx;
    }else{
        jy = nextJy;
    }
    map[jy][jx] = 11;
}

void DDQTMap::chooseItem(int nextJx, int nextJy, int itemIn, int itemFirst)
{
    map[nextJy][nextJx] = itemIn;
    if(clickCount == 0){
        type1 = itemFirst;
        x1 = nextJx;
        y1 = nextJy;
    }
    else if(clickCount == 1){
        type2 = itemFirst;
        x2 = nextJx;
        y2 = nextJy;
    }
    clickCount++;
}
void DDQTMap::playerGo(int nextJx, int nextJy, char xy){
    if (map[nextJy][nextJx] == 1){
        move(nextJx, nextJy, xy);
        showMap();
    }
    else if(map[nextJy][nextJx] == 2){
        chooseItem(nextJx, nextJy, 5, 2);
        showMap();
    }
    else if(map[nextJy][nextJx] == 3){
        chooseItem(nextJx, nextJy, 6, 3);
        showMap();
    }
    else if(map[nextJy][nextJx] == 4){
        chooseItem(nextJx, nextJy, 7, 4);
        showMap();
    }
    else if(map[nextJy][nextJx] == 8){
        move(nextJx, nextJy, xy);
        addTime();
    }
    else if(map[nextJy][nextJx] == 9){
        move(nextJx, nextJy, xy);
        shuffle();
    }
    else if(map[nextJy][nextJx] == 10){
        move(nextJx, nextJy, xy);
        flash();
    }
}

void DDQTMap::moveleft(int nextJx, int nextJy){
    if (nextJx >= 2){
        playerGo(nextJx, nextJy, 'x');
    }
}
void DDQTMap::moveup(int nextJx, int nextJy){
    if (nextJy >= 2){
        playerGo(nextJx, nextJy, 'y');
    }
}
void DDQTMap::movedown(int nextJx, int nextJy){
    if (nextJy <= 12){
        playerGo(nextJx, nextJy, 'y');
    }
}
void DDQTMap::moveright(int nextJx, int nextJy){
    if (nextJx <= 19){
        playerGo(nextJx, nextJy, 'x');
    }
}

void DDQTMap::keyPressEvent(QKeyEvent *event){
    if(!isPaused){
        int nextJy = jy;
        int nextJx = jx;

        if(event->key() == Qt::Key_S){
            nextJy++;
            movedown(nextJx, nextJy);
        }
        else if(event->key() == Qt::Key_W){
            nextJy--;
            moveup(nextJx, nextJy);
        }
        else if(event->key() == Qt::Key_D){
            nextJx++;
            moveright(nextJx, nextJy);
        }
        else if(event->key() == Qt::Key_A)
        {
            nextJx--;
            moveleft(nextJx, nextJy);
        }

        if(clickCount == 2){
            if(IsValidMatch(x1, y1, x2, y2)){
                RemoveMatch(x1, y1, x2, y2);
            }
            else{
                DeleteMatch(x1, y1, x2, y2, type1, type2);
            }
            clickCount = 0;
        }

        if(counter == 72){
            GameOver();
        }
    }
}

void DDQTMap::addTime(){
    timeLeft += 10;
    showMap();
    wPower = 0;
}

void DDQTMap::shuffle(){
    std::vector<int> remain;

    for (int i = 3; i <= 12; ++i) {
        for (int j = 3; j <= 19; ++j) {
            if(map[i][j] == 5){
                remain.push_back(2);
            }
            else if(map[i][j] == 6){
                remain.push_back(3);
            }
            else if(map[i][j] == 7){
                remain.push_back(4);
            }
            else if(map[i][j] != 0 && map[i][j] != 1 && map[i][j] != 8 && map[i][j] != 9 && map[i][j] != 10 && map[i][j] != 11 ) {
                remain.push_back(map[i][j]);
            }
        }
    }
    std::random_shuffle(remain.begin(), remain.end());

    for (auto index = 0u; index < remain.size(); ++index) {
        for (int i = 3; i <= 12; ++i) {
            for (int j = 3; j <= 19; ++j) {
                if(map[i][j] != 1 && map[i][j] != 8 && map[i][j] != 9 && map[i][j] != 10 && map[i][j] != 11){
                    map[i][j] = remain[index];
                    index++;
                }
                else{
                    continue;
                }
            }
        }
    }
    showMap();
    clickCount = 0;
    wPower = 0;
}

void DDQTMap::flash(){

    isFlash = true;

    showMap();
    wPower = 0;
}

void DDQTMap::GameOver(){

    gameOver *gameOverScreen = new gameOver;

    gameOverScreen -> show();

    this -> close();
}

void DDQTMap::randomMap(){
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
            }else{
                map[i][j] = tileTypes[currentTileType];
                currentTileType++;
            }
        }
    }
    map[2][2]=11;
}

void DDQTMap::showMap(){
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
            case 8:
                boxImage.load(":/resources/images/time.png");
                break;
            case 9:
                boxImage.load(":/resources/images/shuffle.png");
                break;
            case 10:
                boxImage.load(":/resources/images/flash.png");
                break;
            case 11:
                boxImage.load(":/resources/images/jerry.png");
                break;
            default:
                break;
            }
            mapLabels[i][j]->setPixmap(boxImage);
        }
    }
}

void DDQTMap::goFlash(int row, int kol){
    if (isFlash == true){
        map[jy][jx] = 1;
        jy = row; jx = kol;
        map[jy][jx] = 11; //jadi jerry
        isFlash = false;
    }
}

void DDQTMap::createMap(){

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout -> setSizeConstraint(QLayout::SetFixedSize);
    mainLayout -> setContentsMargins(75, 75, 75, 75);

    QGridLayout *mapLayout = new QGridLayout;
    mapLayout -> setSpacing(0);
    mainLayout -> addLayout(mapLayout);

    randomMap();

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            mapLabels[i][j] = new ClickableLabel(this);
            mapLabels[i][j] -> setFixedSize(QSize(50, 50));
            mapLabels[i][j] -> setScaledContents(true);
            mapLayout->addWidget(mapLabels[i][j], i-1 , j-1 );

            connect(mapLabels[i][j], &ClickableLabel::labelClicked, this, &DDQTMap::goFlash);
            mapLabels[i][j] -> setRowAndColumn(i, j);
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

    connect(exitSingleGame, &QPushButton::clicked, this, &DDQTMap::on_click_exitSingleGame);
    connect(saveButton, &QPushButton::clicked, this, &DDQTMap::on_click_saveButton);
    connect(pauseButton, &QPushButton::clicked, this, &DDQTMap::togglePause);

    timer = new QTimer(this);
    timer -> setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DDQTMap::updateTimer);
    timer -> start();
    timerLabel = new QLabel(this);
    timerLabel -> setFont(buttonFont);

    scoreLabel = new QLabel(this);
    scoreLabel -> setFixedSize(QSize(200,60));
    scoreLabel -> setFont(buttonFont);
    QTimer *scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, &DDQTMap::updateScore);
    scoreTimer -> start();

    powerUpTimer = new QTimer(this);
    connect(powerUpTimer, &QTimer::timeout, this, &DDQTMap::spawnPowerUp);
    powerUpTimer -> start(8000);

    buttonLayout -> addWidget(pauseButton);
    buttonLayout -> addWidget(saveButton);
    buttonLayout -> addWidget(exitSingleGame);
    buttonLayout -> addWidget(scoreLabel);
    buttonLayout -> addWidget(timerLabel);
}

void DDQTMap::on_click_exitSingleGame(){
    timer -> stop();
    home *homeScreen = new home;

    homeScreen -> show();

    this -> close();
}

void DDQTMap::on_click_saveButton(){
    timer -> stop();
    home *homeScreen = new home;

    homeScreen -> show();

    QString fname = "savefile.txt";
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
            }
        }

        out << newValue << endl;
        out << timeLeft << endl;

        file.close();
    }
    else {
        qDebug() << "Error";
        qDebug() << "File path:" << fname;
    }

    this -> close();
}

void DDQTMap::loadMap(){

    QString fname = "savefile.txt";
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
            map[y][x] = typeload;
        }

        in >> newValue;
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

void DDQTMap::togglePause(){
    isPaused = !isPaused;

    if(isPaused){
        timer -> stop();
        powerUpTimer -> stop();
    }
    else{
        timer -> start();
        powerUpTimer -> stop();
    }
}

void DDQTMap::updateScore(){

    scoreLabel -> setText("P1 Score:" + QString::number(newValue));
}
