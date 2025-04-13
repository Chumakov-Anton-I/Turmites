#include "InfoWindow.h"

#include <QBoxLayout>
#include <QFormLayout>
#include <QTextBrowser>
#include <QLabel>

InfoWindow::InfoWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout;
    QTextBrowser *textMainInfo = new QTextBrowser;
    textMainInfo->setOpenExternalLinks(true);
    textMainInfo->setFrameShape(QFrame::NoFrame);
    textMainInfo->setHtml(tr(
        "A <b>turmite</b> is a Turing machine which has an orientation in addition to a current "
        "state and a \"tape\" that consists of an infinite two-dimensional grid of cells. "
        "<a href=\"https://en.wikipedia.org/wiki/Turmite\">Read more...</a><br>"
        "<b>Langton's ant</b> is a two-dimensional Turing machine with a very simple set of rules "
        "but complex emergent behavior. It was invented by Chris Langton in 1986 and runs on a "
        "square lattice of black and white cells. The idea has been generalized in several "
        "different ways, such as turmites which add more colors and more states. "
        "<a href=\"https://en.wikipedia.org/wiki/Langton%27s_ant\">Read more...</a>"));
    textMainInfo->setReadOnly(true);
    topLayout->addWidget(textMainInfo);
    QFormLayout *linksForm = new QFormLayout;
    topLayout->addLayout(linksForm);
    linksForm->addRow(tr("Author"), new QLabel("A. Chumakov"));
    topLayout->addStretch(1);
    setLayout(topLayout);
}
