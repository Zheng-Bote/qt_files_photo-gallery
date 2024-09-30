/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 * @mainpage https://github.com/Zheng-Bote/
 */

#pragma once

#include <QString>
#include <iostream>
#include <QDir>
#include <QFile>

#include "plog/Log.h"

/* https://github.com/Rookfighter/inifile-cpp */
#include "inicpp.h"

class Inifile
{
public:
    Inifile();
    Inifile(QString &progname);
    Inifile(QString &path, QString &file);
    ~Inifile();

    void Test();
    void createIni();
    bool saveIniToFile(QString &pathFile);
    bool saveIniToFile(QString &path, QString &file);
    bool loadIni(QString &pathFile);

    // DB
    bool getDbEnabled(QString &env);
    QString getDbRdbms(QString &env);
    QString getDbName(QString &env);
    QString getDbFile(QString &env);
    QString getDbHostname(QString &env);
    QString getDbPassword(QString &env);
    int getDbPort(QString &env);
    QString getDbUsername(QString &env);
    QString getDbSqlFile(QString &env);

    void listIniEntries();
    QString getInifile();

    QString pathToInifile;

private:
    ini::IniFile myIni;
};
