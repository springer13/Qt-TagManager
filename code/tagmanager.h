#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QWidget>
#include <QGroupBox>
#include <QSqlRelationalTableModel>

#include "flowlayout.h"
#include "mytagbutton.h"
#include "tagselectorwidget.h"

class TagManager : public QWidget
{
    Q_OBJECT
public:
    explicit TagManager(const QString& tableName,
                        const QString& tagColumnName, QWidget *parent = 0 );

    /**
     * @brief getSelectedTagNames returns the selected tag names (w.r.t. the specified table)
     */
    QList<QString> getSelectedTagNames() const;
    /**
     * @brief getSelectedTagIds returns the selected tag Ids (w.r.t. the specified table)
     */
    QList<int> getSelectedTagIds() const;
signals:

private slots:
    void on_addTag(const QStringList &tags);
    void deleteTag(MyTagButton*);
private:
    bool tagExists(const QString &tag) const;
    void addTag(const QString &tag);

    /*******************************
     * Member variables
     *******************************/
    // non-ui related variables
    std::list<MyTagButton *> myTags_;

    // ui related variables
    QPushButton *addTag_;
    TagSelectorWidget *tagSelectorWidget_;
    QWidget *tagsBox_;

};

#endif // TAGMANAGER_H
