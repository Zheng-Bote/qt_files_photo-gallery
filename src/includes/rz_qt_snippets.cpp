#include "rz_qt_snippets.hpp"

QtSnippets::QtSnippets() {}

QtSnippets::~QtSnippets() {}

/**
 * @brief QtSnippets::getEnvVar
 * @param name
 * @return tuple (bool, name environment value)
 */
std::tuple<bool, std::string> QtSnippets::getEnvVar(const QString &name)
{
    QProcessEnvironment::systemEnvironment();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains(name)) {
        return std::make_tuple(true, env.value(name).toStdString());
    }
    return std::make_tuple(false, "Environment not found");
}

QString QtSnippets::getProgName()
{
    return progName;
}

QString QtSnippets::getProgAbsolutePath()
{
    return progAbsolutePath;
}

QString QtSnippets::getProgDefaultLog()
{
    return progDefaultLog;
}

QString QtSnippets::getProgDefaultIni()
{
    return progDefaultIni;
}

std::tuple<bool, std::string> QtSnippets::setProgData(const QString &pathToProg)
{
    QFile file(pathToProg);
    QFileInfo fileInfo(file.fileName());
    QDir dir = QFileInfo(file).absoluteDir();

    Filesystem fs;
    Snippets snippets;
    bool oknok{false};
    std::string msg{"blank"};

    progName = fileInfo.completeBaseName();
    progAbsolutePath = dir.absolutePath();

    // logfile & path // read only: /var/log
    if (fs.isDirectory("/var/logs")) {
        progDefaultLog = "/var/log/";
    } else {
        progDefaultLog = progAbsolutePath + "/";
    }
    progDefaultLog.append(progName);
    progDefaultLog.append(".log");

    // inifile & path
    std::tie(oknok, msg) = getEnvVar("HOME");

    if (snippets.checkFunctionReturn(std::make_tuple(oknok, msg), Snippets::Status::ERROR)) {
        if (fs.isDirectory(msg + "/.config")) {
            progDefaultIni = msg.c_str();
            progDefaultIni.append("/.config/");
        } else {
            progDefaultIni = progAbsolutePath + "/";
        }
        progDefaultIni.append(progName);
        progDefaultIni.append(".ini");
    }

    return std::make_tuple(true, "Environment set");
}
