#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
    QLineEdit * lEdit;
    QSpinBox * sBox;
    QSlider * slider;
    QLabel * label;
    QPushButton * disEn;
    QPushButton * fStyle;
    QComboBox * cBox;
    QPushButton * buttonExit;
    QFrame * frame;
public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void format();
    QLineEdit * createLineEdit();
    QSpinBox * createSpinBox();
    QSlider * createSlider();
    QLabel * createLabel() ;
    QLayout * createVBoxRightLayout();
    QLayout * createHBoxLayout();
    QLayout * createVBoxLayout();
    QLayout * createGridLayout();
    QComboBox * createComboBox();
signals:
    void mySignal (int s);
public slots:
    void mySlot(QString str) {
        int s =str.toInt();
        emit mySignal(s);
    }
    void slotChangeLayout(int index);
    void slotEnDis();
};

#endif // WIDGET_H
