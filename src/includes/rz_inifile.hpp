/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QDir>
#include <QFile>
#include <QString>
#include <iostream>
#include <memory>

#include "plog/Log.h"

/* https://github.com/Rookfighter/inifile-cpp */
#include "inicpp.h"

#include "rz_datetime.hpp"
#include "rz_qt_snippets.hpp"

#include "rz_string_lib.hpp"

class Inifile
{
public:
    Inifile();
    Inifile(QString &progname);
    Inifile(QString &path, QString &file);
    ~Inifile();

    void Test();
    void createIni();
    std::tuple<bool, std::string> saveIniToFile(QString &pathFile);
    std::tuple<bool, std::string> saveIniToFile(QString &path, QString &file);
    std::tuple<bool, std::string> loadIni(QString &pathFile);

    // DB
    bool getDbEnabled(QString &env);
    QString getDbRdbms(QString &env);
    QString getDbName(QString &env);
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
    QString getPluginsDir(const QString &env, const QString &ProgName);
    QStringList getPluginsToUse(const QString &env);

    void listIniEntries(std::shared_ptr<QtSnippets> sptr_qt_snippets);
    QString getInifile();

private:
    ini::IniFile myIni;
    //DateTime dt;
    std::shared_ptr<DateTime> sptr_dt;

    QString pathToInifile;
};
