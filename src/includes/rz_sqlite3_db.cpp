/**
 * @file rz_sqlite3_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for SQLITE3
 * @details simple class lib for SQLite3
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 * @mainpage https://github.com/Zheng-Bote/
 */

#include "rz_sqlite3_db.h"

SqliteDb::SqliteDb() {}

SqliteDb::SqliteDb(Inifile &iniConfig, QString &env)
{
    SqliteDb::connectDb(iniConfig, env);
}

SqliteDb::~SqliteDb()
{
    SqliteDb::db.close();
}

bool SqliteDb::connectDb(Inifile &iniConfig, QString &env)
{
    bool connectStatus = false;
    SqliteDb::db = QSqlDatabase::addDatabase("QSQLITE");
    SqliteDb::db.setDatabaseName(iniConfig.getDbFile(env));

    if (!SqliteDb::db.open())
    {
        PLOG_ERROR << "Connection to DB failed!";
        connectStatus = false;
    }
    else
    {
        PLOG_INFO << "Connected to DB";
        connectStatus = true;
    }
    return connectStatus;
}

bool SqliteDb::createTables()
{
    bool connectStatus = false;
    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS photos("
                  "ID              integer primary key  NOT NULL, "
                  "path            TEXT                 NOT NULL, "
                  "file_name       TEXT                 NOT NULL );");

    if (query.exec())
    {
        connectStatus = true;
    }
    else
    {
        PLOG_ERROR << "Create table Photo failed: " << query.lastError().text();
    }

    query.prepare("CREATE TABLE IF NOT EXISTS iptc("
                  "ID              integer UNIQUE  NOT NULL, "
                  "DateCreated     CHARACTER(8)    DEFAULT NULL, "
                  "TimeCreated     CHARACTER(11)   DEFAULT NULL, "
                  "City            VARCHAR(32)     DEFAULT NULL, "
                  "Sublocation     VARCHAR(32)     DEFAULT NULL, "
                  "StateProvince   VARCHAR(32)     DEFAULT NULL, "
                  "CountryCode     CHARACTER(2)    DEFAULT NULL, "
                  "Country         VARCHAR(64)     DEFAULT NULL, "
                  "Headline        VARCHAR(256)    DEFAULT NULL, "
                  "CopyrightNotice VARCHAR(128)    DEFAULT NULL, "
                  "Contact         VARCHAR(128)    DEFAULT NULL, "
                  "Capytion        TEXT          DEFAULT 0 );");

    if (query.exec())
    {
        connectStatus = true;
    }
    else
    {
        PLOG_ERROR << "Create table IPTC failed: " << query.lastError().text();
    }

    query.prepare("CREATE INDEX IF NOT EXISTS index_id ON iptc (ID ASC);");
    if (query.exec())
    {
        connectStatus = true;
    }
    else
    {
        PLOG_WARNING << "Create index failed: " << query.lastError().text();
    }

    query.prepare("CREATE TRIGGER IF NOT EXISTS trigger_photo_delete after delete on photos begin "
                  "delete from "
                  "iptc where id = OLD.id; END");
    if (query.exec())
    {
        connectStatus = true;
    }
    else
    {
        PLOG_WARNING << "Create trigger failed: " << query.lastError().text();
    }

    return connectStatus;
}

void SqliteDb::closeDb()
{
    SqliteDb::db.close();
    PLOG_INFO << "Disconnected from DB";
}
