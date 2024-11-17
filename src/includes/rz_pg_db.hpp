/**
 * @file rz_pg_db.hpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple classlib for PostgreSQL
 * @details simple class lib for pg
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QtSql>
#include <memory>

#include "plog/Log.h"

#include "rz_inifile.hpp"

class PgDb
{
public:
    PgDb();
    PgDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName);
    ~PgDb();

    bool connectDb(std::shared_ptr<Inifile> sptr_ini_config, QString &env, QString &ProgName);
    void closeDb();

private:
    QSqlDatabase db;
};
