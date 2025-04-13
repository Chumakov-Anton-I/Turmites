#include "engine.h"

#include <QBoxLayout>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "TabAnt.h"

Engine::Engine(QWidget *parent)
    : QDialog{parent}
{
    m_background = Qt::white;
    initModels();

    auto *topLayout = new QVBoxLayout;
    setLayout(topLayout);
    m_tabs = new QTabWidget;
    topLayout->addWidget(m_tabs);
    m_tabAnt = new TabAnt(&m_colors);
    m_tabs->addTab(m_tabAnt, tr("Ant"));

    auto *btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                      Qt::Horizontal);
    connect(btns, &QDialogButtonBox::accepted, this, &Engine::accept);
    connect(btns, &QDialogButtonBox::rejected, this, &Engine::reject);
    topLayout->addWidget(btns);
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

void Engine::accept()
{
    if (m_tabs->currentIndex() == 0)
        setBehaviour(m_tabAnt->rule());
    // else
    QDialog::accept();
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
}
