#include <QPushButton>
#include <QDebug>
#include <QStyle>
#include <QApplication>

#include "mytagbutton.h"

MyTagButton::MyTagButton(QWidget *parent) : QPushButton(parent)
{
    //this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->setIcon(QApplication::style()->standardIcon(
                                     QStyle::SP_DialogCancelButton));
}

MyTagButton::~MyTagButton()
{
}

void MyTagButton::mousePressEvent(QMouseEvent *e)
{
    emit clicked(this);
}
