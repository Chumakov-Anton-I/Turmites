#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <QRect>
#include <QColor>
#include <QList>

class SquareCell
{
public:
    explicit SquareCell(int i, int j, int size, QColor color = Qt::white)
        : m_X(i), m_Y(j), m_size(size), m_color(color) {}

    void setPos(int x, int y) { m_X = x; m_Y = y; }
    void setColor(QColor color) { m_color = color; }

    QRect rect() const { return QRect(m_X*m_size, m_Y*m_size, m_size, m_size); }
    int x() const { return m_X; }
    int y() const { return m_Y; }
    QColor color() const { return m_color; }

private:
    int m_X;
    int m_Y;
    int m_size;
    QColor m_color;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////
// TEST
class SquareCellX
{
public:
    explicit SquareCellX(int i, int j, int size, QColor color = Qt::white)
        : m_X(i), m_Y(j), m_size(size), m_color(color) {}

    void setPos(int x, int y) { m_X = x; m_Y = y; }
    void setColor(QColor color) { m_color = color; }

    QRect rect() const { return QRect(m_X*m_size, m_Y*m_size, m_size, m_size); }
    int x() const { return m_X; }
    int y() const { return m_Y; }
    QColor color() const { return m_color; }

private:
    int m_X;
    int m_Y;
    int m_size;
    QColor m_color;
};
// end test

// // // //
typedef QList<QList<SquareCell *>> SquaredMap;

#endif // SQUARECELL_H
