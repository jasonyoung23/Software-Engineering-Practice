#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QWidget>
#include <QtWidgets>
#include <QMessageBox>

#include <string>
#include <sstream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void transferMatrix();
    void findPath();
    void showResult();

    Ui::MainWindow *ui;
    void openFile();
    void initializeGrid();
    QVector<QVector<int>> grid;
    QVector<QVector<int>> safetyGrid;
    QVector<QVector<QLabel*>> gridLabels;
    int M;
    int N;
    int requiredSafetyLevel;
    void calculateSafetyLevels();

    bool pathFound;
    void updatePathAppearance(const QVector<QPoint>& x);

};
#endif // MAINWINDOW_H
