#include "GridWidget.h"
#include "SquareCell.h"
#include "CAnt.h"

#include <QPainter>
#include <QTimer>

GridWidget::GridWidget(int size, QWidget *parent)
    : QWidget(parent), m_mapSize(size), m_timeout(10)
{
    initMap();

    m_ant = new CAnt(m_cellSize);
    m_ant->setMap(&m_map);
    m_ant->reset(m_mapSize/2, m_mapSize/2, CAnt::North, Qt::red);

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

void GridWidget::start() { m_timer->start(m_timeout); }

void GridWidget::stop() { m_timer->stop(); }

void GridWidget::reset()
{
    m_timer->stop();
    initMap();
    m_ant->reset(m_mapSize/2, m_mapSize/2, CAnt::North, Qt::red);
    update();
}

void GridWidget::changeTimeout(int timeout)
{
    m_timeout = timeout;
    if (m_timer->isActive())
        m_timer->start(m_timeout);
}

void GridWidget::initMap()
{
    /* Fill grid */
    m_map.clear();
    for (int i = 0; i < m_mapSize; ++i) {
        QVector<SquareCell *> row;
        for (int j = 0; j < m_mapSize; ++j)
            row.push_back(new SquareCell(i, j, m_cellSize));
        m_map.push_back(row);
    }

    /* Resize widget */
    resize(m_mapSize*m_cellSize, m_mapSize*m_cellSize);
    setMinimumSize(size());
    m_score = 0;    // reset score
    emit scoreChanged(0);
}

void GridWidget::updateMap()
{
    if (!m_timer->isActive())
        return; // do nothing when the timer is stopped
    if (!m_ant->move()) {
        m_timer->stop();
        return;
    }
    m_score++;
    emit scoreChanged(m_score);
}

void GridWidget::paintEvent(QPaintEvent *)
{
    updateMap();

    m_painter->begin(this);
    for (auto r = m_map.constBegin(); r != m_map.constEnd(); ++r) {
        for (auto c = r->constBegin(); c != r->constEnd(); ++c)
            m_painter->fillRect((*c)->rect(), (*c)->color());
    }
    m_painter->fillRect(m_ant->rect(), m_ant->color());
    m_painter->end();
}
