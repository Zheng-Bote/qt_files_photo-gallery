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
