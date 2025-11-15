#include "rz_plugins.hpp"

Rz_Plugins::Rz_Plugins(QObject *parent)
    : QObject(parent)
{}

QStringList Rz_Plugins::getPluginsFromDir(const QString &path)
{
    PLOG_INFO << "getPlugins from path: " << path;
    QStringList plugins;
    QStringList filter;

    // Windows, Linux, Mac
    //filter << "*.dll" << "*.so" << "*.dylib";
#ifndef Q_OS_LINUX
    filter << "*.so";
#elif Q_OS_MACX
    filter << "*.dylib";
#endif

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    foreach (QFileInfo file, list) {
        if (!file.isSymLink()) {
            plugins.append(file.filePath());
        }
    }
    if (plugins.length() == 0) {
        PLOG_WARNING << "No PlugIns found";
        return plugins;
    }

    return plugins;
}

QList<QString> Rz_Plugins::reducePlugins(QHash<QString, QString> &pluginMap,
                                         const QStringList &pluginsToUse)
{
    QList<QString> rmItem, orderedPluginsToUse;

    for (auto i = pluginsToUse.cbegin(), end = pluginsToUse.cend(); i != end; ++i) {
        if (pluginMap.contains(*i)) {
            orderedPluginsToUse.append(*i);
        }
    }

    countedPlugins = (int) orderedPluginsToUse.size();
    return orderedPluginsToUse;
}
