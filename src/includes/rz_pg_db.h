#pragma once

#include <QtSql>

#include "plog/Log.h"

#include "rz_inifile.h"

class PgDb
{
public:
    PgDb();
    PgDb(Inifile &iniConfig, QString &env);
    ~PgDb();

    bool connectDb(Inifile &iniConfig, QString &env);
    void closeDb();

private:
    QSqlDatabase db;
};
