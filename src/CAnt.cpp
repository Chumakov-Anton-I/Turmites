/* CAnt.cpp
 * CAnt class implementation
 */

#include "CAnt.h"
#include "engine.h"

CAnt::CAnt(Engine *engine, QColor color, Direction dir)
    : SquareCell(0, 0, color), m_engine(engine), m_dir(dir), m_defColor(color)
{
    //engine = new Engine;
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

    int ax = x();
    int ay = y();
    QColor color = m_map->cell(ax, ay)->color();
    m_engine->move(color, m_dir);
    m_map->cell(ax, ay)->setColor(m_engine->color());
    m_dir = m_engine->direction();

    switch (m_dir) {
    case North:
        --ay;
        break;
    case East:
        ++ax;
        break;
    case South:
        ++ay;
        break;
    case West:
        --ax;
    }

    if (ax < 0 || ay < 0 || ax >= m_mapSize || ay >= m_mapSize)
    {
        if (m_cycled) {
            if (ax < 0)  ax = m_mapSize - 1;
            if (ay < 0)  ay = m_mapSize - 1;
            if (ax == m_mapSize)  ax = 0;
            if (ay == m_mapSize)  ay = 0;
        } else {
            m_alive = false;
            setColor(Qt::gray);
            return false;
        }
    }

    setPos(ax, ay);
    return true;
}
