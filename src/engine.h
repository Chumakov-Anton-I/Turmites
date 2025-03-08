#ifndef ENGINE_H
#define ENGINE_H

#include <QStringList>
#include <QHash>
#include <QColor>

class QColor;

typedef QHash<QString, QString> TColorTable;
typedef QHash<QString, int> TRulesTable;

class Engine
{
public:
    enum Direction { North, East, South, West };
    enum Turn { Left, Front, Right, Uturn };
    explicit Engine();
    ~Engine() {}

    void setBehaviour(const QString &behaviour);
    void setBehaviour(const QStringList &behaviour);

    void move(const QColor &color, int dir);

    QColor color() const { return QColor(out_newColor); }
    int direction() const { return out_newDir; }

private:
    QString m_strBehaviour;         // e.g. "RRLL"
    QStringList m_listBehaviour; // list: "#RRGGBB:dir", ...
    TColorTable m_colorTable;
    TRulesTable m_rulesTable;

    QString out_newColor;
    int out_newDir;
};

#endif // ENGINE_H
