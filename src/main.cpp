/* The Langton's Ant and other turmites simulator */

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle(QString("Turmite"));
    window.setWindowIcon(QIcon(":/ico_app.png"));
    window.show();

    return app.exec();
}
