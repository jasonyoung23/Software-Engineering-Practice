#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

struct Node {
    int x, y;
    int G, H;
    Node *parent;

    Node(int x, int y, Node *parent = nullptr) : x(x), y(y), parent(parent), G(0), H(0) {}

    int getScore() { return G + H; }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->resize(800, 600);
    this->setWindowTitle("Find Path!");

    // @TODO: write your code here

    ui->setupUi(this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct = new QAction(tr("&Open..."), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAct);

    pathFound = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Grid File"), "",
                                                    tr("Grid Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line = in.readLine();
            QStringList dimensions = line.split(' ');
            M = dimensions[0].toInt();
            N = dimensions[1].toInt();

            grid.resize(M);
            for(int i = 0; i < M; ++i){
                grid[i].resize(N);
            }
            for (int i = 0; i < M; ++i) {
                line = in.readLine();
                QStringList row = line.split(' ');
                for (int j = 0; j < N; ++j) {
                    grid[i][j] = row[j].toInt();
                }
            }

            requiredSafetyLevel = in.readLine().toInt();
        }
    }

    initializeGrid();
}

void MainWindow::initializeGrid(){
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    gridLabels.resize(M);

    for(int i = 0; i < M; ++i){
        gridLabels[i].resize(N);
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            QLabel *cell = new QLabel(this);
            cell->setFixedSize(50, 50);
            cell->setFrameStyle(QFrame::Box);
            cell->setAlignment(Qt::AlignCenter);
            if (grid[i][j] == 1) {
                cell->setStyleSheet("background-color: red;");
                cell->setText("1");
            } else {
                cell->setStyleSheet("background-color:  limegreen;");
                cell->setText(QString::number(grid[i][j]));
            }

            layout->addWidget(cell, i, j);
            gridLabels[i][j] = cell;
        }
    }
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    // @TODO: write your code here

    if(event->key() == Qt::Key_T) {
        calculateSafetyLevels();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                QString text = (grid[i][j] == 1) ? "0" : QString::number(safetyGrid[i][j]);
                gridLabels[i][j]->setText(text);
                gridLabels[i][j]->update();
            }
        }
        update();
    }
    else if(event->key() == Qt::Key_P){
        findPath();
    }
}

void MainWindow::calculateSafetyLevels() {
    safetyGrid.resize(M);

    for(int i = 0 ; i < M; ++i){
        safetyGrid[i].resize(N);
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            // If the cell is a fire pit, its safety level is 0
            if (grid[i][j] == 1) {
                safetyGrid[i][j] = 0;
            } else {
                // For passable cells, find the minimum distance to a fire pit
                int minDistance = INT_MAX;
                for (int x = 0; x < M; ++x) {
                    for (int y = 0; y < N; ++y) {
                        if (grid[x][y] == 1) {  // Check distance to each fire pit
                            int distance = abs(x - i) + abs(y - j);
                            minDistance = min(minDistance, distance);
                        }
                    }
                }
                safetyGrid[i][j] = minDistance;
            }
        }
    }
}

void MainWindow::showResult(){
    // @TODO: write your code here
}

void MainWindow::transferMatrix(){
    // @TODO: write your code here, subproblem one
    // You can add parameters to this method as needed
}

void MainWindow::findPath(){
    // @TODO: write your code here, subproblem two
    // You can add parameters to this method as needed
    QVector<Node*> openList;
    QVector<Node*> closedList;

    Node *startNode = new Node(0, 0);
    Node *endNode = new Node(M-1, N-1);
    openList.push_back(startNode);

    while (!openList.isEmpty()) {
        Node *currentNode = nullptr;
        for (Node *node : openList) {
            if (!currentNode || node->getScore() < currentNode->getScore()) {
                currentNode = node;
            }
        }

        if (currentNode->x == endNode->x && currentNode->y == endNode->y) {
            QVector<QPoint> path;
            while (currentNode) {
                path.push_back(QPoint(currentNode->x, currentNode->y));
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(), path.end());

            updatePathAppearance(path);
            pathFound = true;
            delete endNode;
            break;
        }

        openList.removeOne(currentNode);
        closedList.push_back(currentNode);

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; dir++) {
            int newX = currentNode->x + dx[dir];
            int newY = currentNode->y + dy[dir];

            if (newX >= 0 && newY >= 0 && newX < M && newY < N && grid[newX][newY] == 0) {
                bool inClosed = false;
                for (Node *closedNode : closedList) {
                    if (closedNode->x == newX && closedNode->y == newY) {
                        inClosed = true;
                        break;
                    }
                }
                if (inClosed) continue;


                int newG = currentNode->G + 10;
                int newH = (abs(endNode->x - newX) + abs(endNode->y - newY)) * 10;


                bool inOpen = false;
                for (Node *openNode : openList) {
                    if (openNode->x == newX && openNode->y == newY) {
                        inOpen = true;
                        if (newG < openNode->G) {
                            openNode->G = newG;
                            openNode->parent = currentNode;
                        }
                        break;
                    }
                }

                if (!inOpen) {
                    Node *node = new Node(newX, newY, currentNode);
                    node->G = newG;
                    node->H = newH;
                    openList.push_back(node);
                }
            }
        }

    }

    qDeleteAll(openList);
    qDeleteAll(closedList);

    if (!pathFound) {
        QMessageBox::information(this, tr("Error"), tr("Cannot find a path."));
    }
}

void MainWindow::updatePathAppearance(const QVector<QPoint>& path) {
    for (const QPoint& pathCell : path) {
        int i = pathCell.x();
        int j = pathCell.y();
        gridLabels[i][j]->setStyleSheet("background-color: blue;");
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    // @TODO: write your code here
}
