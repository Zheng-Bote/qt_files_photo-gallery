#pragma once

#include <QDebug>
#include <QtSql>

#include "Includes/rz_inifile.h"

class PgDb
{
public:
    PgDb(Inifile &iniConfig);
    ~PgDb();

    void closeDb();

private:
    QSqlDatabase db;
};
