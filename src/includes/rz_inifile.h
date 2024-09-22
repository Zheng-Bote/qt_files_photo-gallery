#pragma once

#include <QString>
#include <iostream>
#include <QDir>
#include <QFile>

#include <plog/Log.h>

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

    // Sql
    QString getSqlHostname();
    int getSqlPort();
    QString getSqlDbName();
    QString getSqlUsername();
    QString getSqlPassword();
    bool checkSqlMeta();

    void listIniEntries();
    QString getInifile();

    QString pathToInifile;

private:
    ini::IniFile myIni;
};


