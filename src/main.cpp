/**
 * @file main.cpp
 * @author ZHENG Robert (https://github.com/Zheng-Bote/qt_files_photo-gallery)
 * @brief QT6 CXX20 console app to add photos to DB
 * @details QT6 CXX20 console app to convert photos, collect Exif/IPTC and add metadata to DB
 * @date 2024-09-19
 * @copyright Copyright (c) 2024 ZHENG Robert
 */

// ToDo: options logfile
// ToDo: configure default ini to /etc/<...>/... ???

#include <QCoreApplication>
#include <QDebug>

#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Init.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Log.h"

#include "configured/rz_config.h"
#include "cxxopts.hpp"
#include "includes/rz_inifile.h"
#include "includes/rz_pg_db.h"
#include "includes/rz_readdir.h"
#include "includes/rz_sqlite3_db.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    QCoreApplication::setApplicationName("files_to_photo-gallery");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationDomain("https://github.com/Zheng-Bote/qt_files_photo-gallery");
*/
    std::string prog = argv[0];

    // default inifile
    QString inifile = prog.c_str();
    inifile.append(".ini");

    // default logging
    QString logfile = prog.c_str();
    logfile.append(".log");

    // default env
    QString env = "dev";

    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logfile.toStdString().c_str(),
                                                                      5000,
                                                                      3);
    plog::init(plog::debug, &fileAppender);
    // fileAppender.setFileName("SetFileNameBBB.log");
    plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::get()->addAppender(&consoleAppender); // Also add logging to the console.

    /**
     * @brief options for program
     */
    cxxopts::Options options(prog, QCoreApplication::applicationName().toStdString());
    options.set_width(100).add_options()("a,auto", "run with default Inifile: " + prog + ".ini")(
        "c,create",
        "create Inifile",
        cxxopts::value<std::string>()
            ->implicit_value("<pathTo/inifile>")
            ->default_value(prog + ".ini"))("e,env",
                                            "Environment <dev> <int> <prod>",
                                            cxxopts::value<std::string>()->default_value("dev"))

        ("i,ini", "use Inifile", cxxopts::value<std::string>()->implicit_value("<pathTo/inifile>"))(
            "l,listini",
            "list Inifile",
            cxxopts::value<std::string>()
                ->implicit_value("<pathTo/inifile>")
                ->default_value(prog + ".ini"))("v,version",
                                                "Print program and version")("h, help",
                                                                             "Print help");

    /**
     * @brief parse prog parameters
     */

    auto result = options.parse(argc, argv);

    // for Dev
    //    if (argc <= 1 || result.count("help")) {
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        std::cout << PROG_NAME << " v" << PROG_VERSION << " " << PROG_HOMEPAGE << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (result.count("version"))
    {
        std::cout << QCoreApplication::applicationName().toStdString() << "-"
                  << QCoreApplication::applicationVersion().toStdString() << std::endl;
        exit(0);
    }

    if (result.count("auto"))
    {
        inifile = prog.c_str();
        inifile.append(".ini");
    }

    if (result.count("env"))
    {
        std::string input = result["env"].as<std::string>();

        if (input.compare("dev") == 0)
        {
            env = "dev";
        }
        else if (input.compare("int") == 0)
        {
            env = "int";
        }
        else if (input.compare("prod") == 0)
        {
            env = "prod";
        }
        else
        {
            PLOG_ERROR << "Wrong Environment defined: " << input;
            exit(EXIT_FAILURE);
        }
    }

    if (result.count("create"))
    {
        std::string input = result["create"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0)
        {
            inifile = prog.c_str();
            inifile.append(".ini");
        }
        else
        {
            inifile = input.c_str();
        }
        Inifile iniConfig;
        iniConfig.createIni();
        if (!iniConfig.saveIniToFile(inifile))
        {
            exit(EXIT_FAILURE);
        }
        if (!iniConfig.loadIni(inifile))
        {
            exit(EXIT_FAILURE);
        }
        iniConfig.listIniEntries();
        exit(EXIT_SUCCESS);
    }

    if (result.count("ini"))
    {
        std::string input = result["ini"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0)
        {
            std::cout << "\t=> missing argument <=\n"
                      << std::endl;
            std::cout << options.help() << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            inifile = input.c_str();
        }
    }

    if (result.count("listini"))
    {
        std::string input = result["listini"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0)
        {
            inifile = prog.c_str();
            inifile.append(".ini");
        }
        else
        {
            inifile = input.c_str();
        }
        Inifile iniConfig;
        if (!iniConfig.loadIni(inifile))
        {
            exit(EXIT_FAILURE);
        }
        iniConfig.listIniEntries();
        exit(EXIT_SUCCESS);
    }

    // ##################
    // ok-la, let's do it

    /*
    PLOG_VERBOSE << "This is a VERBOSE message";
    PLOG_DEBUG << "This is a DEBUG message";
    PLOG_INFO << "This is an INFO message";
    PLOG_WARNING << "This is a WARNING message";
    PLOG_ERROR << "This is an ERROR message";
    PLOG_FATAL << "This is a FATAL message";
    PLOG_NONE << "This is a NONE message";
    */

    /**
     * @brief inifile load
     */
    Inifile iniConfig;
    if (!iniConfig.loadIni(inifile))
    {
        exit(EXIT_FAILURE);
    }
    /*
    if (!iniConfig.checkSqlMeta())
    {
        exit(EXIT_FAILURE);
    }*/

    /**
     * @brief check environment for db or sqlfile
     */
    SqliteDb sqliteDb;
    PgDb pgDb;

    // dev: sql-file
    if (env.compare("dev") == 0)
    {
    }
    // int: sqlite3
    if (env.compare("int") == 0)
    {
        if (sqliteDb.connectDb(iniConfig, env))
        {
            if (sqliteDb.createTables() == true)
            {
                PLOG_INFO << "SQLite3 db created";
            }
            else
            {
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    // prod: PostgreSQL
    if (env.compare("prod") == 0)
    {
        if (pgDb.connectDb(iniConfig, env))
        {
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }

    /**
     * @brief read dirs
     */
    QString path = "/home/zb_bamboo/Dokumente/2021";
    ReadDir readDir(path);
    readDir.searchFilesRekursive();

    /**
     * @brief the end
     */
    // pgDb.closeDb();
    sqliteDb.closeDb();
    exit(EXIT_SUCCESS);
}
