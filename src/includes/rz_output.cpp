#include "rz_output.hpp"

#include <iostream>

Output::Output(QObject *parent)
    : QObject(parent)
{}

Output::~Output() {}

QStringList Output::getPlugins(const QString &path)
{
    PLOG_INFO << "getPlugins from path: " << path;
    QStringList plugins;
    QStringList filter;
    // Windows, Linux, Mac
    //filter << "*.dll" << "*.so" << "*.dylib";
    filter << "*.so";

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
                PLOG_INFO << "Plugin short Name: " << plugin->getPluginNameShort().toStdString();
                // std::cout << std::left << std::setfill('.') << std::setw(20) << "Version:" << plugin->getVersion().toStdString() << std::endl;
                PLOG_INFO << "Plugin Version ?: " << plugin->getPluginVersion().toStdString();
                PLOG_INFO << "Plugin Description: " << plugin->getPluginDescription().toStdString();
                loader.unload();
            } else {
                PLOG_WARNING << "Could not cast: " << loader.fileName();
            }
        }
    }
}

std::tuple<bool, std::string> Output::testPlugins(QMap<QString, QString> &pluginMap,
                                                  const QStringList &plugins)
{
    countedPlugins = int(plugins.length());

    foreach (QString file, plugins) {
        qDebug() << "Loading..." << file;

        QPluginLoader loader(file);
        if (!loader.load()) {
            qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
            --countedPlugins;
            continue;
        }

        qDebug() << "Loaded: " << loader.fileName();

        Plugin *plugin = qobject_cast<Plugin *>(loader.instance());
        const auto width = 20;
        if (plugin) {
            pluginMap[plugin->getPluginNameShort()] = loader.fileName();
            std::cout << std::left << std::setfill('.') << std::setw(width)
                      << "Plugin short Name:" << plugin->getPluginNameShort().toStdString()
                      << std::endl;
            std::cout << std::left << std::setfill('.') << std::setw(width)
                      << "Plugin long Name:" << plugin->getPluginNameLong().toStdString()
                      << std::endl;
            std::cout << std::left << std::setfill('.') << std::setw(width)
                      << "Plugin Version:" << plugin->getPluginVersion().toStdString() << std::endl;
            std::cout << "Plugin Description: " << plugin->getPluginDescription().toStdString()
                      << std::endl;

            loader.unload();
            pluginMap[plugin->getPluginNameShort()] = loader.fileName();
        } else {
            qDebug() << "Could not cast: " << loader.fileName();
            --countedPlugins;
        }
    }

    // no valid plugins
    if (countedPlugins <= 0) {
        return std::make_tuple(false, "no valid plugins");
    }
    // at least 1 valid plugin
    return std::make_tuple(true, std::format("Plugins found: {}", countedPlugins));
}

void Output::reducePlugins(QMap<QString, QString> &pluginMap, const QStringList &pluginsToUse)
{
    for (const auto &plugin : std::as_const(pluginMap)) {
        if (pluginsToUse.contains(plugin) == false) {
            pluginMap.remove(plugin);
        }
    }
    countedPlugins = (int) pluginMap.size();
}

int Output::getCountedPlugins()
{
    return countedPlugins;
}

// TODO
void Output::runPlugins(const QMap<QString, QString> &pluginMap,
                        const QString &inFile,
                        const QString &outFile,
                        std::shared_ptr<Inifile> sptr_ini_config)
{
    QThread::currentThread()->setObjectName("runPlugins");
    QThreadPool pool;

    for (const auto &plugin : std::as_const(pluginMap)) {
        DoThread *doThread = new DoThread();
        doThread->setPluginFile(plugin);
        doThread->setInFile(inFile);
        doThread->setOutFile(outFile);
        doThread->setAutoDelete(true);
        pool.start(doThread);
    }
    pool.waitForDone();
}
