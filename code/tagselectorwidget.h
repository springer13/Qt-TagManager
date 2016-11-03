#ifndef TAGSELECTORWIDGET_H
#define TAGSELECTORWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QMap>

/**
 * @brief The TagSelectorWidget class is used to select a subset of the available tags. Moreover, it can also add new tags to the database.
 */
class TagSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TagSelectorWidget(const QString &tableName,
                               const QString &tagColumnName, QWidget *parent = 0);

    /**
     * @brief getTagIds maps each tag-name to its tag-id
     * @return A mapping for each tag-name to its tag-id (e.g., map["Politics"]=1)
     */
    QMap<QString, int> getTagIds() const;
signals:
    void tagsSelected(const QStringList &tags);

public slots:
    void show();
private slots:
    void on_addTagPushed();
    void on_okayPushed();
private:
    void setupDatabase();
    void keyPressEvent(QKeyEvent *);
    void addTag(const QString& tagText);
    void clear();
    bool tagExist(const QString &tag) const; //< checks if the given tag is already present in the table

    /*******************************
     * Member variables
     *******************************/
    // non-ui related variables
    QSqlRelationalTableModel *table_;
    QString tagColumnName_; //< name of the column which corresponds to the tag
    QString tableName_; //< name of the column which corresponds to the tag

    // ui related variables
    QWidget *tagsBox_;
    QButtonGroup *tagButtomGroup_;
    QLabel *addLabel_; QLineEdit *addEdit_;
    QPushButton *addNewTag_;
    QPushButton *okay_;
    QPushButton *cancel_;
};

#endif // TAGSELECTORWIDGET_H
