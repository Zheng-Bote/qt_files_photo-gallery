#include "rz_pg_db.h"

PgDb::PgDb(Inifile &iniConfig)
{
    PgDb::db = QSqlDatabase::addDatabase("QPSQL", "source");
    PgDb::db.setHostName(iniConfig.getSqlHostname());
    PgDb::db.setDatabaseName(iniConfig.getSqlDbName());
    PgDb::db.setUserName(iniConfig.getSqlUsername());
    PgDb::db.setPassword(iniConfig.getSqlPassword());
    PgDb::db.setPort(iniConfig.getSqlPort());

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
