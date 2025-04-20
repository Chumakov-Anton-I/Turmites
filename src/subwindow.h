/**
 * subwindow.h
 * The Subvindow class describes the simplest Langton's ant.
 */

#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

class GridWidget;
class QPushButton;
class QSpinBox;
class QLineEdit;
class QComboBox;
class QCheckBox;
class Engine;

class Subwindow : public QWidget
{
    Q_OBJECT
public:
    explicit Subwindow(QWidget *parent = nullptr);

private slots:
    void setScore(int score);
    void setGridSize();
    void setStartDirection();
    void setCycled();
    void savePicture();
    void saveScreenshot();
    void openBehaviourDlg();
    void showInfo();

private:
    GridWidget *map;
    Engine *m_engine;
    QPushButton *m_btnStart;
    QPushButton *m_btnStop;
    QPushButton *m_btnReset;
    QPushButton *m_btnSavePix;
    QPushButton *m_btnSaveScreen;
    QPushButton *m_btnSetBehaviour;
    QPushButton *m_btnInfo;

    QLineEdit *m_lblScore;
    QSpinBox *m_sbTimeout;
    QSpinBox *m_sbStepsToUpd;
    QComboBox *m_cbGridSize;
    QCheckBox *m_chbCycledMap;
    QComboBox *m_cbStartDirection;
};

#endif // SUBWINDOW_H
