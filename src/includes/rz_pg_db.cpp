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
        qCritical() << "Connection to DB failed!";
        exit(EXIT_FAILURE);
    } else {
        qInfo() << "Connected to DB";
    }
}

PgDb::~PgDb()
{
    PgDb::db.close();
}

void PgDb::closeDb()
{
    PgDb::db.close();
    qInfo() << "Disconnected from DB";
}
