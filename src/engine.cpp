#include "engine.h"

#include <QBoxLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QPushButton>

Engine::Engine(QWidget *parent)
    : QDialog{parent}
{
    m_background = Qt::white;

    auto *topLayout = new QVBoxLayout;
    setLayout(topLayout);
    // lists
    m_tabs = new QTabWidget;
    topLayout->addWidget(m_tabs);
    m_listAnts = new QListWidget;
    m_listTurmites = new QListWidget;
    m_tabs->addTab(m_listAnts, tr("Ants"));
    m_tabs->addTab(m_listTurmites, tr("Turmites"));
    // buttons
    auto *cmdLayout = new QHBoxLayout;
    topLayout->addLayout(cmdLayout);
    m_btnAddItem = new QPushButton("+");
    m_btnEditItem = new QPushButton("..");
    cmdLayout->addWidget(m_btnAddItem);
    cmdLayout->addWidget(m_btnEditItem);
    cmdLayout->addStretch(1);

    connect(m_listAnts, &QListWidget::itemDoubleClicked, this, &Engine::loadAnt);
    connect(m_listTurmites, &QListWidget::itemDoubleClicked, this, &Engine::loadTurmite);

    initModels();
    setBehaviour(QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0"); // init defaul model - Langton's ant
}

void Engine::setBehaviour(const QStringList &behaviour)
{
    reset();
    m_stateTable.clear();
    for (auto bi = behaviour.constBegin(); bi != behaviour.constEnd(); ++bi) {
        QStringList item = (*bi).split(":");
        m_stateTable.insert(item[0], TState{item[1], item[2].toInt(), item[3].toUInt()});
    }
}

void Engine::move(QColor &color, int &direction)
{
    QString key = QString("%1|%2").arg(m_cState).arg(color.name()); // todo: fix double string transformation
    TState state = m_stateTable.value(key);
    switch (state.direction) {
    case Left:
        if (--direction < North) direction = West;
        break;
    case Right:
        if (++direction > West) direction = North;
        break;
    case Uturn:
        if (++direction > West) direction = North;
        if (++direction > West) direction = North;
    default:    // no turn
        break;
    }
    color = QColor(state.nColorStr);    // update color
    m_cState = state.nState;    // update state
}

void Engine::loadAnt(QListWidgetItem *item)
{
    auto name = item->text();
    if (name == "LR") { // default model - Langton's ant
        setBehaviour(QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
        return;
    }
    auto subList = m_colors.sliced(0, name.length());
    subList << m_background;
    auto ci = subList.constBegin();
    int ddir;
    QStringList list;
    for (auto c = name.constBegin(); c != name.constEnd(); ++c) {
        if (*c == QChar('L'))
            ddir = Engine::Left;
        else if (*c == QChar('F'))
            ddir = Engine::Front;
        else if (*c == QChar('R'))
            ddir = Engine::Right;
        else if (*c == QChar('U'))
            ddir = Engine::Uturn;
        else    // this case is impossible, but...
            ddir = Engine::Front;
        list << QString("0|%1:%2:%3:0").arg(ci->name(), (++ci)->name()).arg(ddir);
    }
    setBehaviour(list);
    accept();
}

void Engine::loadTurmite(QListWidgetItem *item)
{
    auto data = item->data(Qt::UserRole).toStringList();
    setBehaviour(data);
    accept();
}

void Engine::initModels()
{
    using namespace QColorConstants::Svg;
    m_colors << m_background << blueviolet << crimson << orangered << limegreen << tomato << green
             << teal << cadetblue << chartreuse << coral << cornflowerblue << darkblue << darkcyan
             << darkgreen << darkmagenta << darkolivegreen << darkorange << darkorchid << darkred
             << darksalmon << darkseagreen << darkslateblue << darkturquoise << fuchsia << gold
             << darkviolet << deeppink << deepskyblue << dodgerblue << forestgreen << lawngreen
             << mediumorchid << lightsalmon << hotpink << darkslategray << indigo << peru << lime
             << lightcyan << lightgreen<< slateblue  << lightpink << lightseagreen << lightskyblue
             << magenta << maroon << mediumaquamarine << mediumpurple << royalblue << mediumseagreen
             << navy << salmon << turquoise << olive << mediumvioletred << navajowhite << orange
             << orchid << palegreen << palevioletred << peachpuff << pink << powderblue << purple
             << seagreen << skyblue << steelblue << blue << violet << yellow << yellowgreen;
    m_listAnts->clear();
    m_listTurmites->clear();
    // fill ants
    m_listAnts->addItems(QStringList() << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRLL"
                                       << "RRRLR" << "LRRRRRLLR" << "RRRLRRLRRR" << "RRLLLRRLRL"
                                       << "RRLLLRLLLLL" << "RRLRLLRRRRLL" << "RRLLLRLLLRLL"
                                       << "LLRRRLRLRLLR" << "RRLLLRLLLRRR");
    // fill turmites
    auto *item = new QListWidgetItem("Langton's ant");
    item->setData(Qt::UserRole, QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
    m_listTurmites->addItem(item);
    item = new QListWidgetItem("Demo");
    item->setData(Qt::UserRole, QStringList()
                        << QString("0|#000000:#ffffff:2:0") << QString("0|#ffffff:#ffffff:2:1")
                        << QString("1|#000000:#000000:1:0") << QString("1|#ffffff:#000000:1:1"));
    m_listTurmites->addItem(item);
}
