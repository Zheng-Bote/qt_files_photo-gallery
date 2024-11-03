/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QString>
#include <iostream>
#include <QDir>
#include <QFile>

#include "plog/Log.h"

/* https://github.com/Rookfighter/inifile-cpp */
#include "inicpp.h"

#include "rz_datetime.h"
#include "rz_qt_snippets.h"
#include "rz_string_lib.h"

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
    QString getDbRdbms(QString &env, QString &ProgName);
    QString getDbName(QString &env, QString &ProgName);
    QString getDbFile(QString &env, QString &ProgName);
    QString getDbHostname(QString &env, QString &ProgName);
    QString getDbPassword(QString &env, QString &ProgName);
    int getDbPort(QString &env);
    QString getDbUsername(QString &env, QString &ProgName);
    QString getDbSqlFile(QString &env, QString &ProgName);
    // Photos
    QString getPhotosOutputFormat();
    QString getPhotosCopyrightDefault();
    QString getPhotosBasePathCut();
    QStringList getPhotosOutputSizes();
    // App
    QString getPluginsDir(QString &env, QString &ProgName);
    QStringList getPluginsToUse(QString &env);

    void listIniEntries(QT_snippets &qt_snippets);
    QString getInifile();

    QString pathToInifile;

private:
    ini::IniFile myIni;
    DateTime dt;
};
