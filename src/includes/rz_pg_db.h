#pragma once

#include <QtSql>

#include <plog/Log.h>

#include "rz_inifile.h"

class PgDb
{
public:
    PgDb(Inifile &iniConfig);
    ~PgDb();

    void closeDb();

private:
    QSqlDatabase db;
};
