/**
 * @file rz_initfile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief lib to CRUD inifile
 * @details simple class for reading and writing the inifile
 * @version 0.7.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023 ZHENG Robert
 *
 */

#include "rz_inifile.h"

Inifile::Inifile()
{}

Inifile::Inifile(QString &progname)
{
    QString pathFile = progname + ".ini";
    Inifile::loadIni(pathFile);
}

Inifile::Inifile(QString &path, QString &file)
{
    QString pathFile = path + "/" + file;
    Inifile::loadIni(pathFile);
}

Inifile::~Inifile(){}

QString Inifile::getInifile()
{
    return Inifile::pathToInifile;
}

void Inifile::Test()
{

}

void Inifile::createIni()
{
    myIni["DB_dev"]["enabled"] = "";
    myIni["DB_dev"]["rdbms"] = "";
    myIni["DB_dev"]["dbname"] = "";
    myIni["DB_dev"]["dbfile"] = "";
    myIni["DB_dev"]["hostname"] = "";
    myIni["DB_dev"]["password"] = "";
    myIni["DB_dev"]["port"] = "";
    myIni["DB_dev"]["username"] = "";
    myIni["DB_dev"]["sql_file"] = "";

    myIni["DB_int"]["enabled"] = "";
    myIni["DB_int"]["rdbms"] = "";
    myIni["DB_int"]["dbname"] = "";
    myIni["DB_int"]["dbfile"] = "";
    myIni["DB_int"]["hostname"] = "";
    myIni["DB_int"]["password"] = "";
    myIni["DB_int"]["port"] = "";
    myIni["DB_int"]["username"] = "";
    myIni["DB_int"]["sql_file"] = "";

    myIni["DB_prod"]["enabled"] = "";
    myIni["DB_prod"]["rdbms"] = "";
    myIni["DB_prod"]["dbname"] = "";
    myIni["DB_prod"]["dbfile"] = "";
    myIni["DB_prod"]["hostname"] = "";
    myIni["DB_prod"]["password"] = "";
    myIni["DB_prod"]["port"] = "";
    myIni["DB_prod"]["username"] = "";
    myIni["DB_prod"]["sql_file"] = "";

    myIni["APP_dev"]["Logifle"] = "";
    myIni["APP_int"]["Logifle"] = "";
    myIni["APP_prod"]["Logifle"] = "";
}

bool Inifile::saveIniToFile(QString &pathFile)
{
    try {
        myIni.save(pathFile.toStdString());
    } catch (...) {
        PLOG_WARNING << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::saveIniToFile(QString &path, QString &file)
{
    QString pathFile = path + "/" + file;

    try {
        myIni.save(pathFile.toStdString());
    } catch (...) {
        PLOG_WARNING << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::loadIni(QString &pathFile)
{
    Inifile::pathToInifile = pathFile;
    QFileInfo fi(pathFile);

    if(fi.exists() == false || fi.isReadable() == false) {
        PLOG_WARNING << "File doesn't exist or is not readable: " << pathFile;
        return false;
    }

    myIni.load(pathFile.toStdString());

    if(myIni.size() < 1) {
        PLOG_WARNING << "wrong INI size, should be at least 1 section (maybe not readable?): "
                     << myIni.size();
        return false;
    }
    return true;
}

bool Inifile::getDbEnabled(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["enabled"].as<bool>();
}

QString Inifile::getDbRdbms(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["rdbms"].as<std::string>().c_str();
}

QString Inifile::getDbName(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["dbname"].as<std::string>().c_str();
}

QString Inifile::getDbFile(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["dbfile"].as<std::string>().c_str();
}

QString Inifile::getDbHostname(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["hostname"].as<std::string>().c_str();
}

QString Inifile::getDbPassword(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["password"].as<std::string>().c_str();
}

int Inifile::getDbPort(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["port"].as<int>();
}

QString Inifile::getDbUsername(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["username"].as<std::string>().c_str();
}

QString Inifile::getDbSqlFile(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["sql_to_file"].as<std::string>().c_str();
}

void Inifile::listIniEntries()
{
    std::cout << "Parsed ini contents" << std::endl;
    std::cout << "Has " << myIni.size() << " sections" << std::endl;
    for(const auto &sectionPair : myIni)
    {
        const std::string &sectionName = sectionPair.first;
        const ini::IniSection &section = sectionPair.second;
        std::cout << "Section '" << sectionName << "' has " << section.size() << " fields" << std::endl;

        for(const auto &fieldPair : sectionPair.second)
        {
            const std::string &fieldName = fieldPair.first;
            const ini::IniField &field = fieldPair.second;
            std::cout << "  Field '" << fieldName << "' Value '" << field.as<std::string>() << "'" << std::endl;
        }
    }
}





