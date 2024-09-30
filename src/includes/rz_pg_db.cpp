/**
 * @file rz_pg_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for PostgreSQL
 * @details simple class lib for pg
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 * @mainpage https://github.com/Zheng-Bote/
 */

#include "rz_pg_db.h"

PgDb::PgDb() {}

PgDb::PgDb(Inifile &iniConfig, QString &env)
{
    PgDb::connectDb(iniConfig, env);
}

PgDb::~PgDb()
{
    PgDb::db.close();
}

bool PgDb::connectDb(Inifile &iniConfig, QString &env)
{
    bool connectStatus = false;
    PgDb::db = QSqlDatabase::addDatabase("QPSQL", "source");
    PgDb::db.setHostName(iniConfig.getDbHostname(env));
    PgDb::db.setDatabaseName(iniConfig.getDbName(env));
    PgDb::db.setUserName(iniConfig.getDbUsername(env));
    PgDb::db.setPassword(iniConfig.getDbPassword(env));
    PgDb::db.setPort(iniConfig.getDbPort(env));

    if (!PgDb::db.open())
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

void PgDb::closeDb()
{
    PgDb::db.close();
    PLOG_INFO << "Disconnected from DB";
}
