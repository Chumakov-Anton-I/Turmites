#include "GridWidget.h"
#include "SquareCell.h"
#include "CAnt.h"

#include <QPainter>
#include <QTimer>

GridWidget::GridWidget(int size, QWidget *parent)
    : QWidget(parent), m_mapSize(size), m_timeout(10)
{
    m_ant = new CAnt(m_cellSize);
    initMap();

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
    m_map.clear();
    m_ant->setAlive(true);
    initMap();
    update();
}

void GridWidget::changeTimeout(int timeout)
{
    m_timeout = timeout;
    m_timer->start(m_timeout);
}

void GridWidget::initMap()
{
    /* Set ant */
    m_ant->setPos(m_mapSize/2, m_mapSize/2);
    m_ant->setDir(CAnt::North);
    m_ant->setColor(Qt::red);

    // Fill grid */
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
    if (!m_timer->isActive() || !m_ant->isAlive())
        return; // do nothing when the timer is stopped or the ant isn't alive

    int X = m_ant->x();
    int Y = m_ant->y();
    int turn;
    if (m_map.at(X).at(Y)->color() == Qt::black)
        turn = Left;
    else // if (m_map.at(X).at(Y)->color() == Qt::white)
        turn = Right;

    switch (m_ant->direction()) {
    case CAnt::North:
        if (turn == Left) {
            m_map.at(X).at(Y)->setColor(Qt::white);
            m_ant->setDir(CAnt::West);
            X -= 1;
        } else /*if (turn == Right)*/ {
            m_map.at(X).at(Y)->setColor(Qt::black);
            m_ant->setDir(CAnt::East);
            X += 1;
        }
        break;
    case CAnt::East:
        if (turn == Left) {
            m_map.at(X).at(Y)->setColor(Qt::white);
            m_ant->setDir(CAnt::North);
            Y -= 1;
        } else /*if (turn == Right)*/ {
            m_map.at(X).at(Y)->setColor(Qt::black);
            m_ant->setDir(CAnt::South);
            Y += 1;
        }
        break;
    case CAnt::South:
        if (turn == Left) {
            m_map.at(X).at(Y)->setColor(Qt::white);
            m_ant->setDir(CAnt::East);
            X += 1;
        } else /*if (turn == Right)*/ {
            m_map.at(X).at(Y)->setColor(Qt::black);
            m_ant->setDir(CAnt::West);
            X -= 1;
        }
        break;
    case CAnt::West:
        if (turn == Left) {
            m_map.at(X).at(Y)->setColor(Qt::white);
            m_ant->setDir(CAnt::South);
            Y += 1;
        } else /*if (turn == Right)*/ {
            m_map.at(X).at(Y)->setColor(Qt::black);
            m_ant->setDir(CAnt::North);
            Y -= 1;
        }
        break;
    }

    if (X < 0 || Y < 0 || X >= m_mapSize || Y >= m_mapSize)
    {
        if (m_cycledMap) {
            if (X < 0)  X = m_mapSize - 1;
            if (Y < 0)  Y = m_mapSize - 1;
            if (X == m_mapSize) X = 0;
            if (Y == m_mapSize) Y = 0;
        } else {
            m_ant->setAlive(false);
            m_ant->setColor(Qt::gray);
            return;
        }
    }

    m_ant->setPos(X, Y);
    m_score++;
    emit scoreChanged(m_score);
}

void GridWidget::paintEvent(QPaintEvent *)
{
    //Q_UNUSED(event)
    updateMap();

    m_painter->begin(this);
    for (auto r = m_map.constBegin(); r != m_map.constEnd(); ++r) {
        for (auto c = r->constBegin(); c != r->constEnd(); ++c)
            m_painter->fillRect((*c)->rect(), (*c)->color());
    }
    m_painter->fillRect(m_ant->rect(), m_ant->color());
    m_painter->end();
}
