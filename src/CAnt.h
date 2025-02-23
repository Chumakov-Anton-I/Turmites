#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"

#include <QHash>
#include <QColor>

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    enum Turn { Left, Right };
    explicit CAnt(int size, QColor color = Qt::red, Direction dir = North);

    void reset(int x, int y, Direction dir = North);
    void setMap(SquaredMap *map) { m_map = map; }
    void setCycled(bool on) { m_cycled = on; }

    bool move();

private:
    SquaredMap *m_map;
    QHash<QString, int> m_behaviour;    // key = "#RRGGBB", value = Turn::value

    Direction m_dir;
    bool m_alive = true;
    bool m_cycled = false;
    QColor m_defColor;
    int m_mapSize;
};

#endif // CANT_H
