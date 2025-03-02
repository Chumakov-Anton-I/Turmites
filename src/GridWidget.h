/**
 * GridWidget.h
 * The GridWidget class which describes grid map
 */

#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

#include "SquareCell.h"

class QPainter;
class QPixmap;
class QTimer;
class CAnt;

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    GridWidget(int size = 50, QWidget *parent = nullptr);
    ~GridWidget();

    void setSize(int size);
    void setStartDirection(int dir);
    void setAntBehaviour(const QString &behaviour);
    bool savePicture(const QString &filenName) const;

signals:
    void scoreChanged(int score);

public slots:
    void start();
    void stop();
    void reset();
    void changeTimeout(int timeout);
    void setCycled(bool on);

private:
    void initMap();
    void updateMap();
    void paintEvent(QPaintEvent *event);

    QRect getRect(const QPoint &pos);

    SquaredMap m_map;
    CAnt *m_ant;
    QPainter *m_painter;
    QPixmap *m_pixmap;
    QTimer *m_timer;
    int m_mapSize;      //! Current size of the map
    int m_cellSize = 4; //! [pix] Size of cells
    int m_timeout; // ms
    int m_score;        //! Current score
    int m_startDir;

    //enum Turn { Left, Right };

};

#endif // GRIDWIDGET_H
