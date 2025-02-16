#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"

#include <QList>

typedef QList<QList<SquareCell *>> SquaredMap;

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    explicit CAnt(int size, Qt::GlobalColor color = Qt::red)
        : SquareCell(0, 0, size, color) {}

    void reset(int x, int y, Direction dir = North, Qt::GlobalColor color = Qt::red);
    void setMap(SquaredMap *map) { m_map = map; }
    void setCycled(bool on) { m_cycled = on; }

    bool move();

private:
    enum Turn { Left, Right };

    Direction m_dir;
    bool m_alive = true;
    bool m_cycled = false;
    SquaredMap *m_map;
};

#endif // CANT_H
