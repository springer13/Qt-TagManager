#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>

#include "dbmanager.h"

DbManager* DbManager::pInstance_ = nullptr;

DbManager::DbManager()
{
   db_ = QSqlDatabase::addDatabase("QSQLITE");
   this->initDatabase();

}

DbManager::~DbManager()
{
   if (db_.open()) {
       db_.close();
   }
}

void DbManager::initDatabase()
{
    db_.setDatabaseName(":memory:"); // provide path to your database here!
    if (!db_.open()) {
       QMessageBox::critical(0, "Cannot open database",
                "Cannot open SQL database.", QMessageBox::Cancel);
    }

    /********************************
     * Create Tables
     ********************************/
    QSqlQuery query;
    auto success = query.exec("CREATE TABLE IF NOT EXISTS 'tag' ("
    "  'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT ,"
    "  'name' VARCHAR(45) NULL);");
    success |= query.exec("insert into tag (name) values('Politics');");
    success |= query.exec("insert into tag (name) values('Economics');");
    success |= query.exec("insert into tag (name) values('Science');");

    if (!success)
        QMessageBox::critical(0,"Error","Could not create SQL tables: " +
                              query.lastError().text());
}








