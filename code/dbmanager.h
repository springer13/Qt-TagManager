#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

// Singelton
class DbManager
{
public:

    static DbManager* Instance()
    {
        if (pInstance_ == nullptr)
            pInstance_ = new DbManager;
        return pInstance_;
    }

    DbManager(const DbManager&) = delete;

    const QSqlDatabase* getDatabase() { return &db_; }

private:
    DbManager();
    ~DbManager();

    /************************************
     * Member functions
     ************************************/
    void initDatabase();

    /************************************
     * Member variables
     ************************************/
    static DbManager* pInstance_;
    QSqlDatabase db_;
};

#endif // DBMANAGER_H
