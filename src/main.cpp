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
#include <memory>
#include <print>

#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Init.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Log.h"

#include "includes/rz_config.h"

#include "includes/rz_inifile.hpp"
#include "includes/rz_options.hpp"
#include "includes/rz_output.hpp"
#include "includes/rz_qt_snippets.hpp"
#include "includes/rz_snippets.hpp"

#include "includes/httplib.h"
#include "includes/rz_webserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName(PROG_EXEC_NAME);
    QCoreApplication::setApplicationVersion(PROG_VERSION);
    QCoreApplication::setOrganizationName(PROG_ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(PROG_ORGANIZATION_DOMAIN);

    /*
    PLOG_VERBOSE << "This is a VERBOSE message";
    PLOG_DEBUG << "This is a DEBUG message";
    PLOG_INFO << "This is an INFO message";
    PLOG_WARNING << "This is a WARNING message";
    PLOG_ERROR << "This is an ERROR message";
    PLOG_FATAL << "This is a FATAL message";
    PLOG_NONE << "This is a NONE message";    
    */

    QtSnippets qt_snippets;
    auto sptr_qt_snippets = std::make_shared<QtSnippets>();
    auto asyncProgConfig = std::async(std::launch::async,
                                      &QtSnippets::setProgData,
                                      sptr_qt_snippets,
                                      argv[0]);
    bool oknok{false};
    std::string msg{"blank"};
    QString inifile{};
    QString env{"dev"};
    QMap<QString, QString> pluginsMap;

    auto sptr_ini_config = std::make_shared<Inifile>();
    auto sptr_snippets = std::make_shared<Snippets>();
    auto sptr_output = std::make_shared<Output>();

    // ################## ok-la, let's do it ################## //

    std::tie(oknok, msg) = asyncProgConfig.get();
    // default inifile
    if (inifile.length() < 1) {
        inifile = sptr_qt_snippets->getProgDefaultIni();
    }

    // default logging
    QString logfile = sptr_qt_snippets->getProgDefaultLog();
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
    rz_options::check_options(sptr_qt_snippets,
                              sptr_snippets,
                              argc,
                              argv,
                              inifile,
                              env,
                              sptr_ini_config);

    // load inifile
    sptr_snippets->checkFunctionReturn(sptr_ini_config->loadIni(inifile), Snippets::Status::FATAL);

    sptr_snippets->checkFunctionReturn(
        sptr_output->testPlugins(pluginsMap,
                                 sptr_output->getPlugins(
                                     sptr_ini_config->getPluginsDir(env,
                                                                    qt_snippets.getProgName()))),
        Snippets::Status::FATAL);

    // output.listPlugins(output.getPlugins(plugPath));
    //qDebug() << "output Plugins found";
    /*for (auto i = pluginsMap.begin(); i != pluginsMap.end(); ++i) {
        qDebug() << i.key() << ": " << i.value();
    }*/

    // reduce to ordered list of used plugins which also exist
    QList<QString> list = sptr_output->reducePlugins(pluginsMap,
                                                     sptr_ini_config->getPluginsToUse(env));
    /*for (auto i = list.begin(); i != list.end(); ++i) {
        qDebug() << "to use: " << ": " << *i;
    }*/

    qDebug() << "0) " << list[0];
    qDebug() << "1) " << list[1];

    // ###################################### DEBUG

    QHash<QString, QString> exifDefaultMetaTags, iptcDefaultMetaTags, xmpDefaultMetaTags;

    QPluginLoader loader("/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/"
                         "Desktop_Qt_6_7_3-Debug/plugins/librz_default_metadata");
    if (!loader.load()) {
        qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
    }

    qDebug() << "Loaded: " << loader.fileName();

    Plugin *plugin = qobject_cast<Plugin *>(loader.instance());
    if (plugin) {
        qDebug() << "Plugin found";
        QMap<QString, QString> mapParseKey;
        mapParseKey.insert("pathToDb", sptr_ini_config->getDefaultMetadataSource(env));
        sptr_snippets->checkFunctionReturn(plugin->parseFile(mapParseKey, ""),
                                           Snippets::Status::FATAL);
        exifDefaultMetaTags = plugin->getHashMap("EXIF");
        iptcDefaultMetaTags = plugin->getHashMap("IPTC");
        xmpDefaultMetaTags = plugin->getHashMap("XMP");

        /*
        for (auto i = exifDefaultMetaTags.begin(); i != exifDefaultMetaTags.end(); ++i) {
            qDebug() << i.key() << ": " << i.value();
        }
        */
        plugin->doClose();
        loader.unload();
    }

    // read image metadata
    loader.setFileName("/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/"
                       "Desktop_Qt_6_7_3-Debug/plugins/librz_read_metadata");
    if (!loader.load()) {
        qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
    }

    qDebug() << "Loaded read meta: " << loader.fileName();

    QMap<QString, QString> eMT;
    QHash<QString, QString> exifData, iptcData, xmpData;
    QString pathToImgImg = "/home/zb_bamboo/DEV/images/2003-05-24_164033.jpg";
    plugin = qobject_cast<Plugin *>(loader.instance());
    if (plugin) {
        qDebug() << "Plugin found";
        sptr_snippets->checkFunctionReturn(plugin->parseFile(eMT, pathToImgImg),
                                           Snippets::Status::FATAL);

        plugin->setHashMap(exifDefaultMetaTags, "EXIF");
        exifData = plugin->getHashMap("EXIF");

        plugin->setHashMap(iptcDefaultMetaTags, "IPTC");
        iptcData = plugin->getHashMap("IPTC");

        plugin->setHashMap(xmpDefaultMetaTags, "XMP");
        xmpData = plugin->getHashMap("XMP");

        /*
        for (auto i = exifData.begin(); i != exifData.end(); ++i) {
            qDebug() << i.key() << ": " << i.value();
        }
        */
    }

    // convert image
    loader.setFileName("/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/"
                       "Desktop_Qt_6_7_3-Debug/plugins/librz_convert_image");
    if (!loader.load()) {
        qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
    }
    plugin = qobject_cast<Plugin *>(loader.instance());
    if (plugin) {
        qDebug() << "Plugin found";
        sptr_snippets->checkFunctionReturn(plugin->parseFile(eMT, pathToImgImg),
                                           Snippets::Status::FATAL);
        sptr_snippets->checkFunctionReturn(plugin->writeFile(eMT, eMT, pathToImgImg),
                                           Snippets::Status::WARNING);
        ;
    }

    // write SQL-File
    eMT.insert("pathToDb", sptr_ini_config->getDefaultMetadataSource(env));
    loader.setFileName("/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/"
                       "Desktop_Qt_6_7_3-Debug/plugins/librz_write_sqlfile");
    if (!loader.load()) {
        qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
    }
    plugin = qobject_cast<Plugin *>(loader.instance());
    if (plugin) {
        qDebug() << "Plugin found";
        sptr_snippets->checkFunctionReturn(plugin->parseFile(eMT, pathToImgImg),
                                           Snippets::Status::FATAL);

        plugin->setHashMap(exifData, "EXIF");
        plugin->setHashMap(iptcData, "IPTC");
        plugin->setHashMap(xmpData, "XMP");

        sptr_snippets->checkFunctionReturn(plugin->writeFile(eMT, eMT, "./SQL-files"),
                                           Snippets::Status::FATAL);
    }

    // ######################################
    exit(EXIT_SUCCESS);
    // ######################################

    // start webserver
    httplib::Server svr;
    auto img = svr.set_mount_point("/img", "./html/img");
    auto css = svr.set_mount_point("/css", "./html/css");
    auto js = svr.set_mount_point("/js", "./html/js");
    auto i18n = svr.set_mount_point("/i18n", "./html/i18n");

    svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        res.set_file_content("./html/index.html");
    });
    svr.Get("/:file", [&](const httplib::Request &req, httplib::Response &res) {
        auto file = req.path_params.at("file");
        std::string html_file = std::format("./html/{}", file);
        res.set_file_content(html_file);
    });
    svr.Get("/:folder/:file", [&](const httplib::Request &req, httplib::Response &res) {
        auto folder = req.path_params.at("folder");
        auto file = req.path_params.at("file");
        std::string html_file = std::format("./html/{}/{}", folder, file);
        res.set_file_content(html_file);
    });
    svr.Get("/form", [](const httplib::Request & /*req*/, httplib::Response &res) {
        res.set_content(rz_webserver::getForm(), "text/html");
    });
    svr.listen("0.0.0.0", 8080);

    /**
     * @brief the end
     */

    sptr_qt_snippets = nullptr;
    sptr_ini_config = nullptr;
    sptr_snippets = nullptr;
    sptr_output = nullptr;

    exit(EXIT_SUCCESS);
}
