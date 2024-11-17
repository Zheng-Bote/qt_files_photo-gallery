/**
 * @file rz_pg_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for PostgreSQL
 * @details simple class lib for pg
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#include "rz_pg_db.hpp"

PgDb::PgDb() {}

PgDb::PgDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName)
{
    PgDb::connectDb(sptr_ini_config, env, ProgName);
}

PgDb::~PgDb()
{
    PgDb::db.close();
}

bool PgDb::connectDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName)
{
    bool connectStatus = false;
    PgDb::db = QSqlDatabase::addDatabase("QPSQL", "source");
    PgDb::db.setHostName(sptr_ini_config->getDbHostname(env, ProgName));
    PgDb::db.setDatabaseName(sptr_ini_config->getDbName(env));
    PgDb::db.setUserName(sptr_ini_config->getDbUsername(env, ProgName));
    PgDb::db.setPassword(sptr_ini_config->getDbPassword(env, ProgName));
    PgDb::db.setPort(sptr_ini_config->getDbPort(env));

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
