/**
 * @file main.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief QT6 CXX20 console app to add photos to PostgreSQL
 * @details simple console app
 * @version 0.1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024 ZHENG Robert
 *
 */

#include <QCoreApplication>
#include <QDebug>

#include "Includes/cxxopts.hpp"
#include "Includes/rz_inifile.h"
#include "Includes/rz_pg_db.h"
#include "Includes/rz_readdir.h"

const std::string VERSION = "0.1.0";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string prog = argv[0];

    // default inifile
    QString inifile = prog.c_str();
    inifile.append(".ini");

    /**
     * @brief options for program
     */
    cxxopts::Options options(prog, "photos to db");
    options.set_width(100).add_options()("a,auto",
                                         "run with default Inifile: " + prog
                                             + ".ini")("c,create",
                                                       "create Inifile",
                                                       cxxopts::value<std::string>()
                                                           ->implicit_value("<pathTo/inifile>")
                                                           ->default_value(prog + ".ini"))

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
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (result.count("version")) {
        std::cout << prog << "-" << VERSION << std::endl;
        exit(0);
    }

    if (result.count("auto")) {
        inifile = prog.c_str();
        inifile.append(".ini");
    }

    if (result.count("create")) {
        std::string input = result["create"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0) {
            inifile = prog.c_str();
            inifile.append(".ini");
        } else {
            inifile = input.c_str();
        }
        Inifile iniConfig;
        iniConfig.createIni();
        if (!iniConfig.saveIniToFile(inifile)) {
            exit(EXIT_FAILURE);
        }
        if (!iniConfig.loadIni(inifile)) {
            exit(EXIT_FAILURE);
        }
        iniConfig.listIniEntries();
        exit(EXIT_SUCCESS);
    }

    if (result.count("ini")) {
        std::string input = result["ini"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0) {
            std::cout << "\t=> missing argument <=\n" << std::endl;
            std::cout << options.help() << std::endl;
            exit(EXIT_SUCCESS);
        } else {
            inifile = input.c_str();
        }
    }

    if (result.count("listini")) {
        std::string input = result["listini"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0) {
            inifile = prog.c_str();
            inifile.append(".ini");
        } else {
            inifile = input.c_str();
        }
        Inifile iniConfig;
        if (!iniConfig.loadIni(inifile)) {
            exit(EXIT_FAILURE);
        }
        iniConfig.listIniEntries();
        exit(EXIT_SUCCESS);
    }

    /**
     * @brief inifile load
     */
    Inifile iniConfig;
    if (!iniConfig.loadIni(inifile)) {
        exit(EXIT_FAILURE);
    }
    if (!iniConfig.checkSqlMeta()) {
        exit(EXIT_FAILURE);
    }

    /**
     * @brief db connect
     */
    PgDb pgDb(iniConfig);

    /**
     * @brief read dirs
     */
    QString path = "/home/zb_bamboo/Dokumente/2021";
    ReadDir readDir(path);
    readDir.searchFilesRekursive();

    /**
     * @brief the end
     */
    pgDb.closeDb();
    exit(EXIT_SUCCESS);
}
