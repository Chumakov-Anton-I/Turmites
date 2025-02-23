#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

class GridWidget;
class QPushButton;
class QSpinBox;
class QLineEdit;
class QComboBox;
class QCheckBox;

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

private:
    GridWidget *map;
    QPushButton *m_btnStart;
    QPushButton *m_btnStop;
    QPushButton *m_btnReset;
    QPushButton *m_btnSavePix;

    QLineEdit *m_lblScore;
    QSpinBox *m_sbTimeout;
    QComboBox *m_cbGridSize;
    QCheckBox *m_chbCycledMap;
    QComboBox *m_cbStartDirection;
};

#endif // SUBWINDOW_H
