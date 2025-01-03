#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcessEnvironment>

#include <tuple>

#include "rz_filesystem.hpp"
#include "rz_snippets.hpp"

class QtSnippets
{
public:
    QtSnippets();
    ~QtSnippets();

    std::tuple<bool, std::string> setProgData(QString const &pathToProg);

    std::tuple<bool, std::string> getEnvVar(QString const &name);
    QString getProgName();
    QString getProgAbsolutePath();
    QString getProgDefaultLog();
    QString getProgDefaultIni();

private:
    QString progName{}, progAbsolutePath{}, progDefaultLog{"/var/log/"}, progDefaultIni{};
};
