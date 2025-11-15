#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QHash>
#include <QObject>
#include <QPluginLoader>
#include <QString>
#include <QThread>
#include <QThreadPool>

#include <iostream>
#include <memory>

#include "plog/Log.h"

class Rz_Plugins : public QObject
{
    Q_OBJECT

public:
    explicit Rz_Plugins(QObject *parent = nullptr);
    ~Rz_Plugins();

    QStringList getPluginsFromDir(const QString &path);
    QList<QString> reducePlugins(QHash<QString, QString> &pluginMap,
                                 const QStringList &pluginsToUse);

private:
    int countedPlugins{0};
};
