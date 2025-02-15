#ifndef CANT_H
#define CANT_H

#include "SquareCell.h"

class CAnt : public SquareCell
{
public:
    enum Direction {North, East, South, West};
    explicit CAnt(int size, Qt::GlobalColor color = Qt::red)
        : SquareCell(0, 0, size, color) {}

    void setDir(Direction dir) { m_dir = dir; }
    void setAlive(bool status) { m_alive = status; }

    Direction direction() const { return m_dir; }
    bool isAlive() const { return m_alive; }

private:
    Direction m_dir;
    bool m_alive = true;
};

#endif // CANT_H
