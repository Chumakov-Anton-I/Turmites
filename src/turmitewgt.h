/** turmitewgt.h
 * The Subvindow class describes the simplest Langton's ant.
 */

#ifndef TURMITEWGT_H
#define TURMITEWGT_H

#include <QWidget>

class GridWidget;
class QPushButton;
class QSpinBox;
class QLineEdit;
class QComboBox;
class QCheckBox;
class Engine;

class TurmiteWgt : public QWidget
{
    Q_OBJECT
public:
    explicit TurmiteWgt(QWidget *parent = nullptr);

private slots:
    void setScore(int score);
    void setGridSize();
    void setStartDirection();
    void setCycled();
    void savePicture();
    void setBehaviour();

private:
    GridWidget *map;
    Engine *m_engine;
    QPushButton *m_btnStart;
    QPushButton *m_btnStop;
    QPushButton *m_btnReset;
    QPushButton *m_btnSavePix;

    QLineEdit *m_lblScore;
    QSpinBox *m_sbTimeout;
    QComboBox *m_cbGridSize;
    QCheckBox *m_chbCycledMap;
    QComboBox *m_cbStartDirection;
    QComboBox *m_cbBehaviour;
};

#endif // TURMITEWGT_H
