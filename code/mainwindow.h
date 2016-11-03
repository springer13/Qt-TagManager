#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>

#include "mytagbutton.h"
#include "tagmanager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    TagManager *tagManager_;
};

#endif // MAINWINDOW_H
