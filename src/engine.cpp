#include "engine.h"

Engine::Engine()
{
    m_defModels << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRLL" << "RRRLR" << "LRRRRRLLR"
                << "RRRLRRLRRR" << "RRLLLRRLRL" << "RRLLLRLLLLL" << "RRLRLLRRRRLL" << "RRLLLRLLLRLL"
                << "LLRRRLRLRLLR" << "RRLLLRLLLRRR";// << "Custom";
    m_background = Qt::white;
    //Turn: Left = 0, Front = 1, Right = 2, Uturn = 3
    QString c0 = QColor(Qt::black).name();
    QString c1 = QColor(Qt::white).name();
    m_predefTurmites.insert("Langton's ant", QStringList()
            << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
    m_predefTurmites.insert("Demo", QStringList()
        << QString("0|#000000:#ffffff:2:0") << QString("0|#ffffff:#ffffff:2:1")
        << QString("1|#000000:#000000:1:0") << QString("1|#ffffff:#000000:1:1"));
    m_predefTurmites.insert("Spiral", QStringList()
        << QString("0|%1:%2:%3:1").arg(c0, c1).arg(Front) << QString("0|%1:%2:%3:0").arg(c1, c1).arg(Left)
        << QString("1|%1:%2:%3:1").arg(c0, c1).arg(Right) << QString("1|%1:%2:%3:0").arg(c0, c1).arg(Front));
    m_predefTurmites.insert("Highway", QStringList()
        << "0|#000000:#ffffff:2:1" << "0|#ffffff:#000000:2:1"
        << "1|#000000:#ffffff:1:0" << "1|#ffffff:#ffffff:1:1");
    m_predefTurmites.insert("Wormtrail", QStringList()
        << "0|#000000:#ffffff:2:1" << "0|#ffffff:#ffffff:0:1"
        << "1|#000000:#ffffff:2:1" << "1|#ffffff:#000000:2:0");
    m_predefTurmites.insert("Picasso", QStringList()
        << "0|#000000:#ffffff:0:0" << "0|#ffffff:#ffffff:2:1"
        << "1|#000000:#000000:2:0" << "1|#ffffff:#000000:0:1");
    m_predefTurmites.insert("Fibonacci", QStringList()
        << QString("0|%1:%2:%3:1").arg(c0, c1).arg(Left)  << QString("0|%1:%2:%3:1").arg(c1, c1).arg(Left)
        << QString("1|%1:%2:%3:1").arg(c0, c1).arg(Right) << QString("1|%1:%2:%3:0").arg(c1, c0).arg(Front));
    m_predefTurmites.insert("Diamond", QStringList()
        << "0|#000000:#000000:1:1" << "0|#ffffff:#000000:2:1"
        << "1|#000000:#ffffff:0:0" << "1|#ffffff:#000000:1:1");
    m_predefTurmites.insert("Snowflake", QStringList()
        << "0|#000000:#ffffff:0:1" << "0|#ffffff:#ffffff:2:0"
        << "1|#000000:#ffffff:3:1" << "1|#ffffff:#ffffff:3:2"
        << "2|#000000:#000000:0:0" << "2|#ffffff:#000000:3:0");
    using namespace QColorConstants::Svg;
    m_colors << m_background << blueviolet << crimson << orangered << limegreen << green << tomato
             << teal << burlywood << cadetblue << chartreuse << coral << cornflowerblue << darkblue
             << darkcyan << darkgoldenrod << darkgreen << darkkhaki << darkmagenta << darkolivegreen
             << darkorange << darkorchid << darkred << darksalmon << darkseagreen << darkslateblue
             << darkturquoise << fuchsia << gold << darkviolet << deeppink << deepskyblue << plum
             << dodgerblue << firebrick << forestgreen << gainsboro << greenyellow << mediumorchid
             << hotpink << darkslategray << indianred << indigo << khaki << lavenderblush << peru
             << lawngreen << lightblue << lightcyan << lightgoldenrodyellow << lightgreen << aqua
             << lightpink << lightsalmon << lightseagreen << lightskyblue << lime << linen << olive
             << magenta << maroon << mediumaquamarine << mediumpurple << royalblue << mediumseagreen
             << mediumslateblue << midnightblue << mediumspringgreen << salmon << mediumturquoise
             << mediumvioletred << mistyrose << moccasin << navajowhite << navy << orange << orchid
             << palegoldenrod << palegreen << paleturquoise << palevioletred << peachpuff << pink
             << powderblue << purple << rosybrown << sandybrown << seagreen << sienna << skyblue
             << slateblue << springgreen << steelblue << thistle << blue << turquoise << violet
             << wheat << yellow << yellowgreen << goldenrod;
    setBehaviour("RL"); // init defaul model - Langton's ant
}

void Engine::setBehaviour(const QString &behaviour)
{
    if (behaviour == "RL") {    // default model is Langton's ant
        setBehaviour(QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");
        return;
    }
    QList<QColor> subList = m_colors.sliced(0, behaviour.size());    // copy sublist of colors
    subList.push_back(QColor(Qt::white));   // add 1st color to cycle enumerating
    auto ci = subList.constBegin();
    int ddir;
    QStringList list;
    for (auto c = behaviour.constBegin(); c != behaviour.constEnd(); ++c) {
        if (*c == QChar('L'))
            ddir = Left;
        else if (*c == QChar('F'))
            ddir = Front;
        else if (*c == QChar('R'))
            ddir = Right;
        else if (*c == QChar('U'))
            ddir = Uturn;
        else    // this case is impossible, but...
            ddir = Front;
        list << QString("0|%1:%2:%3:0").arg(ci->name(), (++ci)->name()).arg(ddir);
    }
    setBehaviour(list);
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

void Engine::setBehaviourByName(const QString &name)
{
    setBehaviour(m_predefTurmites.value(name));
}

void Engine::move(QColor &color, int &direction)
{
    QString key = QString("%1|%2").arg(m_cState).arg(color.name());
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

void Engine::reset()
{
    m_cState = 0;
}
