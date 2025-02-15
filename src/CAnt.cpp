#include "CAnt.h"

void CAnt::reset(int x, int y, Direction dir, Qt::GlobalColor color)
{
    setPos(x, y);
    m_dir = dir;
    m_alive = true;
    setColor(color);
}

bool CAnt::move()
{
    if (!m_alive) return false; // do nothing if the ant isn't alive

    int X = x();
    int Y = y();
    int turn;
    if (m_map->at(X).at(Y)->color() == Qt::black)
        turn = Left;
    else // if (m_map.at(X).at(Y)->color() == Qt::white)
        turn = Right;

    switch (m_dir) {
    case CAnt::North:
        if (turn == Left) {
            m_map->at(X).at(Y)->setColor(Qt::white);
            m_dir = CAnt::West;
            X -= 1;
        } else /*if (turn == Right)*/ {
            m_map->at(X).at(Y)->setColor(Qt::black);
            m_dir = CAnt::East;
            X += 1;
        }
        break;
    case CAnt::East:
        if (turn == Left) {
            m_map->at(X).at(Y)->setColor(Qt::white);
            m_dir = CAnt::North;
            Y -= 1;
        } else /*if (turn == Right)*/ {
            m_map->at(X).at(Y)->setColor(Qt::black);
            m_dir = CAnt::South;
            Y += 1;
        }
        break;
    case CAnt::South:
        if (turn == Left) {
            m_map->at(X).at(Y)->setColor(Qt::white);
            m_dir = CAnt::East;
            X += 1;
        } else /*if (turn == Right)*/ {
            m_map->at(X).at(Y)->setColor(Qt::black);
            m_dir = CAnt::West;
            X -= 1;
        }
        break;
    case CAnt::West:
        if (turn == Left) {
            m_map->at(X).at(Y)->setColor(Qt::white);
            m_dir = CAnt::South;
            Y += 1;
        } else /*if (turn == Right)*/ {
            m_map->at(X).at(Y)->setColor(Qt::black);
            m_dir = CAnt::North;
            Y -= 1;
        }
        break;
    }

    if (X < 0 || Y < 0 || X >= m_map->size() || Y >= m_map->size())
    {
        if (m_cycled) {
            if (X < 0)  X = m_map->size() - 1;
            if (Y < 0)  Y = m_map->size() - 1;
            if (X == m_map->size()) X = 0;
            if (Y == m_map->size()) Y = 0;
        } else {
            m_alive = false;
            setColor(Qt::gray);
            return false;
        }
    }

    setPos(X, Y);
    return true;
}
