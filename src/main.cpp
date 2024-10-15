/**
 * @file main.cpp
 * @author ZHENG Robert (https://github.com/Zheng-Bote/qt_files_photo-gallery)
 * @brief app to add photos to DB
 * @details QT6 CXX23 console app with plugins to convert photos, collect Exif/IPTC and add metadata to DB
 * @date 2024-09-19
 * @copyright Copyright (c) 2024 ZHENG Robert
 */

// ToDo: options logfile
// ToDo: configure default path for ini to /etc/<...>/... ???
// ToDo: AesEnc

#include <QCoreApplication>

#include <print>

#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Init.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Log.h"

#include "configured/rz_config.h"
#include "cxxopts.hpp"
#include "includes/rz_datetime.h"
#include "includes/rz_inifile.h"
#include "includes/rz_output.h"
#include "includes/rz_string_lib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ToDo
    //   AesEnc aesEnc;

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
    QString logfile = "/var/log/";
    logfile.append(prog.c_str());
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
        std::cout << PROG_NAME << " v" << PROG_VERSION << std::endl;
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

    Output output;
    QString plugPath
        = "/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/Desktop_Qt_6_7_3-Debug";
    output.listPlugins(output.getPlugins(plugPath));

    DateTime dt;

    std::println("{}",
                 rz_string_lib::replace("/var/log/{{ DATE_TIME }}_dev.log",
                                        "{{ DATE_TIME }}",
                                        dt.getFormatedUtcDateTimeHuman("YYYY-MM-DD_HH-MM-SS")));

    /**
     * @brief the end
     */

    EXIT_SUCCESS;
}
