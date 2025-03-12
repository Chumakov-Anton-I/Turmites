#ifndef ENGINE_H
#define ENGINE_H

#include <QStringList>
#include <QHash>
#include <QColor>

struct TState
{
    QString nColorStr;  // new color
    int direction;      // turn
    unsigned nState;    // new state
};

class Engine
{
public:
    enum Direction { North, East, South, West };
    enum Turn { Left, Front, Right, Uturn };

    Engine();
    //~Engine() {}

    void setBehaviour(const QString &behaviour);
    void setBehaviour(const QStringList &behaviour);
    void move(QColor &color, int &direction);

    QStringList predefList() const { return m_defModels; }  // not very good

protected:
    QStringList m_defModels;
    QList<QColor> m_colors;
    QHash<QString, TState> m_stateTable;
    unsigned m_cState;  // current state
    QColor m_background;    // default color
};

#endif // ENGINE_H
