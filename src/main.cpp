/* The Langton's Ant and other turmites simulator */

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle(QString("Langton's Ant"));
    window.show();

    return app.exec();
}
