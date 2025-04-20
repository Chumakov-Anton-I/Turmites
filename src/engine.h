#ifndef ENGINE_H
#define ENGINE_H

#include <QDialog>
#include <QStringList>
#include <QHash>
#include <QColor>

class QPushButton;
class QTabWidget;
class QListWidget;
class QListWidgetItem;
//class TabAnt;

struct TState
{
    QString nColorStr;  // new color
    int direction;      // turn
    unsigned nState;    // new state
};

class Engine : public QDialog
{
    Q_OBJECT
public:
    enum Direction { North, East, South, West };
    enum Turn { Left, Front, Right, Uturn };

    explicit Engine(QWidget *parent = nullptr);

    //! Generates the table of states
    //! \param behaviour
    void setBehaviour(const QStringList &behaviour);

    void move(QColor &color, int &direction);
    void reset() { m_cState = 0; }

public slots:
    void loadAnt(QListWidgetItem *item);
    void loadTurmite(QListWidgetItem *item);

signals:
    void behaviourChanged(const QString &name);

private:
    void initModels();

    QTabWidget *m_tabs;
    QPushButton *m_btnAddItem;
    QPushButton *m_btnEditItem;
    QListWidget *m_listAnts;
    QListWidget *m_listTurmites;

    QList<QColor> m_colors;
    QHash<QString, TState> m_stateTable;    // table of states of transfers
    unsigned m_cState;  // current state
    QColor m_background;    // default color
    QHash<QString, QStringList> m_predefTurmites;
};

#endif // ENGINE_H
