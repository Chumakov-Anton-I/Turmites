#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <QRect>

class SquareCell
{
public:
    explicit SquareCell(int i, int j, int size, Qt::GlobalColor color = Qt::white)
        : m_X(i), m_Y(j), m_size(size), m_color(color) {}

    void setPos(int x, int y) { m_X = x; m_Y = y; }
    void setColor(Qt::GlobalColor color) { m_color = color; }

    QRect rect() const { return QRect(m_X*m_size, m_Y*m_size, m_size, m_size); }
    int x() const { return m_X; }
    int y() const { return m_Y; }
    Qt::GlobalColor color() const { return m_color; }

private:
    int m_X;
    int m_Y;
    int m_size;
    Qt::GlobalColor m_color;
};

#endif // SQUARECELL_H
