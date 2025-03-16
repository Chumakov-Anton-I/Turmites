#include "subwindow.h"
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
#include <QRect>

Subwindow::Subwindow(QWidget *parent)
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
    m_sbStepsToUpd = new QSpinBox;
    m_sbStepsToUpd->setRange(1, 50);
    m_sbStepsToUpd->setValue(1);
    paramsForm->addRow(tr("Steps to update:"), m_sbStepsToUpd);
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
    m_btnSaveScreen = new QPushButton(tr("Save screenshot..."));
    cmdLayout->addWidget(m_btnSaveScreen);

    map = new GridWidget(m_engine, 100);
    topLayout->addWidget(map);

    // tune widgets
    m_cbBehaviour->addItems(m_engine->predefList());
    m_cbGridSize->addItems(QStringList() << "75" << "100" << "125" << "150" << "200" << "250");
    m_cbStartDirection->addItems(QStringList() << "North" << "East" << "South" << "West");

    connect(m_btnStart, &QPushButton::clicked, map, &GridWidget::start);
    connect(m_btnStop, &QPushButton::clicked, map, &GridWidget::stop);
    connect(m_btnReset, &QPushButton::clicked, map, &GridWidget::reset);
    connect(m_sbTimeout, &QSpinBox::valueChanged, map, &GridWidget::changeTimeout);
    connect(m_sbStepsToUpd, &QSpinBox::valueChanged, map, &GridWidget::setStepsToUpdate);
    connect(map, &GridWidget::scoreChanged, this, &Subwindow::setScore);
    connect(m_cbStartDirection, &QComboBox::currentIndexChanged, this, &Subwindow::setStartDirection);
    connect(m_cbGridSize, &QComboBox::currentTextChanged, this, &Subwindow::setGridSize);
    connect(m_chbCycledMap, &QCheckBox::checkStateChanged, this, &Subwindow::setCycled);
    connect(m_btnSavePix, &QPushButton::clicked, this, &Subwindow::savePicture);
    connect(m_cbBehaviour, &QComboBox::currentTextChanged, this, &Subwindow::setBehaviour);
    connect(m_btnSaveScreen, &QPushButton::clicked, this, &Subwindow::saveScreenshot);
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
    resize(minimumSizeHint());
}

void Subwindow::setStartDirection()
{
    map->setStartDirection(m_cbStartDirection->currentIndex());
}

void Subwindow::setCycled()
{
    if (m_chbCycledMap->checkState() == Qt::Unchecked)
        map->setCycled(false);
    else
        map->setCycled(true);
}

void Subwindow::savePicture()
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

void Subwindow::saveScreenshot()
{
    map->stop();
    QString fname = QFileDialog::getSaveFileName(
        this,
        tr("Save screenshot"),
        QString(),
        tr("BMP format (*.bmp);;JPEG format (*.jpg);;PNG format (*.png);;All images (*.bmp *.png *.xpm *.jpg)"));
    if (fname.isEmpty()) return;
    QPixmap pix = this->grab(QRect(QPoint(0,0), size()));
    if (!pix.save(fname))
        QMessageBox::critical(this, tr("Error"), tr("Cannot save file"));   // TODO
}

void Subwindow::setBehaviour()
{
    map->stop();
    map->reset();
    QString beh = m_cbBehaviour->currentText();
    m_engine->setBehaviour(beh);
}
