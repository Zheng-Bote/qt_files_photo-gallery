#include "rz_pg_db.h"

PgDb::PgDb(Inifile &iniConfig, QString &env)
{
    PgDb::db = QSqlDatabase::addDatabase("QPSQL", "source");
    PgDb::db.setHostName(iniConfig.getDbHostname(env));
    PgDb::db.setDatabaseName(iniConfig.getDbName(env));
    PgDb::db.setUserName(iniConfig.getDbUsername(env));
    PgDb::db.setPassword(iniConfig.getDbPassword(env));
    PgDb::db.setPort(iniConfig.getDbPort(env));

    if (!PgDb::db.open()) {
        PLOG_ERROR << "Connection to DB failed!";
        exit(EXIT_FAILURE);
    } else {
        PLOG_INFO << "Connected to DB";
    }
}

PgDb::~PgDb()
{
    PgDb::db.close();
}

void PgDb::closeDb()
{
    PgDb::db.close();
    PLOG_INFO << "Disconnected from DB";
}
