/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#include "rz_inifile.h"

Inifile::Inifile()
{
}

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

Inifile::~Inifile() {}

QString Inifile::getInifile()
{
    return Inifile::pathToInifile;
}

void Inifile::Test()
{
}

void Inifile::createIni()
{
    myIni["DB_dev"]["enabled"] = "true";
    myIni["DB_dev"]["rdbms"] = "sqlite";
    myIni["DB_dev"]["dbname"] = "";
    myIni["DB_dev"]["file"] = "/var/{{ PROG_NAME }}/{{ DATE_TIME }}_{{ PROG_NAME }}.sqlite";
    myIni["DB_dev"]["hostname"] = "";
    myIni["DB_dev"]["password"] = "";
    myIni["DB_dev"]["port"] = "";
    myIni["DB_dev"]["username"] = "";

    myIni["DB_int"]["enabled"] = "false";
    myIni["DB_int"]["rdbms"] = "csv";
    myIni["DB_int"]["dbname"] = "";
    myIni["DB_int"]["file"] = "/var/{{ PROG_NAME }}/{{ DATE_TIME }}_{{ PROG_NAME }}.csv";
    myIni["DB_int"]["hostname"] = "";
    myIni["DB_int"]["password"] = "";
    myIni["DB_int"]["port"] = "";
    myIni["DB_int"]["username"] = "";

    myIni["DB_prod"]["enabled"] = "false";
    myIni["DB_prod"]["rdbms"] = "pg";
    myIni["DB_prod"]["dbname"] = "{{ PROG_NAME }}";
    myIni["DB_prod"]["file"] = "";
    myIni["DB_prod"]["hostname"] = "my-db-server.de";
    myIni["DB_prod"]["password"] = "ENV_SECRET_PROD_DB_PWD";
    myIni["DB_prod"]["port"] = 8154;
    myIni["DB_prod"]["username"] = "ENV_PROD_DB_USER";

    myIni["APP_dev"]["plugins_dir"] = "./{{ PROG_NAME }}/plugins";
    myIni["APP_dev"]["plugins_to_use"] = "pg, sqlite, csv, sql, webp, png, exif, iptc";

    myIni["APP_int"]["plugins_dir"] = "/usr/local/{{ PROG_NAME }}/plugins";
    myIni["APP_int"]["plugins_to_use"] = "csv, webp, exif, iptc";

    myIni["APP_prod"]["plugins_dir"] = "/usr/local/{{ PROG_NAME }}/plugins";
    myIni["APP_prod"]["plugins_to_use"] = "pg, webp, exif, iptc";

    myIni["Photos"]["output_formats"] = "webp, png";
    myIni["Photos"]["output_sizes"] = "480, 640, 800, 1024";
    myIni["Photos"]["copyright_default"] = "ZHENG Robert";
    myIni["Photos"]["images_source_path"] = "/var/data/{{ PROG_NAME }}/images";
    myIni["Photos"]["base_path_cut"] = "/var/data/{{ PROG_NAME }}/";
    myIni["Photos"]["base_path_replace"] = "{{ PROG_NAME }}/web_img/";
}

