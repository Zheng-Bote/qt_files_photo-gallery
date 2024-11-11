#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QPluginLoader>
#include <QThread>
#include <QThreadPool>

#include "plog/Log.h"
#include "rz_do_thread.h"
#include "rz_inifile.h"
#include "rz_photo-gallery_plugins.h"

class Output : public QObject
{
    Q_OBJECT

public:
    explicit Output(QObject *parent = nullptr);
    ~Output();

    QStringList getPlugins(const QString &path);
    void listPlugins(QStringList plugins);
    std::tuple<bool, std::string> testPlugins(QMap<QString, QString> &pluginMap,
                                              const QStringList &plugins);
    void reducePlugins(QMap<QString, QString> &pluginMap, const QStringList &pluginsToUse);
    int getCountedPlugins();
    void runPlugins(const QMap<QString, QString> &pluginMap,
                    const QString &inFile,
                    const QString &outFile,
                    Inifile &iniConfig);

private:
    int countedPlugins{0};
signals:

public slots:
};
