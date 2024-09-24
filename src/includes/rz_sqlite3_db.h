#pragma once

#include <QtSql>

#include "plog/Log.h"

#include "rz_inifile.h"

class SqliteDb
{
public:
    SqliteDb(Inifile &iniConfig, QString &env);
    ~SqliteDb();

    void closeDb();

private:
    QSqlDatabase db;
};
