#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->format();
    buttonExit = new QPushButton(QObject::tr("Exit"),this);
    QObject::connect(buttonExit,SIGNAL(clicked(bool)), this, SLOT(close()));
    frame =new QFrame(this);
    frame->setFrameStyle(1);
    lEdit = this->createLineEdit();
    sBox = this->createSpinBox();
    slider = this->createSlider();
    label = this->createLabel();
    disEn = new QPushButton(QObject::tr("Disable"),this);
    fStyle = new QPushButton(QObject::tr("Fusion style"),this);
    cBox = this->createComboBox();
    QHBoxLayout * mainLayout = new QHBoxLayout;
    QLayout * rLayout = this->createVBoxRightLayout();
    QLayout * lLayout = this->createHBoxLayout();
    frame->setLayout(lLayout);
    mainLayout->addWidget(frame);
    mainLayout->addLayout(rLayout);
    this->setLayout(mainLayout);
    QObject::connect(sBox,SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)), sBox, SLOT(setValue(int)));
    QObject::connect(lEdit,SIGNAL(textChanged(QString)), this, SLOT(mySlot(QString)));
    QObject::connect(this,SIGNAL(mySignal(int)), sBox, SLOT(setValue(int)));
    QObject::connect(sBox,SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
    QObject::connect(cBox,SIGNAL(activated(int)), this, SLOT(slotChangeLayout(int)));
    QObject::connect(disEn,SIGNAL(clicked(bool)), this, SLOT(slotEnDis()));
    emit sBox->valueChanged(10);
   }
Widget::~Widget()
{

}

void Widget::format() {
    Qt::WindowFlags flags = this->windowFlags();
    flags=Qt::Widget;
    flags|=Qt::CustomizeWindowHint;
    flags|=Qt::WindowTitleHint;
    this->setWindowFlags(flags);
}
QLineEdit * Widget::createLineEdit() {
    QLineEdit * QLE = new QLineEdit(this);
    QIntValidator * qVal = new QIntValidator(0, 50, QLE);
    QLE->setValidator(qVal);
    return QLE;
}
QSpinBox * Widget::createSpinBox() {
    QSpinBox * QSB = new QSpinBox(this);
    QSB->setMaximum(50);
    return QSB;
}
QSlider * Widget::createSlider() {
    QSlider * QSL = new QSlider(this);
    QSL->setOrientation(Qt::Horizontal);
    QSL->setRange(0, 50);
    QSL->setTickPosition(QSlider::TicksAbove);
    return QSL;
}
QLabel * Widget::createLabel() {
    QLabel * QLB = new QLabel("Not set", this);
    QLB->setFrameStyle(2);
    QLB->setAlignment(Qt::AlignCenter);
    return QLB;
}
QLayout * Widget::createVBoxRightLayout() {
    QVBoxLayout * rLayout = new QVBoxLayout();
    rLayout->addWidget(cBox);
    rLayout->addWidget(disEn);
    rLayout->addWidget(fStyle);
    rLayout->addWidget(buttonExit);
    return rLayout;
}
QLayout * Widget::createHBoxLayout() {
    QHBoxLayout * lLayout = new QHBoxLayout();
    lLayout->addWidget(sBox);
    lLayout->addWidget(slider);
    lLayout->addWidget(lEdit);
    lLayout->addWidget(label);
    return lLayout;
}
QLayout * Widget::createVBoxLayout() {
    QVBoxLayout * lLayout = new QVBoxLayout();
    lLayout->addWidget(sBox,Qt::AlignCenter);
    //sBox->setSizePolicy(QSizePolicy::Fixed);
    lLayout->addWidget(slider, Qt::AlignCenter);
    lLayout->addWidget(lEdit, Qt::AlignCenter);
    //lEdit->setSizePolicy(QSizePolicy::Fixed);
    lLayout->addWidget(label, Qt::AlignCenter);
    //label->setSizePolicy(QSizePolicy::Fixed);
    return lLayout;
}
QLayout * Widget::createGridLayout() {
    QGridLayout * lLayout = new QGridLayout();
    lLayout->addWidget(sBox,1,1);
    lLayout->addWidget(slider,1, 2);
    lLayout->addWidget(lEdit, 2, 1);
    lLayout->addWidget(label, 2, 2);
    return lLayout;
}
QComboBox * Widget::createComboBox() {
    QComboBox * QCB = new QComboBox(this);
    QCB->addItem("Horizontal");
    QCB->addItem("Vertical");
    QCB->addItem("Grid");
    return QCB;
}
void Widget::slotChangeLayout(int index) {
    QLayout* lay = frame->layout();
    delete lay;
    switch (index)
    {
    case 0: lay= this->createHBoxLayout();break;
    case 1: lay= this->createVBoxLayout();break;
    case 2: lay= this->createGridLayout();break;
    }
    frame->setLayout(lay);
    lay->activate();
    frame->updateGeometry();
}
void Widget::slotEnDis() {
    QString name(QObject::tr("Disable"));
    if (name == disEn->text()) {
        frame->setDisabled(1);
        disEn->setText(QObject::tr("Enable"));
    } else {frame->setEnabled(1);  disEn->setText(QObject::tr("Disable"));}
}
