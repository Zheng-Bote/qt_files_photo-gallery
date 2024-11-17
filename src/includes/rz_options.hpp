#pragma once

#include <memory>
#include <print>

#include "configured/rz_config.h"
#include "cxxopts.hpp"
#include "rz_inifile.hpp"
#include "rz_qt_snippets.hpp"


namespace rz_options {

void check_options(std::shared_ptr<QtSnippets> sptr_qt_snippets,
                   std::shared_ptr<Snippets> sptr_snippets,
                   const int argc,
                   char *argv[],
                   QString &inifile,
                   QString &env,
                   std::shared_ptr<Inifile> sptr_ini_config)
{
    std::string prog = PROG_NAME;

    cxxopts::Options options(PROG_NAME, PROG_DESCRIPTION);
    options.set_width(120).add_options()("a,auto",
                                         "runs with default Inifile: /<user home>/.config/" + prog
                                             + ".ini")("c,create",
                                                       "create Inifile",
                                                       cxxopts::value<std::string>()
                                                           ->implicit_value("<pathTo/inifile>")
                                                           ->default_value("/<user home>/.config/"
                                                                           + prog + ".ini"))(
        "e,env",
        "Environment <dev> <int> <prod>",
        cxxopts::value<std::string>()->default_value("dev"))

        ("i,ini",
         "use Inifile",
         cxxopts::value<std::string>()->implicit_value(
             "<pathTo/inifile>"))("l,listini",
                                  "list Inifile",
                                  cxxopts::value<std::string>()
                                      ->implicit_value("<pathTo/inifile>")
                                      ->default_value(
                                          "/<user home>/.config/" + prog
                                          + ".ini"))("v,version",
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
        std::cout << PROG_NAME << " v" << PROG_VERSION << " " << PROG_HOMEPAGE << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (result.count("version")) {
        std::cout << PROG_NAME << " v" << PROG_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (result.count("create")) {
        std::string input = result["create"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0) {
            inifile = sptr_qt_snippets->getProgDefaultIni();
        } else {
            inifile = input.c_str();
        }

        sptr_ini_config->createIni();
        sptr_snippets->checkFunctionReturn(sptr_ini_config->saveIniToFile(inifile),
                                           Snippets::Status::FATAL);
        sptr_snippets->checkFunctionReturn(sptr_ini_config->loadIni(inifile),
                                           Snippets::Status::FATAL);
        sptr_ini_config->listIniEntries(sptr_qt_snippets);
        exit(EXIT_SUCCESS);
    }

    if (result.count("listini")) {
        std::string input = result["listini"].as<std::string>();
        if (input.compare("<pathTo/inifile>") == 0) {
            inifile = sptr_qt_snippets->getProgDefaultIni();
        } else {
            inifile = input.c_str();
        }

        sptr_snippets->checkFunctionReturn(sptr_ini_config->loadIni(inifile),
                                           Snippets::Status::FATAL);
        sptr_ini_config->listIniEntries(sptr_qt_snippets);
        exit(EXIT_SUCCESS);
    }

    if (result.count("env")) {
        std::string input = result["env"].as<std::string>();

        if (input.compare("dev") == 0) {
            env = "dev";
        } else if (input.compare("int") == 0) {
            env = "int";
        } else if (input.compare("prod") == 0) {
            env = "prod";
        } else {
            PLOG_ERROR << "Wrong Environment defined: " << input;
            exit(EXIT_FAILURE);
        }
        PLOG_INFO << "Environment: " << env;
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

    // default, nothing to do
    /*if (result.count("auto")) {
        inifile = prog.c_str();
        inifile.append(".ini");
    }*/
}
} // namespace rz_options
