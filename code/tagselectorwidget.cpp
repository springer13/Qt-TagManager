#include <QSqlDatabase>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QGroupBox>
#include <QSqlError>
#include <QShortcut>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollArea>
#include <QSqlRecord>
#include <QSqlField>

#include "dbmanager.h"
#include "tagselectorwidget.h"
#include "flowlayout.h"

TagSelectorWidget::TagSelectorWidget(const QString &tableName,
                                     const QString &tagColumnName, QWidget *parent) :
    QWidget(parent), tableName_(tableName), tagColumnName_(tagColumnName)
{
    // open database
    this->setupDatabase();

    // allocate
    tagButtomGroup_ = new QButtonGroup(this);
    tagButtomGroup_->setExclusive(false);
    tagsBox_ = new QGroupBox("Select labels:");
    tagsBox_->setLayout(new FlowLayout);
    addLabel_ = new QLabel("Create new tag:");
    addEdit_ = new QLineEdit;
    addNewTag_ = new QPushButton("+");
    okay_ = new QPushButton("&Okay");
    cancel_ = new QPushButton("&Cancel");

    // configure widgets
    QShortcut *shortcut_ok = new QShortcut(QKeySequence("Ctrl+O"), this);
    QObject::connect(shortcut_ok, SIGNAL(activated()), this, SLOT(on_okayPushed()));
    QShortcut *shortcut_cancel = new QShortcut(QKeySequence("Ctrl+C"), this);
    QObject::connect(shortcut_cancel, SIGNAL(activated()), this, SLOT(close()));
    okay_->setIcon(QApplication::style()->standardIcon(
                                     QStyle::SP_DialogApplyButton));
    cancel_->setIcon(QApplication::style()->standardIcon(
                                     QStyle::SP_DialogCancelButton));

    // scroll area
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    scrollArea->setGeometry( 10, 10, 200, 100 );
    scrollArea->setMinimumSize(200,10);
    scrollArea->setMaximumHeight(150);
    scrollArea->setWidget(tagsBox_);

    // ui
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(scrollArea,1,1,1,3);
    layout->addWidget(addLabel_,2,1,1,1);
    layout->addWidget(addEdit_,2,2,1,1);
    layout->addWidget(addNewTag_,2,3,1,1);
    layout->addWidget(okay_,3,2,1,1);
    layout->addWidget(cancel_,3,3,1,1);
    this->setLayout(layout);

    // add all tag-Buttoms
    for(int row=0; row < table_->rowCount(); row++) {
        QModelIndex index = table_->index(row,table_->fieldIndex(tagColumnName_));
        auto tagText = index.data().toString();
        this->addTag(tagText);
    }

    // connect
    connect(addNewTag_, &QPushButton::clicked,
            this, &TagSelectorWidget::on_addTagPushed);
    connect(okay_, &QPushButton::clicked,
            this, &TagSelectorWidget::on_okayPushed);
    connect(cancel_, &QPushButton::clicked,
            this, &TagSelectorWidget::close);
    connect(addEdit_, &QLineEdit::returnPressed,
            this, &TagSelectorWidget::on_addTagPushed);
}

void TagSelectorWidget::setupDatabase()
{
    table_ = new QSqlRelationalTableModel(this, *DbManager::Instance()->getDatabase());
    table_->setTable(tableName_);
    table_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table_->setSort(table_->fieldIndex(tagColumnName_), Qt::AscendingOrder);
    table_->select();
}

void TagSelectorWidget::show()
{
     this->clear();
     QWidget::show();
}

void TagSelectorWidget::on_addTagPushed()
{
    auto tagText = addEdit_->text();
    this->addTag(tagText);
    addEdit_->clear();
}

void TagSelectorWidget::on_okayPushed()
{
     QStringList tags;
     auto buttons = tagButtomGroup_->buttons();
     foreach(QAbstractButton *button, buttons)
     {
         const QPushButton *push = static_cast<QPushButton*>(button);
         if ( push->isChecked() )
             tags << push->text();
     }
     emit tagsSelected(tags);
     this->close();
}

void TagSelectorWidget::keyPressEvent(QKeyEvent *event)
{
      if( event->key() == Qt::Key_Escape ){
          this->close();
      }
}

void TagSelectorWidget::clear()
{
    auto buttons = tagButtomGroup_->buttons();
    foreach(QAbstractButton *button, buttons)
    {
       QPushButton *push = static_cast<QPushButton*>(button);
       push->setChecked(false);
    }
}

void TagSelectorWidget::addTag(const QString& tagText)
{
   if ( !tagText.isEmpty() )
   {
       // avoid duplicates
       auto buttons = tagButtomGroup_->buttons();
       foreach(QAbstractButton *button, buttons)
       {
          const QPushButton *push = static_cast<QPushButton*>(button);
          if ( push->text() == tagText )
              return;
       }

       // add buttom to tagBox
       auto newTagButtom = new QPushButton(tagText);
       newTagButtom->setCheckable(true);
       tagsBox_->layout()->addWidget(newTagButtom);
       tagButtomGroup_->addButton(newTagButtom);

       // Insert into table, if it doesn't exist yet
       if ( !this->tagExist(tagText) )
       {
           QSqlField v1(tagColumnName_, QVariant::String);
           v1.setValue(QVariant(tagText));
           QSqlRecord rec;
           rec.append(v1);

           if( !table_->insertRecord(-1,rec) )
               qDebug() <<"ERROR:"<< table_->lastError();
           table_->submitAll();
       }
   }
}

QMap<QString, int> TagSelectorWidget::getTagIds() const
{
    QMap<QString, int> ids;
    for(int row=0; row < table_->rowCount(); row++) {
        QModelIndex id = table_->index(row,table_->fieldIndex("id"));
        QModelIndex name = table_->index(row,table_->fieldIndex(tagColumnName_));
        ids[name.data().toString()] = id.data().toInt();
    }
    return ids;
}

bool TagSelectorWidget::tagExist(const QString &tag) const
{
    for(int row=0; row < table_->rowCount(); row++) {
        QModelIndex index = table_->index(row,table_->fieldIndex(tagColumnName_));
        if ( tag == index.data().toString() )
            return true;
    }
    return false;
}
