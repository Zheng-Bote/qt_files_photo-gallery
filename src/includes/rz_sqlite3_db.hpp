/**
 * @file rz_sqlite3_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for SQLITE3
 * @details simple class lib for SQLite3
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QtSql>
#include <memory>

#include "plog/Log.h"

#include "rz_inifile.hpp"

class SqliteDb
{
public:
    SqliteDb();
    SqliteDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName);
    ~SqliteDb();

    bool connectDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName);
    bool createTables();

    void closeDb();

private:
    QSqlDatabase db;
};
