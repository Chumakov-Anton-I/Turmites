#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>

class InfoWindow : public QWidget
{
    Q_OBJECT
public:
    InfoWindow(QWidget *parent = nullptr) : QWidget(parent) {}
};

#endif // INFOWINDOW_H
