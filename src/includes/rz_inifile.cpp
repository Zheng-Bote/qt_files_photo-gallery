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
    myIni["SQL"]["hostname"] = "   # <database server>";
    myIni["SQL"]["port"] = "       # <database server port>";
    myIni["SQL"]["dbname"] = "     # <my database>";
    myIni["SQL"]["username"] = "   # <database user>";
    myIni["SQL"]["password"] = "   # <database user password>";
}

bool Inifile::saveIniToFile(QString &pathFile)
{
    try {
        myIni.save(pathFile.toStdString());
    } catch (...) {
        qWarning() << "Write Ini failed: " << pathFile;
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
        qWarning() << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::loadIni(QString &pathFile)
{
    Inifile::pathToInifile = pathFile;
    QFileInfo fi(pathFile);

    if(fi.exists() == false || fi.isReadable() == false) {
        qFatal() << "File doesn't exist or is not readable: " << pathFile;
        return false;
    }

    myIni.load(pathFile.toStdString());

    if(myIni.size() < 1) {
        qFatal() << "wrong INI size, should be at least 1 section (maybe not readable?): " << myIni.size();
        return false;
    }
    return true;
}

// DB
QString Inifile::getSqlHostname()
{
    std::string val = myIni["SQL"]["hostname"].as<std::string>();
    return val.c_str();
}
int Inifile::getSqlPort()
{
    int val = myIni["SQL"]["port"].as<int>();
    return val;
}
QString Inifile::getSqlDbName()
{
    std::string val = myIni["SQL"]["dbname"].as<std::string>();
    return val.c_str();
}
QString Inifile::getSqlUsername()
{
    std::string val = myIni["SQL"]["username"].as<std::string>();
    return val.c_str();
}
QString Inifile::getSqlPassword()
{
    std::string val = myIni["SQL"]["password"].as<std::string>();
    return val.c_str();
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

bool Inifile::checkSqlMeta()
{
    std::string hostname = myIni["SQL"]["hostname"].as<std::string>();
    int port = myIni["SQL"]["port"].as<int>();
    std::string dbname = myIni["SQL"]["dbname"].as<std::string>();
    std::string username = myIni["SQL"]["username"].as<std::string>();
    std::string password = myIni["SQL"]["password"].as<std::string>();

    if(hostname.empty() == true) {
        qCritical() << "No SQL hostname defined";
        return false;
    }
    if(port < 80) {
        qCritical() << "No SQL port defined";
        return false;
    }
    if(dbname.empty() == true) {
        qCritical() << "No SQL database defined";
        return false;
    }
    if(username.empty() == true) {
        qCritical() << "No SQL username defined";
        return false;
    }
    if(password.empty() == true) {
        qCritical() << "No SQL password defined";
        return false;
    }

    return true;
}




