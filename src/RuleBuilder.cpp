#include "RuleBuilder.h"

#include <QBoxLayout>
#include <QTabWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QDialogButtonBox>

#include "engine.h"
#include "TabAnt.h"

RuleBuilder::RuleBuilder(Engine *engine, QWidget *parent)
    : QDialog(parent), m_engine(engine)
{
    m_bgColor1 = Qt::white;
    initModels();
    // create widgets
    auto *topLayout = new QVBoxLayout;
    setLayout(topLayout);
    auto *tabs = new QTabWidget;
    topLayout->addWidget(tabs);
    m_tabAnt = new TabAnt(&m_colors);
    tabs->addTab(m_tabAnt, tr("Ant"));
    //
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                         Qt::Horizontal);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    topLayout->addWidget(buttons);

    setAntBehaviour("RL");
}

void RuleBuilder::setAntBehaviour(const QString &behaviour)
{
    if (behaviour == "RL") {    // default model is Langton's ant
        m_engine->setBehaviour(QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
        return;
    }
    QList<QColor> subList = m_colors.sliced(0, behaviour.size());    // copy sublist of colors
    subList << m_bgColor1;  // add 1st color to cycle enumerating
    auto ci = subList.constBegin();
    int ddir;
    QStringList list;
    for (auto c = behaviour.constBegin(); c != behaviour.constEnd(); ++c) {
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
    m_engine->setBehaviour(list);
}

void RuleBuilder::setBehaviourByName(const QString &name)
{
    m_engine->setBehaviour(m_builtinTurmites.value(name));
}

void RuleBuilder::initModels()
{
    m_builtinModels << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRLL" << "RRRLR" << "LRRRRRLLR"
                    << "RRRLRRLRRR" << "RRLLLRRLRL" << "RRLLLRLLLLL" << "RRLRLLRRRRLL" << "RRLLLRLLLRLL"
                    << "LLRRRLRLRLLR" << "RRLLLRLLLRRR";// << "Custom";
    //Turn: Left = 0, Front = 1, Right = 2, Uturn = 3
    QString c0 = QColor(Qt::black).name();
    QString c1 = QColor(Qt::white).name();
    m_builtinTurmites.insert("Langton's ant", QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
    m_builtinTurmites.insert("Demo", QStringList()
        << QString("0|#000000:#ffffff:2:0") << QString("0|#ffffff:#ffffff:2:1")
        << QString("1|#000000:#000000:1:0") << QString("1|#ffffff:#000000:1:1"));
    m_builtinTurmites.insert("Spiral", QStringList()
        << QString("0|%1:%2:%3:1").arg(c0, c1).arg(Engine::Front) << QString("0|%1:%2:%3:0").arg(c1, c1).arg(Engine::Left)
        << QString("1|%1:%2:%3:1").arg(c0, c1).arg(Engine::Right) << QString("1|%1:%2:%3:0").arg(c0, c1).arg(Engine::Front));
    m_builtinTurmites.insert("Highway", QStringList()
        << "0|#000000:#ffffff:2:1" << "0|#ffffff:#000000:2:1"
        << "1|#000000:#ffffff:1:0" << "1|#ffffff:#ffffff:1:1");
    m_builtinTurmites.insert("Wormtrail", QStringList()
        << "0|#000000:#ffffff:2:1" << "0|#ffffff:#ffffff:0:1"
        << "1|#000000:#ffffff:2:1" << "1|#ffffff:#000000:2:0");
    m_builtinTurmites.insert("Picasso", QStringList()
        << "0|#000000:#ffffff:0:0" << "0|#ffffff:#ffffff:2:1"
        << "1|#000000:#000000:2:0" << "1|#ffffff:#000000:0:1");
    m_builtinTurmites.insert("Fibonacci", QStringList()
        << QString("0|%1:%2:%3:1").arg(c0, c1).arg(Engine::Left)  << QString("0|%1:%2:%3:1").arg(c1, c1).arg(Engine::Left)
        << QString("1|%1:%2:%3:1").arg(c0, c1).arg(Engine::Right) << QString("1|%1:%2:%3:0").arg(c1, c0).arg(Engine::Front));
    m_builtinTurmites.insert("Diamond", QStringList()
        << "0|#000000:#000000:1:1" << "0|#ffffff:#000000:2:1"
        << "1|#000000:#ffffff:0:0" << "1|#ffffff:#000000:1:1");
    m_builtinTurmites.insert("Snowflake", QStringList()
        << "0|#000000:#ffffff:0:1" << "0|#ffffff:#ffffff:2:0"
        << "1|#000000:#ffffff:3:1" << "1|#ffffff:#ffffff:3:2"
        << "2|#000000:#000000:0:0" << "2|#ffffff:#000000:3:0");
    using namespace QColorConstants::Svg;
    m_colors << m_bgColor1 << blueviolet << crimson << orangered << limegreen << tomato << green
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
