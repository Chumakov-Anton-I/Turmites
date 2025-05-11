#include "subwindow.h"
#include "GridWidget.h"
#include "engine.h"
#include "InfoWindow.h"

#include <QBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QRect>
#include <QLabel>
#include <QGroupBox>

Subwindow::Subwindow(QWidget *parent)
    : QWidget(parent)
{
    m_engine = new Engine(this);
    m_engine->setBehaviour(QStringList() << "0|#000000:#ffffff:0:0" << "0|#ffffff:#000000:2:0");    // default behaviour - Langton's ant

    auto *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(2, 2, 2, 2);
    topLayout->setSpacing(2);
    setLayout(topLayout);
    // left pane
    auto *cmdLayout = new QVBoxLayout;
    cmdLayout->setSpacing(3);
    //cmdLayout->setContentsMargins(2, 2, 2, 2);
    topLayout->addLayout(cmdLayout);

    auto *btnsGrid = new QGridLayout;
    btnsGrid->setSpacing(2);
    cmdLayout->addLayout(btnsGrid);
    m_btnStart = new QPushButton(tr("Start"));
    m_btnStop = new QPushButton(tr("Stop"));
    m_btnReset = new QPushButton(tr("Reset"));
    btnsGrid->addWidget(m_btnStart, 0, 0);
    btnsGrid->addWidget(m_btnStop, 0, 1);
    btnsGrid->addWidget(m_btnReset, 0, 2);

    m_lblScore = new QLineEdit("0");
    m_lblScore->setReadOnly(true);
    btnsGrid->addWidget(new QLabel(tr("Score")), 1, 0);
    btnsGrid->addWidget(m_lblScore, 1, 1, 1, 2);

    auto *settingsGroup = new QGroupBox(tr("Settings"));
    cmdLayout->addWidget(settingsGroup);

    auto *paramsForm = new QFormLayout;
    //paramsForm->setContentsMargins(1, 1, 1, 1);
    paramsForm->setRowWrapPolicy(QFormLayout::DontWrapRows);
    paramsForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    paramsForm->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    paramsForm->setLabelAlignment(Qt::AlignRight);
    settingsGroup->setLayout(paramsForm);

    // set timeout
    m_sbTimeout = new QSpinBox;
    m_sbTimeout->setRange(1, 1000);
    m_sbTimeout->setValue(5);
    m_sbTimeout->setSingleStep(5);
    m_sbTimeout->setSuffix(tr(" ms"));
    paramsForm->addRow(tr("Timeout:"), m_sbTimeout);
    m_sbStepsToUpd = new QSpinBox;
    m_sbStepsToUpd->setRange(1, 1000);
    m_sbStepsToUpd->setValue(1);
    paramsForm->addRow(tr("Steps to update:"), m_sbStepsToUpd);
    // set behaviour
    m_btnSetBehaviour = new QPushButton(tr("Change behaviour"));
    paramsForm->addRow(tr("Behaviour:"), m_btnSetBehaviour);
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
    m_btnSaveScreen = new QPushButton(tr("Take screenshot..."));
    cmdLayout->addWidget(m_btnSaveScreen);
    m_btnInfo = new QPushButton(tr("Info"));
    cmdLayout->addWidget(m_btnInfo);

    QStringList sizeList(QStringList() << "100" << "125" << "150" << "200" << "250");
    map = new GridWidget(m_engine, sizeList.at(0).toInt());
    topLayout->addWidget(map);

    // tune widgets
    m_cbGridSize->addItems(sizeList);
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
    connect(m_btnSaveScreen, &QPushButton::clicked, this, &Subwindow::saveScreenshot);
    connect(m_btnSetBehaviour, &QPushButton::clicked, this, &Subwindow::openBehaviourDlg);
    connect(m_btnInfo, &QPushButton::clicked, this, &Subwindow::showInfo);
    connect(m_engine, &Engine::behaviourChanged, m_btnSetBehaviour, &QPushButton::setText);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
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
    //resize(minimumSizeHint());
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

void Subwindow::openBehaviourDlg()
{
    map->stop();
    if (m_engine->exec() == QDialog::Accepted) {
        map->reset();
        return;
    }
}

void Subwindow::showInfo()
{
    auto *win = new InfoWindow(this);
    //win->setWindowModality(Qt::WindowModal);
    win->exec();
    delete win;
}
