#include "rz_qt_snippets.h"

QT_snippets::QT_snippets() {}

/**
 * @brief QT_snippets::getEnvVar
 * @param name
 * @return tuple (bool, name environment value)
 */
std::tuple<bool, std::string> QT_snippets::getEnvVar(const QString &name)
{
    QProcessEnvironment::systemEnvironment();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains(name)) {
        return std::make_tuple(true, env.value(name).toStdString());
    }
    return std::make_tuple(false, "Environment not found");
}

QString QT_snippets::getProgName()
{
    return progName;
}

QString QT_snippets::getProgAbsolutePath()
{
    return progAbsolutePath;
}

QString QT_snippets::getProgDefaultLog()
{
    return progDefaultLog;
}

QString QT_snippets::getProgDefaultIni()
{
    return progDefaultIni;
}

std::tuple<bool, std::string> QT_snippets::setProgData(const QString &pathToProg)
{
    QFile file = pathToProg;
    QFileInfo fileInfo(file.fileName());
    QDir dir = QFileInfo(file).absoluteDir();

    Filesystem fs;
    Snippets snippets;
    bool oknok{false};
    std::string msg{"blank"};

    progName = fileInfo.completeBaseName();
    progAbsolutePath = dir.absolutePath();

    // logfile & path
    if (fs.isDirectory("/var/log")) {
        progDefaultLog = "/var/log/";
    } else {
        progDefaultLog = progAbsolutePath;
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
            progDefaultIni = progAbsolutePath;
        }
        progDefaultIni.append(progName);
        progDefaultIni.append(".ini");
    }

    return std::make_tuple(true, "Environment set");
}
