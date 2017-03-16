#include <QApplication>
#include <QtQuick/QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("../TimeLine/Test.qml"));
    view.show();

    return a.exec();
}
