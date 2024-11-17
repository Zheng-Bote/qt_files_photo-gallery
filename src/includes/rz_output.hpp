#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QPluginLoader>
#include <QThread>
#include <QThreadPool>
#include <memory>

#include "plog/Log.h"
#include "rz_do_thread.hpp"
#include "rz_inifile.hpp"
#include "rz_photo-gallery_plugins.hpp"

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
                    std::shared_ptr<Inifile> sptr_ini_config);

private:
    int countedPlugins{0};
signals:

public slots:
};
