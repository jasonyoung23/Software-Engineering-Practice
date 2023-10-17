#include "home.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    home menu;
    menu.show();

    return a.exec();
}
