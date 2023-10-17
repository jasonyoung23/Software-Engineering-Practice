#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QWidget>
#include <QtWidgets>
#include <QLabel>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent), row(-1), col(-1) {}

protected:
    void mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            emit labelClicked(row, col);
        }
    }

public slots:
    void setRowAndColumn(int i, int j) {
        row = i;
        col = j;
    }

signals:
    void labelClicked(int row, int col);

private:
    int row;
    int col;
};

#endif // CLICKABLELABEL_H
