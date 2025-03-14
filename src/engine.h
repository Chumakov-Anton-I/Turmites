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
    void setBehaviourByName(const QString &name);
    void move(QColor &color, int &direction);
    void reset();

    QStringList predefList() const { return m_defModels; }  // not very good
    QStringList predefListT() const { return QStringList(m_predefTurmites.keys()); }  // not very good too

protected:
    QStringList m_defModels;
    QList<QColor> m_colors;
    QHash<QString, TState> m_stateTable;
    unsigned m_cState;  // current state
    QColor m_background;    // default color
    QHash<QString, QStringList> m_predefTurmites;
};

#endif // ENGINE_H
