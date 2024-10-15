#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QPluginLoader>

#include "plog/Log.h"

#include "rz_photo-gallery_plugins.h"

class Output : public QObject
{
    Q_OBJECT

public:
    explicit Output(QObject *parent = nullptr);
    ~Output();

    QStringList getPlugins(QString &path);
    void listPlugins(QStringList plugins);

private:
signals:

public slots:
};
