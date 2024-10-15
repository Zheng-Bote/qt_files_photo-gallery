#include "rz_output.h"

#include <iostream>

Output::Output(QObject *parent)
    : QObject(parent)
{}

Output::~Output() {}

QStringList Output::getPlugins(QString &path)
{
    PLOG_INFO << "getPlugins from path: " << path;
    QStringList plugins;
    QStringList filter;
    // Windows, Linux, Mac
    filter << "*.dll" << "*.so" << "*.dylib";

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    foreach (QFileInfo file, list) {
#ifndef Q_OS_MACX
        plugins.append(file.filePath());
#else
        if (!file.isSymLink()) {
            plugins.append(file.filePath());
        }
#endif
    }

    if (plugins.length() == 0) {
        PLOG_WARNING << "No PlugIns found";
        return plugins;
    }

    return plugins;
}

void Output::listPlugins(QStringList plugins)
{
    PLOG_INFO << "listPlugins";

    foreach (QString file, plugins) {
        QPluginLoader loader(file);

        if (!loader.load()) {
            PLOG_WARNING << "Error: " << loader.fileName() << " Error: " << loader.errorString();
            continue;
        } else {
            Plugin *plugin = qobject_cast<Plugin *>(loader.instance());
            if (plugin) {
                // std::cout << std::left << std::setfill('.') << std::setw(20) << "Plugin Name:" << plugin->getNameShort().toStdString() << std::endl;
                PLOG_INFO << "Plugin Name: " << plugin->getNameShort().toStdString();
                // std::cout << std::left << std::setfill('.') << std::setw(20) << "Version:" << plugin->getVersion().toStdString() << std::endl;
                PLOG_INFO << "Plugin Version: " << plugin->getVersion().toStdString();
                loader.unload();
            } else {
                PLOG_WARNING << "Could not cast: " << loader.fileName();
            }
        }
    }
}
