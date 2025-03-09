#ifndef ENGINE_H
#define ENGINE_H

#include <QStringList>
#include <QHash>
#include <QColor>

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
    //void setBehaviour(const QStringList &behaviour);

    void move(QColor &color, int &dir);

    QColor color() const { return QColor(out_newColor); }
    int direction() const { return out_newDir; }

    QStringList predefList() const { return m_defModels; }  // not very good

private:
    QStringList m_defModels;

    QString m_strBehaviour;         // e.g. "RRLL"
    QStringList m_listBehaviour; // list: "#RRGGBB:dir", ...
    TColorTable m_colorTable;
    TRulesTable m_rulesTable;

    QString out_newColor;
    int out_newDir;
    QList<QColor> m_colors;

    QColor m_background;    // default color
};

#endif // ENGINE_H
