/*
 * CAnt.cpp
 * CAnt class implementation
 */

#include "CAnt.h"

CAnt::CAnt(QColor color, Direction dir)
    : SquareCell(0, 0, color), m_dir(dir), m_defColor(color)
{
    m_behaviour.insert(QColorConstants::Svg::black.name(), Left);
    m_behaviour.insert(QColorConstants::Svg::white.name(), Right);
}

void CAnt::reset(int x, int y, Direction dir)
{
    setPos(x, y);
    m_mapSize = m_map->mapSize();
    m_dir = dir;
    m_alive = true;
    setColor(m_defColor);
}

bool CAnt::move()
{
    if (!m_alive) return false; // do nothing if the ant isn't alive

    int X = x();
    int Y = y();
    QColor color = m_map->cell(X, Y)->color();
    int turn = m_behaviour.value(color.name());

    switch (m_dir) {
    case CAnt::North:
        if (turn == Left) {
            m_map->cell(X, Y)->setColor(Qt::white);
            m_dir = CAnt::West;
            X -= 1;
        } else /*if (turn == Right)*/ {
            m_map->cell(X, Y)->setColor(Qt::black);
            m_dir = CAnt::East;
            X += 1;
        }
        break;
    case CAnt::East:
        if (turn == Left) {
            m_map->cell(X, Y)->setColor(Qt::white);
            m_dir = CAnt::North;
            Y -= 1;
        } else /*if (turn == Right)*/ {
            m_map->cell(X, Y)->setColor(Qt::black);
            m_dir = CAnt::South;
            Y += 1;
        }
        break;
    case CAnt::South:
        if (turn == Left) {
            m_map->cell(X, Y)->setColor(Qt::white);
            m_dir = CAnt::East;
            X += 1;
        } else /*if (turn == Right)*/ {
            m_map->cell(X, Y)->setColor(Qt::black);
            m_dir = CAnt::West;
            X -= 1;
        }
        break;
    case CAnt::West:
        if (turn == Left) {
            m_map->cell(X, Y)->setColor(Qt::white);
            m_dir = CAnt::South;
            Y += 1;
        } else /*if (turn == Right)*/ {
            m_map->cell(X, Y)->setColor(Qt::black);
            m_dir = CAnt::North;
            Y -= 1;
        }
    }

    if (X < 0 || Y < 0 || X >= m_mapSize || Y >= m_mapSize)
    {
        if (m_cycled) {
            if (X < 0)  X = m_mapSize - 1;
            if (Y < 0)  Y = m_mapSize - 1;
            if (X == m_mapSize)  X = 0;
            if (Y == m_mapSize)  Y = 0;
        } else {
            m_alive = false;
            setColor(Qt::gray);
            return false;
        }
    }

    setPos(X, Y);
    return true;
}
