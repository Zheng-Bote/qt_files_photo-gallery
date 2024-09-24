#include "rz_sqlite3_db.h"

SqliteDb::SqliteDb(Inifile &iniConfig, QString &env)
{
    SqliteDb::db = QSqlDatabase::addDatabase("QSQLITE", "source");
    SqliteDb::db.setDatabaseName(iniConfig.getDbFile(env));

    if (!SqliteDb::db.open()) {
        PLOG_ERROR << "Connection to DB failed!";
        exit(EXIT_FAILURE);
    } else {
        PLOG_INFO << "Connected to DB";
    }
}

SqliteDb::~SqliteDb()
{
    SqliteDb::db.close();
}

void SqliteDb::closeDb()
{
    SqliteDb::db.close();
    PLOG_INFO << "Disconnected from DB";
}
