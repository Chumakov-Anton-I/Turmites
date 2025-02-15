#include "subwindow.h"
#include "GridWidget.h"

#include <QBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

Subwindow::Subwindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(topLayout);

    QVBoxLayout *cmdLayout = new QVBoxLayout;
    cmdLayout->setContentsMargins(1, 1, 1, 1);
    topLayout->addLayout(cmdLayout);

    m_btnStart = new QPushButton(tr("Start"));
    m_btnStop = new QPushButton(tr("Stop"));
    m_btnReset = new QPushButton(tr("Reset"));

    cmdLayout->addWidget(m_btnStart);
    cmdLayout->addWidget(m_btnStop);
    cmdLayout->addWidget(m_btnReset);

    QFormLayout *paramsForm = new QFormLayout;
    paramsForm->setContentsMargins(1, 1, 1, 1);
    cmdLayout->addLayout(paramsForm);

    m_lblScore = new QLabel("0");
    paramsForm->addRow(tr("Steps"), m_lblScore);
    m_sbTimeout = new QSpinBox;
    m_sbTimeout->setRange(1, 1000);
    m_sbTimeout->setValue(5);
    m_sbTimeout->setSingleStep(5);
    m_sbTimeout->setSuffix(tr(" ms"));
    paramsForm->addRow(tr("Timeout"), m_sbTimeout);
    m_cbGridSize = new QComboBox;
    paramsForm->addRow(tr("Grid size"), m_cbGridSize);
    m_chbCycledMap = new QCheckBox(tr("Cycled map"));
    paramsForm->addRow(m_chbCycledMap);

    cmdLayout->addStretch(1);

    map = new GridWidget(100);
    topLayout->addWidget(map);

    // tune widgets
    m_cbGridSize->addItems(QStringList() << "100" << "150" << "200" << "250");

    connect(m_btnStart, &QPushButton::clicked, map, &GridWidget::start);
    connect(m_btnStop, &QPushButton::clicked, map, &GridWidget::stop);
    connect(m_btnReset, &QPushButton::clicked, map, &GridWidget::reset);
    connect(m_sbTimeout, &QSpinBox::valueChanged, map, &GridWidget::changeTimeout);
    connect(map, &GridWidget::scoreChanged, this, &Subwindow::setScore);
    connect(m_cbGridSize, &QComboBox::currentTextChanged, this, &Subwindow::setGridSize);
    connect(m_chbCycledMap, &QCheckBox::checkStateChanged, this, &Subwindow::setCycled);
}

void Subwindow::setScore(int score)
{
    m_lblScore->setText(QString::number(score));
}

void Subwindow::setGridSize()
{
    int size = m_cbGridSize->currentText().toInt();
    if (size == 0) size = 100;
    map->setSize(size);
}

void Subwindow::setCycled()
{
    if (m_chbCycledMap->checkState() == Qt::Unchecked)
        map->setCycled(false);
    else
        map->setCycled(true);
}
