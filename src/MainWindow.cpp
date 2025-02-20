#include "MainWindow.h"
#include "subwindow.h"
#include "InfoWindow.h"

#include <QTabWidget>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout;
    m_tabWidget = new QTabWidget;
    m_tabWidget->addTab(new Subwindow, tr("Simplest"));
    m_tabWidget->addTab(new InfoWindow, tr("Info"));
    topLayout->addWidget(m_tabWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(topLayout);
}
