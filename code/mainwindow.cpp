#include <QVBoxLayout>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // allocate
    tagManager_ = new TagManager("tag", "name");

    // setup ui
    auto layout = new QVBoxLayout;
    layout->addWidget(tagManager_);
    this->setLayout(layout);

}

MainWindow::~MainWindow()
{

}


