#include <QHBoxLayout>
#include <QStringList>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QScrollArea>

#include "tagmanager.h"

TagManager::TagManager(const QString& tableName,
                       const QString& tagColumnName, QWidget *parent) : QWidget(parent)
{
    // allocate
    addTag_ =  new QPushButton("+");
    tagSelectorWidget_ = new TagSelectorWidget(tableName, tagColumnName);
    tagsBox_ = new QWidget;
    tagsBox_->setLayout(new FlowLayout);

    // scroll area
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    scrollArea->setGeometry( 10, 10, 200, 100 );
    scrollArea->setMinimumSize(200,10);
    scrollArea->setMaximumHeight(150);
    scrollArea->setWidget(tagsBox_);

    // setup ui
    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(new QLabel("Tags:"));
    this->layout()->addWidget(scrollArea);
    this->layout()->addWidget(addTag_);

    // connect
    connect(addTag_, &QPushButton::clicked,
            tagSelectorWidget_, &TagSelectorWidget::show);
    connect(tagSelectorWidget_, &TagSelectorWidget::tagsSelected,
            this, &TagManager::on_addTag);
}

QList<QString> TagManager::getSelectedTagNames() const
{
    QList<QString> tagNames;
    for(auto tagButton : myTags_)
        tagNames.push_back(tagButton->text());
    return tagNames;
}

QList<int> TagManager::getSelectedTagIds() const
{
    auto tagNames = this->getSelectedTagNames();
    auto tagIds = tagSelectorWidget_->getTagIds();
    QList<int> ids;
    for(auto name: tagNames){
        ids.append(tagIds[name]);
    }
    return ids;
}

void TagManager::on_addTag(const QStringList &tags){
    QString tag;
    foreach (tag, tags) {
        if ( !this->tagExists(tag) )
           this->addTag(tag);
    }
}

void TagManager::deleteTag(MyTagButton* tag)
{
    tagsBox_->layout()->removeWidget(tag);
    myTags_.remove(tag);
    delete tag;
}

bool TagManager::tagExists(const QString &tag) const
{
    for(auto tagButton : myTags_)
        // avoid duplicates
        if ( tagButton->text() == tag )
            return true;
    return false;
}

void TagManager::addTag(const QString &text)
{
    auto newTag = new MyTagButton;
    newTag->setText(text);
    myTags_.push_back(newTag);
    tagsBox_->layout()->addWidget(newTag);

    connect(newTag, &MyTagButton::clicked,
            this, &TagManager::deleteTag);
}
