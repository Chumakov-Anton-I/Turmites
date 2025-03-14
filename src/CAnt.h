/** CAnt.h
 *  This class describes an ant and its behaviour
 */

#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"
#include "GridWidget.h"

#include <QColor>

class GridWidget;
class Engine;

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    explicit CAnt(Engine *engine, QColor color = Qt::red, Direction dir = North);

    void reset(int x = 0 , int y = 0, Direction dir = North);
    void setMap(GridWidget *map) { m_map = map; }
    void setCycled(bool on) { m_cycled = on; }

    bool move();

private:
    GridWidget *m_map;
    Engine *m_engine;

    int m_dir;
    bool m_alive = true;
    bool m_cycled = false;
    QColor m_defColor;  // Default color
    int m_mapSize;

};

#endif // CANT_H
