#ifndef TABANT_H
#define TABANT_H

#include <QWidget>
#include <QList>

class QTableWidget;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QLineEdit;
class QColor;

class TabAnt : public QWidget
{
    Q_OBJECT
public:
    explicit TabAnt(QList<QColor> *colors, QWidget *parent = nullptr);

    QStringList rule() const { return m_rule; }

private:
    void init();
    QListWidget *m_ruleList;
    QTableWidget *m_table;
    QLineEdit *m_editRule;
    QString m_ruleName;
    QStringList m_rule;
    QPushButton *m_btnAddRule;
    QList<QColor> *m_colors;

private slots:
    void generateTable(const QString &text);
    void loadFromList(QListWidgetItem *item);
    void addRuleToList();
};

#endif // TABANT_H
