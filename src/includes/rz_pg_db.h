/**
 * @file rz_pg_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for PostgreSQL
 * @details simple class lib for pg
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QtSql>

#include "plog/Log.h"

#include "rz_inifile.h"

class PgDb
{
public:
    PgDb();
    PgDb(Inifile &iniConfig, QString &env, QString &ProgName);
    ~PgDb();

    bool connectDb(Inifile &iniConfig, QString &env, QString &ProgName);
    void closeDb();

private:
    QSqlDatabase db;
};
