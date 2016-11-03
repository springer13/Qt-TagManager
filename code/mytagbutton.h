#ifndef MYTAGBUTTON_H
#define MYTAGBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyTagButton : public QPushButton
{
    Q_OBJECT
public:
    MyTagButton(QWidget *parent = 0);
    ~MyTagButton();

signals:
    void clicked(MyTagButton*);

public slots:
private:
    virtual void mousePressEvent(QMouseEvent *e);
};

#endif // MYTAGBUTTON_H
