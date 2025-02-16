#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"

#include <QList>
#include <QHash>

typedef QList<QList<SquareCell *>> SquaredMap;

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    enum Turn { Left, Right };
    explicit CAnt(int size, Qt::GlobalColor color = Qt::red)
        : SquareCell(0, 0, size, color) {
        m_behavior.insert(Qt::black, Left);
        m_behavior.insert(Qt::white, Right);
    }

    void reset(int x, int y, Direction dir = North, Qt::GlobalColor color = Qt::red);
    void setMap(SquaredMap *map) { m_map = map; }
    void setCycled(bool on) { m_cycled = on; }
    void setBehavior(const QHash<Qt::GlobalColor, Turn> &behavior) { m_behavior = behavior; }

    bool move();

private:
    QHash<Qt::GlobalColor, Turn> m_behavior;

    Direction m_dir;
    bool m_alive = true;
    bool m_cycled = false;
    SquaredMap *m_map;
};

#endif // CANT_H
