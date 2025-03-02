/**
 * SquareCell.h
 * The SquareCell class describes an elementary cell of a map.
 */

#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <QPoint>
#include <QColor>
#include <QList>

class SquareCell
{
public:
    explicit SquareCell()
        : m_X(0), m_Y(0), m_color(Qt::white) {}
    SquareCell(int i, int j, QColor color = Qt::white)
        : m_X(i), m_Y(j), m_color(color) {}

    void setPos(int x, int y) { m_X = x; m_Y = y; }
    void setColor(QColor color) { m_color = color; }

    QPoint pos() const { return QPoint(m_X, m_Y); }
    int x() const { return m_X; }
    int y() const { return m_Y; }
    QColor color() const { return m_color; }

private:
    int m_X;
    int m_Y;
    QColor m_color;
};

typedef QList<QList<SquareCell *>> SquaredMap;

#endif // SQUARECELL_H
