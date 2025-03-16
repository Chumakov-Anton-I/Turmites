#include "turmitewgt.h"
#include "GridWidget.h"
#include "engine.h"

#include <QBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>

TurmiteWgt::TurmiteWgt(QWidget *parent)
    : QWidget(parent)
{
    m_engine = new Engine;

    setBackgroundRole(QPalette::Window);
    setAutoFillBackground(true);

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
    paramsForm->setRowWrapPolicy(QFormLayout::DontWrapRows);
    paramsForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    paramsForm->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    paramsForm->setLabelAlignment(Qt::AlignRight);
    cmdLayout->addLayout(paramsForm);

    // score counter
    m_lblScore = new QLineEdit("0");
    m_lblScore->setReadOnly(true);
    paramsForm->addRow(tr("Steps:"), m_lblScore);
    // set timeout
    m_sbTimeout = new QSpinBox;
    m_sbTimeout->setRange(1, 1000);
    m_sbTimeout->setValue(5);
    m_sbTimeout->setSingleStep(5);
    m_sbTimeout->setSuffix(tr(" ms"));
    paramsForm->addRow(tr("Timeout:"), m_sbTimeout);
    // set behaviour
    m_cbBehaviour = new QComboBox;
    paramsForm->addRow(tr("Behaviour:"), m_cbBehaviour);
    // set start orient
    m_cbStartDirection = new QComboBox;
    paramsForm->addRow(tr("Start orientation:"), m_cbStartDirection);
    // grid size
    m_cbGridSize = new QComboBox;
    paramsForm->addRow(tr("Grid size:"), m_cbGridSize);
    // is the map cycled?
    m_chbCycledMap = new QCheckBox(tr("Cycled map"));
    paramsForm->addRow(m_chbCycledMap);

    cmdLayout->addStretch(1);
    m_btnSavePix = new QPushButton(tr("Save picture..."));
    cmdLayout->addWidget(m_btnSavePix);

    map = new GridWidget(m_engine, 100);
    topLayout->addWidget(map);

    // tune widgets
    m_cbBehaviour->addItems(m_engine->predefListT());
    m_cbGridSize->addItems(QStringList() << "100" << "125" << "150" << "200" << "250");
    m_cbStartDirection->addItems(QStringList() << "North" << "East" << "South" << "West");

    connect(m_btnStart, &QPushButton::clicked, map, &GridWidget::start);
    connect(m_btnStop, &QPushButton::clicked, map, &GridWidget::stop);
    connect(m_btnReset, &QPushButton::clicked, map, &GridWidget::reset);
    connect(m_sbTimeout, &QSpinBox::valueChanged, map, &GridWidget::changeTimeout);
    connect(map, &GridWidget::scoreChanged, this, &TurmiteWgt::setScore);
    connect(m_cbStartDirection, &QComboBox::currentIndexChanged, this, &TurmiteWgt::setStartDirection);
    connect(m_cbGridSize, &QComboBox::currentTextChanged, this, &TurmiteWgt::setGridSize);
    connect(m_chbCycledMap, &QCheckBox::checkStateChanged, this, &TurmiteWgt::setCycled);
    connect(m_btnSavePix, &QPushButton::clicked, this, &TurmiteWgt::savePicture);
    connect(m_cbBehaviour, &QComboBox::currentTextChanged, this, &TurmiteWgt::setBehaviour);
}

void TurmiteWgt::setScore(int score)
{
    m_lblScore->setText(QString::number(score));
}

void TurmiteWgt::setGridSize()
{
    int size = m_cbGridSize->currentText().toInt();
    if (size == 0) size = 100;
    map->setSize(size);
    resize(minimumSizeHint());
}

void TurmiteWgt::setStartDirection()
{
    map->setStartDirection(m_cbStartDirection->currentIndex());
}

void TurmiteWgt::setCycled()
{
    if (m_chbCycledMap->checkState() == Qt::Unchecked)
        map->setCycled(false);
    else
        map->setCycled(true);
}

void TurmiteWgt::savePicture()
{
    map->stop();
    QString selectedFormat;
    QString fname = QFileDialog::getSaveFileName(
        this,
        tr("Save picture"),
        QString(),
        tr("BMP format (*.bmp);;JPEG format (*.jpg);;PNG format (*.png);;All images (*.bmp *.png *.xpm *.jpg)"),
        &selectedFormat);
    if (fname.isEmpty()) return;
    if (!map->savePicture(fname))
        QMessageBox::critical(this, tr("Error"),
                              tr("Cannot save file"));  // TODO
    map->start();
}

void TurmiteWgt::setBehaviour()
{
    map->stop();
    map->reset();
    QString beh = m_cbBehaviour->currentText();
    m_engine->setBehaviourByName(beh);
}
