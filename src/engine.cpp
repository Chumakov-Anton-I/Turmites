#include "engine.h"

#include <QDebug>

Engine::Engine()
{
    m_defModels << "RL" << "RLR" << "RLLR" << "RRLR" << "LLRR" << "RRRLR" << "RRRLRRLRRR"
                << "RRLRLLRRRRLL" << "RRLLLRRLRL" << "RRLLLRLLLRLL" << "RRLLLRLLLLL";// << "Custom";
    m_background = Qt::white;
    /* Make default behaviour - Langton's Ant */
    m_colorTable.insert("#000000", "#ffffff");  // black => white
    m_colorTable.insert("#ffffff", "#000000");  // white => black
    m_rulesTable.insert("#000000", Left);  // black <=> left turn
    m_rulesTable.insert("#ffffff", Right);  // white <=> right turn
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
}

void Engine::setBehaviour(const QString &behaviour)
{
    m_strBehaviour = behaviour;
    m_colorTable.clear();
    m_rulesTable.clear();
    // fill rules
    auto ci = m_colors.constBegin();
    QString color0 = ci->name();    // memorize start color
    QString color2;
    int ddir;
    for (auto c = m_strBehaviour.constBegin(); c != m_strBehaviour.constEnd(); ++c) {
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
        color2 = ci->name();    // get current key
        m_rulesTable.insert(color2, ddir);
        m_colorTable.insert(color2, (++ci)->name());
    }
    m_colorTable.insert(color2, color0);  // last key-color references to 0st key
}

/*void Engine::setBehaviour(const QStringList &behaviour)
{
    m_listBehaviour = behaviour;
    m_colorTable.clear();
    m_rulesTable.clear();
    //
}*/

void Engine::move(const QColor &color, int dir)
{
    // bullshit
    QString s_color = color.name();
    QString s_newColor = m_colorTable.value(s_color);
    int turn = m_rulesTable.value(s_color);
    switch (turn) {
    case Left:
        if (--dir < North) dir = West;
        break;
    case Right:
        if (++dir > West) dir = North;
        break;
    case Uturn:
        if (++dir > West) dir = North;
        if (++dir > West) dir = North;
        break;
    default:    // Front <-> No turn
        break;
    }
    out_newColor = s_newColor;
    out_newDir = dir;
}
