#ifndef RULEBUILDER_H
#define RULEBUILDER_H

#include <QDialog>
#include <QStringList>
#include <QColor>
#include <QHash>

class QPushButton;
class Engine;
class TabAnt;

class RuleBuilder : public QDialog
{
    Q_OBJECT
public:
    explicit RuleBuilder(Engine *engine, QWidget *parent = nullptr); //++

    void setAntBehaviour(const QString &behaviour);
    void setBehaviourByName(const QString &name);

    QStringList predefinedModels() const { return m_builtinModels; }
    QStringList predefinedTurmites() const { return QStringList(m_builtinTurmites.keys()); }

private:
    void initModels();  //++

    TabAnt *m_tabAnt;   //++

    QPushButton *m_btnAddState; //++
    QPushButton *m_btnAddColor; //++

    QStringList m_builtinModels;
    QList<QColor> m_colors;
    QColor m_bgColor1;
    QHash<QString, QStringList> m_builtinTurmites;

    Engine *m_engine;

    void createTable();
};

#endif // RULEBUILDER_H
