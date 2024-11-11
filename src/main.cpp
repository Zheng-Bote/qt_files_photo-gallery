/**
 * @file main.cpp
 * @author ZHENG Robert (https://github.com/Zheng-Bote/qt_files_photo-gallery)
 * @brief app to add photos to web-based photo-gallery
 * @details QT6 CXX23 console app with plugins to convert photos, collect Exif/IPTC and add metadata to DB
 * @date 2024-09-19
 * @copyright Copyright (c) 2024 ZHENG Robert
 */

// TODOS: options logfile
// TODOS: configure default path for ini to /etc/<...>/... ???
// TODOS: AesEnc

#include <QCoreApplication>

#include <future>
#include <print>

#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Init.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Log.h"

#include "configured/rz_config.h"

#include "includes/rz_options.hpp"
#include "includes/rz_qt_snippets.h"
#include "includes/rz_snippets.h"

#include "includes/rz_inifile.h"
#include "includes/rz_output.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    QCoreApplication::setApplicationName("files_to_photo-gallery");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationDomain("https://github.com/Zheng-Bote/qt_files_photo-gallery");

    PLOG_VERBOSE << "This is a VERBOSE message";
    PLOG_DEBUG << "This is a DEBUG message";
    PLOG_INFO << "This is an INFO message";
    PLOG_WARNING << "This is a WARNING message";
    PLOG_ERROR << "This is an ERROR message";
    PLOG_FATAL << "This is a FATAL message";
    PLOG_NONE << "This is a NONE message";    
    */

    QT_snippets qt_snippets;
    auto asyncProgConfig = std::async(std::launch::async,
                                      &QT_snippets::setProgData,
                                      &qt_snippets,
                                      argv[0]);
    bool oknok{false};
    std::string msg{"blank"};
    QString inifile{};
    QString env{"dev"};
    QMap<QString, QString> pluginsMap;

    Inifile iniConfig;
    Snippets snippets;
    Output output;

    // ################## ok-la, let's do it ################## //

    std::tie(oknok, msg) = asyncProgConfig.get();
    // default inifile
    if (inifile.length() < 1) {
        inifile = qt_snippets.getProgDefaultIni();
    }

    // default logging
    QString logfile = qt_snippets.getProgDefaultLog();
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logfile.toStdString().c_str(),
                                                                      5000,
                                                                      3);
    plog::init(plog::debug, &fileAppender);
    //plog::init(plog::info, &fileAppender);
    // fileAppender.setFileName("SetFileNameBBB.log");
    plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::get()->addAppender(&consoleAppender); // Also add logging to the console.
    PLOG_INFO << "Logfile: " << logfile;

    // get the options
    rz_options::check_options(qt_snippets, snippets, argc, argv, inifile, env, iniConfig);

    // load inifile
    snippets.checkFunctionReturn(iniConfig.loadIni(inifile), Snippets::Status::FATAL);

    snippets.checkFunctionReturn(output.testPlugins(pluginsMap,
                                                    output.getPlugins(iniConfig.getPluginsDir(
                                                        env, qt_snippets.getProgName()))),
                                 Snippets::Status::FATAL);

    // output.listPlugins(output.getPlugins(plugPath));

    // reduce to used plugins
    output.reducePlugins(pluginsMap, iniConfig.getPluginsToUse(env));

    if (snippets.checkFunctionReturn(snippets.test("Hello World!"), Snippets::Status::ERROR)) {
        std::println("main: OK");
    } else {
        std::println("main: NOK");
    }
    // FATAL doesn't need if-case due to EXIT_FAILURE
    snippets.checkFunctionReturn(snippets.test("Hello World!"), Snippets::Status::FATAL);

    /**
     * @brief the end
     */

    exit(EXIT_SUCCESS);
}
