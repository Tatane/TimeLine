#include <QApplication>
#include "mainwin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWin mainWin;
    mainWin.show();

    return app.exec();
}