bool Inifile::saveIniToFile(QString &pathFile)
{
    try
    {
        myIni.save(pathFile.toStdString());
    }
    catch (...)
    {
        PLOG_WARNING << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::saveIniToFile(QString &path, QString &file)
{
    QString pathFile = path + "/" + file;

    try
    {
        myIni.save(pathFile.toStdString());
    }
    catch (...)
    {
        PLOG_WARNING << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::loadIni(QString &pathFile)
{
    Inifile::pathToInifile = pathFile;
    QFileInfo fi(pathFile);

    if (fi.exists() == false || fi.isReadable() == false)
    {
        PLOG_WARNING << "File doesn't exist or is not readable: " << pathFile;
        return false;
    }

    myIni.load(pathFile.toStdString());

    if (myIni.size() < 1)
    {
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

QString Inifile::getDbRdbms(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["rdbms"].as<std::string>().c_str();
}

QString Inifile::getDbName(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["dbname"].as<std::string>().c_str();
}

QString Inifile::getDbFile(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    std::string ret = rz_string_lib::replace(myIni[dbenv]["dbfile"].as<std::string>(),
                                             "{{ DATE_TIME }}",
                                             dt.getFormatedUtcDateTimeHuman("YYYY-MM-DD_HH-MM-SS"));
    ret = rz_string_lib::replace(ret, "{{ PROG_NAME }}", ProgName.toStdString());
    return ret.c_str();
}

QString Inifile::getDbHostname(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    std::string ret = rz_string_lib::replace(myIni[dbenv]["hostname"].as<std::string>(),
                                             "{{ DATE_TIME }}",
                                             dt.getFormatedUtcDateTimeHuman("YYYY-MM-DD_HH-MM-SS"));
    ret = rz_string_lib::replace(ret, "{{ PROG_NAME }}", ProgName.toStdString());
    return ret.c_str();
}

QString Inifile::getDbPassword(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    std::string ret = myIni[dbenv]["password"].as<std::string>().c_str();
    ret = rz_string_lib::replace(ret, "{{ PROG_NAME }}", ProgName.toStdString());
    return ret.c_str();
}

int Inifile::getDbPort(QString &env)
{
    std::string dbenv = "DB_" + env.toStdString();
    return myIni[dbenv]["port"].as<int>();
}

QString Inifile::getDbUsername(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    std::string ret = myIni[dbenv]["username"].as<std::string>().c_str();
    ret = rz_string_lib::replace(ret, "{{ PROG_NAME }}", ProgName.toStdString());
    return ret.c_str();
}

QString Inifile::getDbSqlFile(QString &env, QString &ProgName)
{
    std::string dbenv = "DB_" + env.toStdString();
    std::string ret = rz_string_lib::replace(myIni[dbenv]["sql_to_file"].as<std::string>(),
                                             "{{ DATE_TIME }}",
                                             dt.getFormatedUtcDateTimeHuman("YYYY-MM-DD_HH-MM-SS"));
    ret = rz_string_lib::replace(ret, "{{ PROG_NAME }}", ProgName.toStdString());
    return ret.c_str();
}

QString Inifile::getPhotosOutputFormat()
{
    return myIni["Photos"]["output_format"].as<std::string>().c_str();
}

QString Inifile::getPhotosCopyrightDefault()
{
    return myIni["Photos"]["copyright_default"].as<std::string>().c_str();
}

QString Inifile::getPhotosBasePathCut()
{
    return myIni["Photos"]["base_path_cut"].as<std::string>().c_str();
}

QStringList Inifile::getPhotosOutputSizes()
{
    std::string extensionsStr = myIni["Photos"]["output_sizes"].as<std::string>();
    QString qextensionsStr = extensionsStr.c_str();
    return (qextensionsStr.remove(" ").split(",", Qt::SkipEmptyParts));
}

QString Inifile::getPluginsDir(QString &env, QString &ProgName)
{
    std::string appenv = "APP_" + env.toStdString();
    std::string ret = rz_string_lib::replace(myIni[appenv]["plugins_dir"].as<std::string>(),
                                             "{{ PROG_NAME }}",
                                             ProgName.toStdString());
    return ret.c_str();
}

QStringList Inifile::getPluginsToUse(QString &env)
{
    std::string appenv = "APP_" + env.toStdString();
    std::string extensionsStr = myIni[appenv]["plugins_to_use"].as<std::string>();
    QString pluginsStr = extensionsStr.c_str();
    return (pluginsStr.remove(" ").split(",", Qt::SkipEmptyParts));
}

void Inifile::listIniEntries(QT_snippets &qt_snippets)
{
    std::cout << "Parsed ini contents" << std::endl;
    std::cout << "Has " << myIni.size() << " sections" << std::endl;
    for (const auto &sectionPair : myIni)
    {
        const std::string &sectionName = sectionPair.first;
        const ini::IniSection &section = sectionPair.second;

        std::string out = "\nSection '" + sectionName + "' has " + std::to_string(section.size())
                          + " fields";
        int len = out.length();

        //std::cout << "Section '" << sectionName << "' has " << section.size() << " fields" << std::endl;
        std::cout << out << std::endl;
        std::cout << std::setfill('*') << std::setw(len) << "\n";

        for (const auto &fieldPair : sectionPair.second) {
            const std::string &fieldName = fieldPair.first;
            const ini::IniField &field = fieldPair.second;
            std::string ret = rz_string_lib::replace(field.as<std::string>(),
                                                     "{{ PROG_NAME }}",
                                                     qt_snippets.getProgName().toStdString());
            ret = rz_string_lib::replace(ret,
                                         "{{ DATE_TIME }}",
                                         dt.getFormatedUtcDateTimeHuman("YYYY-MM-DD_HH-MM-SS"));
            std::cout << fieldName << " = " << ret << std::endl;
        }
    }
}
