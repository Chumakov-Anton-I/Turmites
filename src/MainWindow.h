#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QTabWidget;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    QTabWidget *m_tabWidget;
};

#endif // MAINWINDOW_H
