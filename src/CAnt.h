/**
 * CAnt.h
 * This class describes an ant and its behaviour
 */

#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"
#include "GridWidget.h"

//#include <QHash>
#include <QColor>

class GridWidget;
class Engine;

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    enum Turn { Left, Right };
    explicit CAnt(QColor color = Qt::red, Direction dir = North);

    void reset(int x, int y, Direction dir = North);
    void setMap(GridWidget *map) { m_map = map; }
    void setCycled(bool on) { m_cycled = on; }

    bool move();

private:
    GridWidget *m_map;
    //QHash<QString, int> m_behaviour;    // key = "#RRGGBB", value = Turn::value
    Engine *engine;

    int m_dir;
    bool m_alive = true;
    bool m_cycled = false;
    QColor m_defColor;  // Default color
    int m_mapSize;

};

#endif // CANT_H
