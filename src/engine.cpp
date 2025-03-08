#include "engine.h"

//#include <QColor>

Engine::Engine()
{
    /* Make default behaviour - Langton's Ant */
    m_colorTable.insert("#000000", "#FFFFFF");  // black => white
    m_colorTable.insert("#FFFFFF", "#000000");  // white => black
    m_rulesTable.insert("#000000", Left);  // black <=> left turn
    m_rulesTable.insert("#FFFFFF", Right);  // white <=> right turn
}

void Engine::setBehaviour(const QString &behaviour)
{
    m_strBehaviour = behaviour;
    m_colorTable.clear();
    m_rulesTable.clear();
    //
}

void Engine::setBehaviour(const QStringList &behaviour)
{
    m_listBehaviour = behaviour;
    m_colorTable.clear();
    m_rulesTable.clear();
    //
}

void Engine::move(const QColor &color, int dir)
{
    // bullshit
    QString s_color = color.name().toUpper();
    QString s_newColor = m_colorTable.value(s_color).toUpper();
    int turn = m_rulesTable.value(s_color);
    switch (turn) {
    case Left:
        if (--dir < North) dir = West;
        break;
    case Right:
        if (++dir > West) dir = North;
        break;
    case Uturn:
        if (++dir > West) dir = North;
        if (++dir > West) dir = North;
        break;
    default:    // Front <-> No turn
        break;
    }
    out_newColor = s_newColor;
    out_newDir = dir;
}
