#include "engine.h"

Engine::Engine()
{
    m_defModels << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRLL" << "RRRLR" << "RRRLRRLRRR"
                << "RRLRLLRRRRLL" << "RRLLLRRLRL" << "RRLLLRLLLRLL" << "RRLLLRLLLLL";// << "Custom";
    m_background = Qt::white;
    //Turn: Left = 0, Front = 1, Right = 2, Uturn =3
    //QStringList b;
    /*b << "0|#ffffff:#000000:1:1" << "0|#ffffff:#ffffff:0:0"
      << "1|#ffffff:#000000:2:1" << "1|#000000:#ffffff:1:0";*/
    /*QString color0 = QColorConstants::Svg::white.name();
    QString color1 = QColorConstants::Svg::blueviolet.name();
    QString color2 = QColorConstants::Svg::crimson.name();
    QString color3 = QColorConstants::Svg::orangered.name();
    // RRLL
    b << QString("0|%1:%2:%3:0").arg(color0, color1).arg(Right)
      << QString("0|%1:%2:%3:0").arg(color1, color2).arg(Right)
      << QString("0|%1:%2:%3:0").arg(color2, color3).arg(Left)
      << QString("0|%1:%2:%3:0").arg(color3, color0).arg(Left);
    setBehaviour(b);*/
    // color list, see https://www.w3.org/TR/SVG11/types.html#ColorKeywords
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
    // init defaul model - Langton's ant
    setBehaviour("RL");
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
    m_stateTable.clear();
    m_cState = 0;   // init state
    for (auto bi = behaviour.constBegin(); bi != behaviour.constEnd(); ++bi) {
        QStringList item = (*bi).split(":");
        m_stateTable.insert(item[0], TState{item[1], item[2].toInt(), item[3].toUInt()});
    }
}

void Engine::move(QColor &color, int &direction)
{
    QString key = QString("%1|%2").arg(m_cState).arg(color.name());
    TState state = m_stateTable.value(key);
    int turn = state.direction;
    switch (turn) {
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
