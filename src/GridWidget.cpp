/*
 * GridWidget.cpp
 * GridWidget class implementation
 */

#include "GridWidget.h"
#include "CAnt.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>

GridWidget::GridWidget(int size, QWidget *parent)
    : QWidget(parent), m_mapSize(size), m_timeout(10), m_startDir(CAnt::North)
{
    initMap();

    m_ant = new CAnt(Qt::red);
    m_ant->setMap(&m_map);
    m_ant->reset(m_mapSize/2, m_mapSize/2, CAnt::North);

    m_painter = new QPainter;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&GridWidget::update));
}

GridWidget::~GridWidget()
{
    delete m_ant;
    delete m_painter;
}

void GridWidget::setSize(int size)
{
    m_mapSize = size;
    reset();
}

void GridWidget::setStartDirection(int dir)
{
    m_startDir = dir;
    reset();
}

void GridWidget::setAntBehaviour(const QString &behaviour)
{
    Q_UNUSED(behaviour)
    //m_ant->setBehaviour(behaviour);
}

bool GridWidget::savePicture(const QString &filenName) const
{
    if (m_pixmap != nullptr)
        return m_pixmap->save(filenName);
    return false;
}

void GridWidget::start()
{
    m_timer->start(m_timeout);
}

void GridWidget::stop()
{
    m_timer->stop();
}

void GridWidget::reset()
{
    m_timer->stop();
    initMap();
    m_ant->reset(m_mapSize/2, m_mapSize/2, CAnt::Direction(m_startDir));
    update();
}

void GridWidget::changeTimeout(int timeout)
{
    m_timeout = timeout;
    if (m_timer->isActive())
        m_timer->start(m_timeout);
}

void GridWidget::setCycled(bool on)
{
    m_ant->setCycled(on);
}

void GridWidget::initMap()
{
    /* Fill grid */
    m_map.clear();
    for (int i = 0; i < m_mapSize; ++i) {
        QVector<SquareCell *> row;
        for (int j = 0; j < m_mapSize; ++j)
            row.push_back(new SquareCell(i, j));
        m_map.push_back(row);
    }

    /* Resize widget */
    resize(m_mapSize*m_cellSize, m_mapSize*m_cellSize);
    setMinimumSize(size());
    m_pixmap = new QPixmap(size());

    m_score = 0;    // reset score
    emit scoreChanged(0);
}

void GridWidget::updateMap()
{
    if (!m_timer->isActive() || !m_ant->move()) {
        m_timer->stop();    // stop the timer after ant's death
        return;
    }
    m_score++;
    emit scoreChanged(m_score);
}

void GridWidget::paintEvent(QPaintEvent *)
{
    updateMap();

    m_painter->begin(m_pixmap);
    for (auto r = m_map.constBegin(); r != m_map.constEnd(); ++r) {
        for (auto c = r->constBegin(); c != r->constEnd(); ++c)
            m_painter->fillRect(getRect((*c)->pos()), (*c)->color());
    }
    m_painter->fillRect(getRect(m_ant->pos()), m_ant->color());
    m_painter->end();

    m_painter->begin(this);
    m_painter->drawPixmap(m_pixmap->rect(), *m_pixmap);
    m_painter->end();
}

QRect GridWidget::getRect(const QPoint &pos)
{
    return QRect(pos*m_cellSize, QSize(m_cellSize, m_cellSize));
}
