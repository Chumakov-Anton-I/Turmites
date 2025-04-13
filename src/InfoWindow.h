/**
 * About widget
 */

#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>

class InfoWindow : public QDialog
{
    Q_OBJECT
public:
    InfoWindow(QWidget *parent = nullptr);
};

#endif // INFOWINDOW_H
