#include "TabAnt.h"

#include <QBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHeaderView>
#include <QValidator>
#include <QRegularExpression>

#include "engine.h"
#include "RuleValidator.h"

/*class RuleValidator : public QValidator
{
    QRegularExpression pattern;
public:
    RuleValidator(QObject *parent = nullptr) : QValidator(parent) {
        pattern.setPattern("[^LFRU]");
    }

    State validate(QString &str, int &) const {
        str = str.toUpper();
        if (str.contains(pattern))
            return Invalid;
        return Acceptable;
    }
};*/

TabAnt::TabAnt(QList<QColor> *colors, QWidget *parent)
    : QWidget{parent}, m_colors{colors}
{
    auto *topLayout = new QHBoxLayout;
    setLayout(topLayout);
    // list
    auto *listGroup = new QGroupBox(tr("Available behaviours"));
    listGroup->setMaximumWidth(164);
    topLayout->addWidget(listGroup);
    auto *listLayout = new QVBoxLayout;
    listGroup->setLayout(listLayout);
    m_ruleList = new QListWidget;
    listLayout->addWidget(m_ruleList);
    // table
    auto *tableGroup = new QGroupBox(tr("Settings"));
    topLayout->addWidget(tableGroup);
    auto *tableLayout = new QVBoxLayout;
    tableGroup->setLayout(tableLayout);
    // // edit
    auto *editLayout = new QHBoxLayout;
    tableLayout->addLayout(editLayout);
    editLayout->addWidget(new QLabel(tr("Behaviour")));
    m_editRule = new QLineEdit;
    editLayout->addWidget(m_editRule);
    m_btnAddRule = new QPushButton(tr("Add to list"));
    editLayout->addWidget(m_btnAddRule);
    // // table
    m_table = new QTableWidget;
    m_table->setRowCount(2);
    m_table->horizontalHeader()->hide();
    m_table->verticalHeader()->hide();  // don't show headers
    m_table->setGridStyle(Qt::NoPen);   // don't draw grid
    tableLayout->addWidget(m_table);

    connect(m_btnAddRule, &QPushButton::clicked, this, &TabAnt::addRuleToList);
    connect(m_ruleList, &QListWidget::itemDoubleClicked, this, &TabAnt::loadFromList);
    connect(m_editRule, &QLineEdit::textEdited, this, &TabAnt::generateTable);

    m_editRule->setValidator(new RuleValidator);

    init();
}

void TabAnt::init()
{
    m_ruleList->addItems(QStringList() << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRLL"
                                       << "RRRLR" << "LRRRRRLLR" << "RRRLRRLRRR" << "RRLLLRRLRL"
                                       << "RRLLLRLLLLL" << "RRLRLLRRRRLL" << "RRLLLRLLLRLL"
                                       << "LLRRRLRLRLLR" << "RRLLLRLLLRRR");
}

void TabAnt::generateTable(const QString &text)
{
    m_table->clear();
    m_table->setColumnCount(text.length());
    m_rule.clear();
    if (text.isEmpty())
        return;
    auto subList = m_colors->sliced(0, text.length());
    subList << subList.at(0);
    auto ci = subList.constBegin();
    int pos = 0; int dir = 0;
    foreach (auto lett, text) { // enumerate each letter
        m_table->setItem(0, pos, new QTableWidgetItem(lett));
        auto *item = new QTableWidgetItem;
        item->setBackground(*ci);
        m_table->setItem(1, pos, item);
        m_table->setColumnWidth(pos, 28);
        if (lett == QChar('L'))
            dir = Engine::Left;
        else if (lett == QChar('F'))
            dir = Engine::Front;
        else if (lett == QChar('R'))
            dir = Engine::Right;
        else if (lett == QChar('U'))
            dir = Engine::Uturn;
        else    // this case is impossible, but...
            dir = Engine::Front;
        m_rule << QString("0|%1:%2:%3:0").arg(ci->name(), (++ci)->name()).arg(dir);
        ++pos;
    }
    m_ruleName = text;
}

void TabAnt::loadFromList(QListWidgetItem *item)
{
    auto behaviour = item->text();
    m_editRule->setText(behaviour);
    generateTable(behaviour);
}

void TabAnt::addRuleToList()
{
    auto name = m_editRule->text();
    if (name.length() < 2) return; // too short
    if (m_ruleList->findItems(name, Qt::MatchFixedString).isEmpty()) {
        auto *item = new QListWidgetItem(name);
        item->setData(Qt::ToolTipRole, m_rule.join("\n"));
        m_ruleList->addItem(item);
    }
}
