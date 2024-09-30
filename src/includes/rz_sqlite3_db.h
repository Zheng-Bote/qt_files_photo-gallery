/**
 * @file rz_sqlite3_db.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for SQLITE3
 * @details simple class lib for SQLite3
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 * @mainpage https://github.com/Zheng-Bote/
 */

#pragma once

#include <QtSql>

#include "plog/Log.h"

#include "rz_inifile.h"

class SqliteDb
{
public:
    SqliteDb();
    SqliteDb(Inifile &iniConfig, QString &env);
    ~SqliteDb();

    bool connectDb(Inifile &iniConfig, QString &env);
    bool createTables();

    void closeDb();

private:
    QSqlDatabase db;
};
