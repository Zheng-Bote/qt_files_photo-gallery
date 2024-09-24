#pragma once

#include <QtSql>

#include "plog/Log.h"

#include "rz_inifile.h"

class PgDb
{
public:
    PgDb(Inifile &iniConfig, QString &env);
    ~PgDb();

    void closeDb();

private:
    QSqlDatabase db;
};
